#ifndef __MINISTM32H723_BOARD_H__
#define __MINISTM32H723_BOARD_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h723xx.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_spi.h"
#include "stm32h7xx_hal_gpio.h"

// TFT-LCD PINS
#define LCD_SDA_PIN    GPIO_PIN_14
#define LCD_WR_RS_PIN  GPIO_PIN_13
#define LCD_SCL_PIN    GPIO_PIN_12
#define LCD_CS_PIN     GPIO_PIN_11
#define LCD_LED_PIN    GPIO_PIN_10
// #define LCD_RESET  SYS_RESET


// TFT-LCD PORTS
#define LCD_SDA_PORT    GPIOE
#define LCD_WR_RS_PORT  GPIOE
#define LCD_SCL_PORT    GPIOE
#define LCD_CS_PORT     GPIOE
#define LCD_LED_PORT    GPIOE
// #define LCD_RESET  SYS_RESET

// SPIx - PINS
#define SPIx_MISO_PIN GPIO_PIN_4
#define SPIx_MOSI_PIN GPIO_PIN_7
#define SPIx_CLK_PIN  GPIO_PIN_3
#define SPIx_CS_PIN   GPIO_PIN_6

// SPIx - PORTS
#define SPIx_MISO_PORT GPIOB
#define SPIx_MOSI_PORT GPIOD
#define SPIx_CLK_PORT  GPIOB
#define SPIx_CS_PORT   GPIOD

extern TIM_HandleTypeDef htim1;
extern SPI_HandleTypeDef hspi4;


// FUNCTIONS
uint8_t TFT_backlight_init(void);
uint8_t TFT_SPI_init(void);

#ifdef __cplusplus
}
#endif
#endif