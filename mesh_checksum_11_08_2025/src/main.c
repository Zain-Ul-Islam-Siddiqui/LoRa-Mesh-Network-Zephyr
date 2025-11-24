#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "mesh_handler.h"

LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);

void payload_handler(uint8_t *payload, size_t len)
{
    LOG_HEXDUMP_INF(payload, len, "User callback received payload");    // Print the received data in hex format for debugging/logging
}

void main(void)
{
    const struct device *lora_dev = DEVICE_DT_GET(DT_ALIAS(lora0));

    if (mesh_init(lora_dev, payload_handler) < 0) // Initialize the mesh stack (configures RX, starts TX task, registers callback).
    {
        return;
    }

    LOG_INF("Mesh node starting (ID 0x%02x)", NODE_ID); // Log message showing that this node has started, printing its NODE_ID.

    uint16_t seq_counter = 0; // Sequence counter to uniquely identify packets from this node.
    /* 
    // If outside while (Receiver- transmits once)
    struct tx_msg_dyn *tx = k_malloc(sizeof(struct tx_msg_dyn) + MAX_MESH_PAYLOAD);
    if (!tx)
        return;

    tx->hdr.src = NODE_ID;          // Source node ID
    tx->hdr.dst = RECEIVER_ID;      // Destination node ID
    tx->hdr.seq = seq_counter++;    // Packet sequence number
    tx->hdr.ttl = MAX_TTL;          // Time-To-Live (max hops allowed)


    tx->len = snprintk((char *)tx->payload, MAX_MESH_PAYLOAD,   // Fill payload buffer with a message string
                       "Hello from node %d   ", NODE_ID);

    mesh_enqueue_tx(tx);    // Enqueue the message for transmission
    */
    /* 
    // Only  Receiver (Forwarder)
    int ret = configure_rx(lora_dev);
    if (ret < 0)
        LOG_ERR("Failed to reconfigure RX");
    */
    while (1)
    {
        // Transmit periodically
        struct tx_msg_dyn *tx = k_malloc(sizeof(struct tx_msg_dyn) + MAX_MESH_PAYLOAD);
        if (!tx)
            return;

        tx->hdr.src = NODE_ID;          // Current node’s ID as source
        tx->hdr.dst = RECEIVER_ID;      // Target node’s ID
        tx->hdr.seq = seq_counter++;    // Increment sequence number for uniqueness
        tx->hdr.ttl = MAX_TTL;          // Set maximum allowed hops


        tx->len = snprintk((char *)tx->payload, MAX_MESH_PAYLOAD, // Prepare payload (print a message into buffer)
                        "Hello from node %d   ", NODE_ID);

        mesh_enqueue_tx(tx);    // Enqueue prepared message into TX queue for transmission
        k_sleep(K_SECONDS(BROADCAST_INTERVAL_S));   // Sleep for BROADCAST_INTERVAL_S seconds before sending the next packet
    }
}
