#include <SPI.h>
#include <LoRa.h>
#include "GatewayFirebase.hpp"

#define WIFI_SSID "VM4204423"//VM4204423
#define WIFI_PASSWORD "cdxk5MyFmhdb"//cdxk5MyFmhdb
#define API_KEY "AIzaSyAKTTz2q61WZQ_wn8_gUM3xqqMDRLbz6cc"
#define USER_EMAIL "zain.siddiqui0071@gmail.com"
#define USER_PASSWORD "tuzaes006"
#define PROJECT_ID "lora-mesh-network-51116"
#define GATEWAY_ID 0x10
#define CACHE_SIZE 64
static struct recent_entry
{
    uint8_t src;
    uint16_t seq;
} recent_cache[CACHE_SIZE];

static int cache_idx;

FirebaseUploader uploader(WIFI_SSID, WIFI_PASSWORD, API_KEY,
                          USER_EMAIL, USER_PASSWORD, PROJECT_ID);

// Pin mapping
#define SCK 11
#define MISO 12
#define MOSI 10
#define SS 9
#define RST 18
#define DIO0 46

#define LORA_BAND 865100000

struct mesh_hdr {
  uint8_t src;
  uint8_t dst;
  uint16_t seq;
  uint8_t ttl;
} __attribute__((packed));

struct tx_msg_dyn {
  struct mesh_hdr hdr;
  size_t len;  // 4 bytes on ESP32
  uint8_t payload[];
};

// CRC16-CCITT (poly=0x1021, init=0x0000)
uint16_t calc_checksum_crc16(const uint8_t *data, size_t len) {
  uint16_t crc = 0x0000;
  for (size_t i = 0; i < len; i++) {
    crc ^= (uint16_t)data[i] << 8;
    for (uint8_t j = 0; j < 8; j++) {
      if (crc & 0x8000)
        crc = (crc << 1) ^ 0x1021;
      else
        crc <<= 1;
    }
  }
  return crc;
}

static bool seen_before(uint8_t src, uint16_t seq)
{
    for (int i = 0; i < CACHE_SIZE; i++)
    {
        if (recent_cache[i].src == src && recent_cache[i].seq == seq)
            return true;
    }
    return false;
}

static void add_to_cache(uint8_t src, uint16_t seq)
{
    recent_cache[cache_idx].src = src;
    recent_cache[cache_idx].seq = seq;
    cache_idx = (cache_idx + 1) % CACHE_SIZE;
}

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("LoRa Receiver with CRC16...");

  SPI.begin(SCK, MISO, MOSI);
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(LORA_BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }

  LoRa.setSpreadingFactor(12);
  LoRa.setCodingRate4(5);
  LoRa.setPreambleLength(8);
  LoRa.setSyncWord(0x12);
  LoRa.setSignalBandwidth(125E3);

  Serial.println("LoRa Receiver ready!");

  uploader.begin();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    uint8_t buf[512];
    int idx = 0;
    while (LoRa.available() && idx < sizeof(buf)) {
      buf[idx++] = (uint8_t)LoRa.read();
    }

    Serial.print("RSSI : ");
    Serial.println(LoRa.packetRssi());

    // Dump raw packet
    Serial.print("Raw packet: ");
    for (int i = 0; i < idx; i++) {
      Serial.printf("%02X ", buf[i]);
    }
    Serial.println();

    if (idx < sizeof(mesh_hdr) + sizeof(size_t) + 2) {
      Serial.println("Packet too short!");
      return;
    }

    tx_msg_dyn *msg = (tx_msg_dyn *)buf;

    size_t expected = sizeof(mesh_hdr) + sizeof(size_t) + msg->len + 2;  // +2 for CRC
    if (expected > (size_t)idx) {
      Serial.printf("Invalid length! expected=%u actual=%d\n",
                    (unsigned)expected, idx);
      return;
    }

    uint16_t checksum = calc_checksum_crc16(
      (uint8_t *)buf,
      sizeof(struct mesh_hdr) + sizeof(size_t) + msg->len);

    uint16_t rx_checksum;
    memcpy(&rx_checksum, ((uint8_t *)buf) + sizeof(struct mesh_hdr) + sizeof(size_t) + msg->len, sizeof(rx_checksum));

    if (checksum != rx_checksum) {
      Serial.printf("Checksum mismatch! Calc=0x%04X, Rx=0x%04X\n", checksum, rx_checksum);
      return;
    }

    if (seen_before(msg->hdr.src, msg->hdr.seq))
        return;
    add_to_cache(msg->hdr.src, msg->hdr.seq);

    if (msg->hdr.dst != GATEWAY_ID)
      return;

    // ✅ Print header
    Serial.printf("SRC: %u, DST: %u, SEQ: %u, TTL: %u, LEN: %u\n",
                  msg->hdr.src, msg->hdr.dst,
                  msg->hdr.seq, msg->hdr.ttl,
                  (unsigned)msg->len);

    // ✅ Print payload as hex
    Serial.print("Payload (hex): ");
    for (size_t i = 0; i < msg->len; i++) {
      Serial.printf("%02X ", msg->payload[i]);
    }
    Serial.println();
    msg->payload[msg->len] = '\0';

    // ✅ Print payload as ASCII (respecting length)
    Serial.print("Payload (ascii): ");
    Serial.println((char *)msg->payload);

    if (uploader.ready())
      uploader.pushPayload(msg->hdr.src, String((char*)msg->payload));
  }

  uploader.loop();  // keep Firebase running
}
