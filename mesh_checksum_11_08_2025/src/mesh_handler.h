#ifndef MESH_HANDLER_H
#define MESH_HANDLER_H

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <stdint.h>
#include <stddef.h>

// MACROS DEFINED IN HEADER FILE

#define NODE_ID 0x02
#define RECEIVER_ID 0x10

#define MAX_MESH_PAYLOAD 240
#define MAX_TTL 8
#define CACHE_SIZE 64
#define BROADCAST_INTERVAL_S 2
#define TX_QUEUE_LEN 4
#define CHECKSUM_SIZE sizeof(uint16_t)

#define STACK_SIZE 1024
#define PRIORITY 5

struct mesh_hdr
{
    uint8_t src;
    uint8_t dst;
    uint16_t seq;
    uint8_t ttl;
} __packed;

struct tx_msg_dyn
{
    struct mesh_hdr hdr;
    size_t len;
    uint8_t payload[]; // Flexible array member
};

typedef void (*mesh_receive_callback_t)(uint8_t *payload, size_t len);

// Initialize mesh module and LoRa device
int mesh_init(const struct device *dev, mesh_receive_callback_t cb);

// Send a message through mesh
int mesh_send_msg(const struct device *dev, struct tx_msg_dyn *msg);

// Enqueue a message for transmission (helper API)
int mesh_enqueue_tx(struct tx_msg_dyn *msg);

// Thread function for handling transmission
void tx_task(void *p1, void *p2, void *p3);

// LoRa receive callback
void mesh_receive_cb(const struct device *dev, uint8_t *data, uint16_t size,
                     int16_t rssi, int8_t snr, void *user_data);

#endif // MESH_HANDLER_H
