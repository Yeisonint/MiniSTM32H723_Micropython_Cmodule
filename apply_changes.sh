#!/bin/bash

rm -rf ./micropython/ports/stm32/boards/WEACTH723VG
cp -r ./MiniSTM32H723_Micropython_Port/WEACTH723VG ./micropython/ports/stm32/boards
# if [ ! -d "./micropython/ports/stm32/boards/WEACTH723VG" ]; then
#     echo "Copy MiniSTM32H723 board to stm32 boards in micropython"
#     cp -r ./MiniSTM32H723_Micropython_Port/WEACTH723VG ./micropython/ports/stm32/boards
# fi

# Apply some changes according to
if [ $(grep -ic "MICROPY_HW_RCC_OSPI_CLKSOURCE" ./micropython/ports/stm32/system_stm32.c) -eq 0 ]
then
echo "MICROPY_HW_RCC_OSPI_CLKSOURCE not found, adding patch"
awk 'NR==463{print "\n\
    #if defined(MICROPY_HW_RCC_OSPI_CLKSOURCE)\n\
    PeriphClkInitStruct.PeriphClockSelection |= RCC_PERIPHCLK_OSPI;\n\
    PeriphClkInitStruct.OspiClockSelection = MICROPY_HW_RCC_OSPI_CLKSOURCE;\n\
    #endif"}1' ./micropython/ports/stm32/system_stm32.c > ./tmp
mv ./tmp ./micropython/ports/stm32/system_stm32.c
fi

if [ $(grep -ic "STM32H7" ./micropython/ports/stm32/octospi.c) -eq 0 ]
then
echo "STM32H7 not found, adding patch"
sed '47,76d' ./micropython/ports/stm32/octospi.c > tmp
awk 'NR==47{print "    // Configure OCTOSPI pins (allows 1, 2, 4 or 8 line configuration).\n\
    #if defined(STM32H7)\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_CS, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPIM_P1_NCS);\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_SCK, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPIM_P1_CLK);\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO0, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPIM_P1_IO0);\n\
    #if defined(MICROPY_HW_OSPIFLASH_IO1)\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO1, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPIM_P1_IO1);\n\
    #if defined(MICROPY_HW_OSPIFLASH_IO2)\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO2, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPIM_P1_IO2);\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO3, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPIM_P1_IO3);\n\
    #if defined(MICROPY_HW_OSPIFLASH_IO4)\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO4, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPIM_P1_IO4);\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO5, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPIM_P1_IO5);\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO6, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPIM_P1_IO6);\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO7, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPIM_P1_IO7);\n\
    #endif\n\
    #endif\n\
    #endif\n\
    #else\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_CS, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPI1_NCS);\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_SCK, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPI1_CLK);\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO0, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPI1_IO0);\n\
    #if defined(MICROPY_HW_OSPIFLASH_IO1)\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO1, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPI1_IO1);\n\
    #if defined(MICROPY_HW_OSPIFLASH_IO2)\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO2, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPI1_IO2);\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO3, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPI1_IO3);\n\
    #if defined(MICROPY_HW_OSPIFLASH_IO4)\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO4, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPI1_IO4);\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO5, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPI1_IO5);\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO6, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPI1_IO6);\n\
    mp_hal_pin_config_alt_static_speed(MICROPY_HW_OSPIFLASH_IO7, MP_HAL_PIN_MODE_ALT, MP_HAL_PIN_PULL_NONE, MP_HAL_PIN_SPEED_VERY_HIGH, STATIC_AF_OCTOSPI1_IO7);\n\
    #endif\n\
    #endif\n\
    #endif\n\
    #endif\n\
\n\
    // Reset and turn on the OCTOSPI peripheral.\n\
    __HAL_RCC_OSPI1_CLK_ENABLE();\n\
    __HAL_RCC_OSPI1_FORCE_RESET();\n\
    __HAL_RCC_OSPI1_RELEASE_RESET();\n\
\n\
    // Configure the OCTOSPI peripheral.\n\
    #if defined(STM32H7)\n\
    OCTOSPI1->CR =\n\
        3 << OCTOSPI_CR_FTHRES_Pos // 4 bytes must be available to read/write\n\
            | 0 << OCTOSPI_CR_FSEL_Pos // FLASH 0 selected\n\
            | 0 << OCTOSPI_CR_DQM_Pos // dual-memory mode disabled\n\
    ;\n\
    #else\n\
    OCTOSPI1->CR =\n\
        3 << OCTOSPI_CR_FTHRES_Pos // 4 bytes must be available to read/write\n\
            | 0 << OCTOSPI_CR_MSEL_Pos // FLASH 0 selected\n\
            | 0 << OCTOSPI_CR_DMM_Pos // dual-memory mode disabled\n\
    ;\n\
    #endif"}1' ./tmp > ./tmp2
rm tmp
mv ./tmp2 ./micropython/ports/stm32/octospi.c
fi