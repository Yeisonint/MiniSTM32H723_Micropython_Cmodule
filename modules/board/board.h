#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32h7xx_hal.h"
#include "Legacy/stm32_hal_legacy.h"
#include "stm32h7xx_hal_def.h"
#include "stm32h7xx_hal_dcmi.h"
#include "stm32h7xx_hal_dma.h"
#include "stm32h7xx_hal_dma_ex.h"
#include "stm32h7xx_hal_gpio.h"
#include "stm32h7xx_hal_gpio_ex.h"
#include "stm32h7xx_hal_i2c.h"
#include "stm32h7xx_hal_i2c_ex.h"
#include "stm32h7xx_hal_spi.h"
#include "stm32h7xx_hal_spi_ex.h"
#include "stm32h7xx_hal_tim.h"
#include "stm32h7xx_hal_tim_ex.h"

#define TFT96

#define KEY_Pin GPIO_PIN_13
#define KEY_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_3
#define LED_GPIO_Port GPIOE
#define LCD_CS_Pin GPIO_PIN_11
#define LCD_CS_GPIO_Port GPIOE
#define LCD_WR_RS_Pin GPIO_PIN_13
#define LCD_WR_RS_GPIO_Port GPIOE

#ifdef TFT96
// QQVGA
#define FrameWidth 160
#define FrameHeight 120
#elif TFT18
// QQVGA2
#define FrameWidth 128
#define FrameHeight 160
#endif

// extern void FrameEvent(DCMI_HandleTypeDef *hdcmi);
// picture buffer
static uint16_t pic[FrameWidth][FrameHeight];
static volatile uint32_t DCMI_FrameIsReady = 0;
static uint32_t Camera_FPS=0;

void board_button_init(void);
uint8_t board_button_getstate(void);
void board_led_init(void);
void board_led_toggle(void);
void board_led_set(uint8_t set);

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif
