#!/bin/sh

cd esp-open-sdk
make STANDALONE=y
echo 'Path added to .profile and PATH var'

PATH_ESP_OPEN_SDK=$(pwd)
echo $PATH_ESP_OPEN_SDK
echo 'PATH=$PATH:'$PATH_ESP_OPEN_SDK'/xtensa-lx106-elf/bin' >> ~/.profile
echo 'PATH=$PATH:'$PATH_ESP_OPEN_SDK'/esptool'  >> ~/.profile
PATH=$PATH':'$PATH_ESP_OPEN_SDK'/xtensa-lx106-elf/bin'
PATH=$PATH':'$PATH_ESP_OPEN_SDK'/esptool'

