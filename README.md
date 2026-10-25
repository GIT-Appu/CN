# KTU Computer Networks Lab

Practical C programs and observation guides for the Computer Networks laboratory.

## Socket Programs

Each exercise is a short, top-level directory containing `client.c`, `server.c`,
and its own README:

- `basic-tcp` — TCP greeting exchange
- `matrix-tcp` — TCP matrix classification
- `chat-tcp` — TCP multi-user chat
- `basic-udp` — UDP greeting exchange
- `english-udp` — UDP informal-to-formal English converter
- `time-udp` — concurrent UDP time server
- `file-udp` — concurrent UDP file server
- `raw-socket` — Linux packet-header capture using a raw socket

## Prerequisites

- Linux/macOS with `gcc`
- Two terminal windows for each socket exercise
- Wireshark for packet analysis
- Cisco Packet Tracer for the routing exercise

Each example directory contains its own compile/run instructions. Use `127.0.0.1` when server and client run on the same computer. Change the IP address in a client when using two systems on the same LAN.

> **Note:** Packet Tracer topologies are normally supplied by the instructor. The Packet-Tracer section contains the required configuration commands for static routing, OSPF, and RIPv2 rather than prebuilt topology files.
