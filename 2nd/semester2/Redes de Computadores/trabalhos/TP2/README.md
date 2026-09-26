<div align="center">

# 🔍 Packet Sniffer

A real-time network packet capture and analysis tool written in **Python** using **Scapy**.

![Python](https://img.shields.io/badge/-Python-3776AB?style=for-the-badge\&logo=python\&logoColor=white)
![Scapy](https://img.shields.io/badge/-Scapy-white?style=for-the-badge\&logo=python\&logoColor=blue)

</div>

## 📖 About the Project

**Packet Sniffer** is a network traffic analysis tool developed in **Python** using the **Scapy** library.

The application captures network packets in real time and identifies different protocols, allowing the user to analyze network traffic directly from the command line.

The sniffer can be used both in a controlled **CORE** network environment and on a real network interface such as Wi-Fi or Ethernet.

## ✨ Features

The application provides several features for capturing and analyzing network traffic:

* 📡 **Live Capture** — Display packets in real time in the terminal.
* 📝 **File Logging** — Save captured packets to a file for later analysis.
* 🔍 **Protocol Detection** — Automatically identify protocols such as ARP, ICMP, TCP, IPv4, DHCP and Wi-Fi.
* 🧩 **IPv4 Fragmentation** — Detect and analyze fragmented IPv4 packets.
* 📊 **Protocol Analysis** — Analyze protocol-specific interactions and statistics.
* 🔎 **Interactive Analysis** — Inspect captured packets after the capture is finished.
* 🎯 **Filtering** — Filter traffic by protocol, IP address or MAC address.
* 📋 **Verbosity Control** — Choose between detailed and compact console output.

## 🌐 Protocol Analysis

The sniffer provides specific analysis for several network protocols:

| Protocol     | Analysis                                                                |
| ------------ | ----------------------------------------------------------------------- |
| 📡 **ICMP**  | Identifies Echo Requests and Replies and calculates RTT statistics.     |
| 🔗 **ARP**   | Detects request/reply pairs and analyzes address resolution.            |
| 🔌 **TCP**   | Tracks the three-way handshake and connection termination events.       |
| 📦 **DHCP**  | Groups messages by transaction ID and identifies the DORA sequence.     |
| 🌐 **IPv4**  | Detects and groups fragmented datagrams and tracks their reassembly.    |
| 📶 **Wi-Fi** | Classifies IEEE 802.11 frames and identifies active devices and BSSIDs. |

## ⚙️ Installation

The project requires **Python** and the **Scapy** library.

### 📦 Install Scapy

```bash
pip install scapy
```

## 🖥️ Usage

Before starting the sniffer, list the available network interfaces:

```bash
ip a
```

This allows you to identify the interface that should be used for packet capture, such as `eth0`, `wlan0` or `wlp62s0`.

### ▶️ Run the Sniffer

The general syntax is:

```bash
sudo python3 main.py -i <interface> -m <mode> -o <file> -v <verbosity>
```

### 📋 Available Arguments

| Argument      | Short | Values                | Default   | Description                                                   |
| ------------- | ----- | --------------------- | --------- | ------------------------------------------------------------- |
| `--interface` | `-i`  | Interface name        | Required  | Network interface used for packet capture.                    |
| `--mode`      | `-m`  | `live`, `log`, `both` | `live`    | Determines where captured packets are displayed or stored.    |
| `--output`    | `-o`  | File path             | `None`    | File used to store captured packets.                          |
| `--verbosity` | `-v`  | `verbose`, `compact`  | `verbose` | Controls the amount of information displayed in the terminal. |

## 💻 Examples

### 📡 Basic Capture

Capture packets and display them directly in the terminal:

```bash
sudo python3 main.py -i eth0
```

### 📝 Save Packets to a File

Capture packets and save them to a file:

```bash
sudo python3 main.py -i eth0 -m log -o captura.txt
```

### 📡📝 Console and File Capture

Display packets in the terminal while also saving them to a file:

```bash
sudo python3 main.py -i wlan0 -m both -o captura.txt
```

### ⚡ Compact Mode

Use compact output for a less detailed display:

```bash
sudo python3 main.py -i wlan0 -m both -o captura.txt -v compact
```

## 🔎 Interactive Analysis

After stopping the packet capture with `Ctrl+C`, the application enters an **interactive analysis mode**.

| Command               | Description                                      |
| --------------------- | ------------------------------------------------ |
| `tcp`                 | Display captured TCP packets.                    |
| `dhcp`                | Display captured DHCP packets.                   |
| `icmp`                | Display captured ICMP packets.                   |
| `ipv4`                | Display captured IPv4 packets.                   |
| `wifi`                | Display captured Wi-Fi packets.                  |
| `arp`                 | Display captured ARP packets.                    |
| `status <protocol>`   | Display detailed statistics for a protocol.      |
| `fragments ipv4`      | Display detailed IPv4 fragmentation information. |
| `filter ip <IP>`      | Filter traffic for a specific IP address.        |
| `filter proto <NAME>` | Filter packets by protocol.                      |
| `filter mac <MAC>`    | Filter traffic for a specific MAC address.       |

## 🌐 Running the Sniffer

The project can be used in different network environments.

### 🧪 CORE Environment

The sniffer can be executed inside a **CORE** network node:

```bash
sudo python3 main.py -i eth0
```

Traffic can then be generated from other nodes using commands such as:

```bash
ping <destination_ip>
```

or:

```bash
nc <destination_ip> <port>
```

### 💻 Local Machine

The sniffer can also be executed directly on a computer using an active network interface:

```bash
sudo python3 main.py -i <your_interface> -m live -v compact
```

Traffic can be generated through normal network activity or commands such as `ping`.

## 🛠️ Technologies

* 🐍 **Python** — Main programming language.
* 🕵️ **Scapy** — Packet capture and network protocol analysis.
* 💻 **Command-Line Interface (CLI)** — User interaction and packet analysis.
* 🌐 **CORE** — Network emulation and testing environment.

## 📁 Project Structure

```text
.

├── packet_sniffer/     # Application source code
├── relatorio/          # Project report
└── README.md           # Project documentation
```

## 🎯 Objective

The main objective of the project is to develop a network packet sniffer capable of **capturing, identifying and analyzing network traffic** in real time.

The project applies concepts related to **computer networks, network protocols, packet analysis, traffic filtering and protocol behavior**, providing a practical way to inspect and understand network communications.

---
