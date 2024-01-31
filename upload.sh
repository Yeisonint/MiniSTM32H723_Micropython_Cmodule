#!/bin/bash

cd ./micropython/ports/stm32
make BOARD=WEACTH723VG submodules
# make V=1 BOARD=WEACTH723VG USER_C_MODULES=../../../modules all deploy-stlink
st-flash write build-WEACTH723VG/firmware.bin 0x08000000
cd ../../..