# pcap-test

## Overview

`pcap-test` is a console application that captures TCP packets from a specified network interface and displays Ethernet, IP, TCP headers, and payload information. This application uses the `libpcap` library to perform packet capture.

## Requirements

- GCC compiler
- `libpcap` library

## Installation

You need to install the `libpcap` library first. On most Linux distributions, you can install it using the package manager.

```sh
sudo apt-get update
sudo apt-get install libpcap-dev
```

# Build

To build the project, use qmake and make.

1. Generate the Makefile using the .pro file.

```sh
qmake pcap-test.pro
```

2. Compile the project using 'make'

```sh
make
```

After building, the executable 'pcap-test' will be created.

# Usage

To run the program, you need to provide the name of the network interface as an argument. For example, to capture packets from the wireless network interface 'wlan0', run:
```sh
sudo ./pcap-test wlan0
```

Note: Packet capturing typically requires root privileges.

# Features

* Ethernet Header: Displays the source and destination MAC addresses.
* IP Header: Displays the source and destination IP addresses.
* TCP Header: Displays the source and destination ports.
* Payload: Displays the first 20 bytes of payload data in hexadecimal format.

# Example

```sh
sudo ./pcap-test eth0

96 bytes captured
src mac: 00:0c:29:6c:ba:40 -> dst mac: ff:ff:ff:ff:ff:ff
src ip: 192.168.1.10 -> dst ip: 192.168.1.255
src port: 12345 -> dst port: 80
Data: 48 65 6c 6c 6f 20 57 6f 72 6c 64 21 ...
```
# Contributing

If you would like to contribute to the project, please open an issue or submit a pull request.

# License

This project is licensed under th MIT License. See the LICENSE file for details
