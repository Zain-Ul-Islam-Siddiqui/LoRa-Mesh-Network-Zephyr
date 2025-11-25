# LoRa Mesh Network Using Zephyr RTOS
## Overview

Designed and implemented a fully functional LoRa-based mesh network capable of multi-hop wireless communication in remote, infrastructure-limited areas. Built a custom routing protocol with packet forwarding, TTL enforcement, duplicate suppression, and Zephyr-powered multitasking.

## Description
This project delivers a scalable LoRa mesh sensor network designed for rural, remote, and infrastructure-poor environments such as farmlands, conservation zones, and disaster-hit regions. Using STM32 Cortex-M4 MCUs, SX1276 LoRa radios, and Zephyr RTOS, I built a decentralized multi-hop protocol from scratch.

The mesh network features packet forwarding, duplicate-packet suppression, TTL-based loop prevention, and real-time scheduling through Zephyr. Point-to-point, one-hop, and multi-hop tests validated reliable communication up to 200 m indoors, with extended coverage through relays.

The gateway (ESP32 + LoRa module) aggregates multihop packets and pushes data to a cloud database.

## Key Features
- Custom multi-hop routing protocol
- TTL-based loop prevention
- Duplicate packet suppression (per-node cache)
- Zephyr RTOS task scheduling
- STM32-based nodes with SX1276 LoRa
- Multi-node indoor testing: 2-node, 3-node, and 5-node setups
- Real-world packet delivery ratio (~70% for 3-hop)

## Technologies
- Zephyr RTOS, STM32F401RE, SX1276, LoRa, C/C++, SPI, UART, Firebase
- Your Contribution
- End-to-end protocol design
- Firmware development in C (Zephyr)
- Custom packet structure (CRC16, header, payload)
- Multi-hop testing and system evaluation
- Hardware assembly + LoRa shield PCB

## Contribution
- End-to-end protocol design
- Firmware development in C (Zephyr)
- Custom packet structure (CRC16, header, payload)
- Multi-hop testing and system evaluation
- Hardware assembly + LoRa shield PCB

![Alt text](Nucleo.webp)
![Alt text](RFM95_Shield.jpg)
