#include "mesh_handler.h"               // Custom header
#include <zephyr/kernel.h>
#include <zephyr/drivers/lora.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#include <string.h>
#include <stdlib.h>

// FUNCTION DEF

LOG_MODULE_REGISTER(mesh_node, CONFIG_LOG_DEFAULT_LEVEL);   // Register this source file ("mesh_node") as a logging module

// Make tx_msgq private
K_MSGQ_DEFINE(tx_msgq, sizeof(struct tx_msg_dyn *), TX_QUEUE_LEN, 4);   // Message queue for outgoing packets (private to this file).
K_THREAD_STACK_DEFINE(stack_area, STACK_SIZE);                          // Stack memory and thread object for the transmit task.
static struct k_thread transmit_thread;                                 // Stack memory and thread object for the transmit task.

static struct recent_entry  // Cache for recently seen packets to prevent duplicate forwarding.
{
    uint8_t src;
    uint16_t seq;
} recent_cache[CACHE_SIZE];

static int cache_idx;   // Tracks cache insertion index
static mesh_receive_callback_t receive_callback = NULL; // User callback for application layer

// ------------------------ Utility Functions ------------------------//

// Compute 16-bit CRC checksum (polynomial 0x1021) over given data.
//Used for error detection in transmitted packets.
static uint16_t calc_checksum_crc16(const uint8_t *data, size_t len){
    uint16_t crc = 0x0000;
    for (size_t i = 0; i < len; i++)
    {
        crc ^= (uint16_t)data[i] << 8;
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x8000)
                crc = (crc << 1) ^ 0x1021;  // Polynomial division
            else
                crc <<= 1;
        }
    }
    return crc;
}

// Check if a (src, seq) pair was already processed (duplicate suppression).
static bool seen_before(uint8_t src, uint16_t seq)
{
    for (int i = 0; i < CACHE_SIZE; i++)
    {
        if (recent_cache[i].src == src && recent_cache[i].seq == seq)
            return true;
    }
    return false;
}

// Add a new (src, seq) pair to the recent packet cache.
static void add_to_cache(uint8_t src, uint16_t seq)
{
    recent_cache[cache_idx].src = src;
    recent_cache[cache_idx].seq = seq;
    cache_idx = (cache_idx + 1) % CACHE_SIZE;   // Circular buffer
}


// ------------------------ LoRa Config ------------------------//

// Configure LoRa modem in RX mode.
static int configure_rx(const struct device *dev)
{
    struct lora_modem_config cfg = {
        .frequency = 865100000,         // Operating frequency
        .bandwidth = BW_125_KHZ,        // Channel bandwidth
        .datarate = SF_12,              // Spreading factor
        .preamble_len = 8,              // Preamble length
        .coding_rate = CR_4_5,          // Error correction coding rate
        .iq_inverted = false,
        .public_network = false,
        .tx_power = 14,                 // Transmission power in dBm
        .tx = false,                    // RX mode
    };  

    int ret = lora_config(dev, &cfg);
    if (ret < 0)
    {
        LOG_ERR("Failed to configure RX: %d", ret);
        return ret;
    }

    // Register asynchronous receive callback
    lora_recv_async(dev, mesh_receive_cb, NULL);
    return 0;
}

// Configure LoRa modem in TX mode.
static int configure_tx(const struct device *dev)
{
    // Disable RX callback while transmitting
    lora_recv_async(dev, NULL, NULL);

    struct lora_modem_config cfg = {
        .frequency = 865100000,
        .bandwidth = BW_125_KHZ,
        .datarate = SF_12,
        .preamble_len = 8,
        .coding_rate = CR_4_5,
        .iq_inverted = false,
        .public_network = false,
        .tx_power = 14,
        .tx = true,                 // TX mode
    };

    int ret = lora_config(dev, &cfg);
    if (ret < 0)
    {
        LOG_ERR("Failed to configure TX: %d", ret);
    }
    return ret;
}

// ------------------------ Send Message ------------------------//

// High-level API to send a mesh message.
int mesh_send_msg(const struct device *dev, struct tx_msg_dyn *buffer)
{
    // Check payload length constraint
    if (buffer->len > MAX_MESH_PAYLOAD)
    {
        LOG_ERR("Payload too large (%zu > %d)", buffer->len, MAX_MESH_PAYLOAD);
        return -EINVAL;
    }

    // Remember this packet in duplicate cache
    add_to_cache(buffer->hdr.src, buffer->hdr.seq);

    // Compute CRC16 over header + length + payload
    uint16_t checksum = calc_checksum_crc16((uint8_t *)buffer,
                                            sizeof(struct mesh_hdr) + sizeof(size_t) + buffer->len);

    // Switch radio to TX mode                                        
    int ret = configure_tx(dev);
    if (ret < 0)
        return ret;

    // Build transmit buffer: header + length + payload + checksum
    size_t total_size = sizeof(struct mesh_hdr) + sizeof(size_t) + buffer->len + CHECKSUM_SIZE;
    uint8_t *send_buf = k_malloc(total_size);
    if (!send_buf)
        return -ENOMEM;

    memcpy(send_buf, buffer, sizeof(struct mesh_hdr) + sizeof(size_t) + buffer->len);
    memcpy(send_buf + sizeof(struct mesh_hdr) + sizeof(size_t) + buffer->len, &checksum, CHECKSUM_SIZE);

    // Perform LoRa transmission
    ret = lora_send(dev, send_buf, total_size);
    k_free(send_buf);

    if (ret < 0)
        LOG_ERR("lora_send failed: %d", ret);
    else
        LOG_INF("Sent packet src:0x%02x dst:0x%02x seq:%u ttl:%u checksum:0x%04X",
                buffer->hdr.src, buffer->hdr.dst, buffer->hdr.seq, buffer->hdr.ttl, checksum);

    // Switch back to RX mode after TX
    ret = configure_rx(dev);
    if (ret < 0)
        LOG_ERR("Failed to reconfigure RX after send");

    return ret;
}

// ------------------------ Receive Callback ------------------------//
// Callback called whenever a packet is received over LoRa
void mesh_receive_cb(const struct device *dev, uint8_t *data, uint16_t size,
                     int16_t rssi, int8_t snr, void *user_data)
{
    ARG_UNUSED(user_data);

    // Validate minimum packet size (header + len + checksum)
    if (size < sizeof(struct mesh_hdr) + sizeof(size_t) + CHECKSUM_SIZE)
        return;

    // Extract and verify checksum
    uint16_t received_checksum;
    memcpy(&received_checksum, data + size - CHECKSUM_SIZE, CHECKSUM_SIZE);

    if (calc_checksum_crc16(data, size - CHECKSUM_SIZE) != received_checksum)
        return;

    // Cast received data into mesh message format
    struct tx_msg_dyn *rx_msg = (struct tx_msg_dyn *)data;
    size_t payload_len = rx_msg->len;

    // Drop duplicates
    if (seen_before(rx_msg->hdr.src, rx_msg->hdr.seq))
        return;
    add_to_cache(rx_msg->hdr.src, rx_msg->hdr.seq);

    // Log packet details
    LOG_INF("Mesh RX src:0x%02x dst:0x%02x seq:%u ttl:%u RSSI:%d SNR:%d",
            rx_msg->hdr.src, rx_msg->hdr.dst, rx_msg->hdr.seq, rx_msg->hdr.ttl, rssi, snr);

     // If this node is the destination, deliver to application
    if (rx_msg->hdr.dst == NODE_ID)
    {
        if (receive_callback != NULL)
        {
            receive_callback(rx_msg->payload, payload_len);
        }
    }
    // Otherwise, forward if TTL > 1
    else if (rx_msg->hdr.ttl > 1)
    {
        struct tx_msg_dyn *fwd = k_malloc(sizeof(struct mesh_hdr) + sizeof(size_t) + payload_len);
        if (!fwd)
            return;
        fwd->hdr = rx_msg->hdr;
        fwd->hdr.ttl -= 1;                      // Decrement TTL
        fwd->len = payload_len;
        memcpy(fwd->payload, rx_msg->payload, payload_len);
        k_msgq_put(&tx_msgq, &fwd, K_NO_WAIT);  // Enqueue for transmission
    }
}

// ------------------------ TX Task ------------------------//
// Background thread that continuously sends messages from the TX queue
void tx_task(void *p1, void *p2, void *p3)
{
    const struct device *dev = DEVICE_DT_GET(DT_ALIAS(lora0));
    if (!device_is_ready(dev))
        return;

    struct tx_msg_dyn *msg;
    while (1)
    {
        // Block until a message is available in queue
        if (k_msgq_get(&tx_msgq, &msg, K_FOREVER) == 0)
        {
            mesh_send_msg(dev, msg);    // Send via LoRa
            k_free(msg);                // Free memory after sending
            k_sleep(K_MSEC(100));       // Small delay to prevent congestion
        }
    }
}

// ------------------------ Initialization ------------------------//
// Initialize the mesh subsystem
int mesh_init(const struct device *dev, mesh_receive_callback_t cb)
{
    if (!device_is_ready(dev))
        return -ENODEV;

    // Register application callback for received payloads
    receive_callback = cb;
    // Start background TX thread
    k_tid_t tid = k_thread_create(&transmit_thread, stack_area, STACK_SIZE,
                                  tx_task, NULL, NULL, NULL,
                                  PRIORITY, 0, K_NO_WAIT);
    k_thread_name_set(tid, "transmit_thread");
    return configure_rx(dev);
}

// ------------------------ Helper API ------------------------//
// Enqueue a message for transmission by TX task
int mesh_enqueue_tx(struct tx_msg_dyn *msg)
{
    return k_msgq_put(&tx_msgq, &msg, K_NO_WAIT);
}
