# ESP8266_Transparent_SPI_UART_mode 

Version 0.1

## Overview

A simple Aplication for ESP8266 to make a Transparent mode for SPI and UART.

It is designed to send Data from a SPI bus to an UDP server and a TCP Server is used to Recieve or transmit slow command with control.

The ESP8266_Transparent_SPI_UART_mode is designed to provide maximum of the bandwith for emission of trace from a Robot


## Supported hardware

### ESP8266

The src is compatible with most of the ESP8266 modules & ESP8266 development boards.

### Serial

For Serial communications, the library has been tested with the direct USB serial connection on an USB communication and STM32DiscoveryF4

## Requirements

you need the latest toolchain of pfalcon: https://github.com/pfalcon/esp-open-sdk
and for flash the esp8266
for debian distribution go to in esp-open-sdk directory
```
$ wget -O esptool_0.0.2-1_i386.deb https://github.com/esp8266/esp8266-wiki/raw/master/deb/esptool_0.0.2-1_i386.deb
$ sudo dpkg -i esptool_0.0.2-1_i386.deb
$ rm esptool_0.0.2-1_i386.deb
```

## Dependances
- autoconf
- build-essential 
- gperf
- bison
- flex
- texinfo
- libtool
- libncurses5-dev 
- wget
- gawk
- libc6-dev-amd64
- python-serial
- libexpat-dev unzip

