#ifndef __MINISTM32H723_BOARD_H__
#define __MINISTM32H723_BOARD_H__
#ifdef __cplusplus
extern "C" {
#endif

// #define HAL_SPI_MODULE_ENABLED (1)
// #define HAL_SPI_MODULE_ENABLED

#include "stm32h723xx.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_spi.h"
#include "stm32h7xx_hal_gpio.h"

// DCMI - PINS
#define DCMI_D0_PIN     GPIO_PIN_6
#define DCMI_D1_PIN     GPIO_PIN_7
#define DCMI_D2_PIN     GPIO_PIN_0
#define DCMI_D3_PIN     GPIO_PIN_1
#define DCMI_D4_PIN     GPIO_PIN_4
#define DCMI_D5_PIN     GPIO_PIN_3
#define DCMI_D6_PIN     GPIO_PIN_5
#define DCMI_D7_PIN     GPIO_PIN_6
#define DCMI_VSYNC_PIN  GPIO_PIN_7
#define DCMI_HSYNC_PIN  GPIO_PIN_4
#define DCMI_PIXCLK_PIN GPIO_PIN_6
#define RCC_MCO_1_PIN   GPIO_PIN_8
#define I2C1_SCL_PIN    GPIO_PIN_8
#define I2C1_SDA_PIN    GPIO_PIN_9

// DCMI - PORTS
#define DCMI_D0_PORT     GPIOC
#define DCMI_D1_PORT     GPIOC
#define DCMI_D2_PORT     GPIOE
#define DCMI_D3_PORT     GPIOE
#define DCMI_D4_PORT     GPIOE
#define DCMI_D5_PORT     GPIOD
#define DCMI_D6_PORT     GPIOE
#define DCMI_D7_PORT     GPIOE
#define DCMI_VSYNC_PORT  GPIOB
#define DCMI_HSYNC_PORT  GPIOA
#define DCMI_PIXCLK_PORT GPIOA
#define RCC_MCO_1_PORT   GPIOA
#define I2C1_SCL_PORT    GPIOB
#define I2C1_SDA_PORT    GPIOB

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

// LED
#define LED_PIN  GPIO_PIN_3
#define LED_PORT GPIOE

// BUTTON
#define BUTTON_PIN  GPIO_PIN_13
#define BUTTON_PORT GPIOC

// ATTIBUTES
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static TIM_HandleTypeDef htim1;
static SPI_HandleTypeDef hspi4;
#pragma GCC diagnostic pop


// FUNCTIONS
void board_led_init(void);
void board_button_init(void);
uint8_t board_button_state(void);
void board_led_set(uint8_t);
void board_led_toggle(void);
uint8_t TFT_backlight_init(void);
uint8_t TFT_SPI_init(void);

#ifdef __cplusplus
}
#endif
#endif