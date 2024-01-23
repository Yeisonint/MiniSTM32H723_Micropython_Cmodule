#ifdef __cplusplus
extern "C" {
#endif

#include "ministm32h723_board.h"

void board_led_init(void){
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}

void board_led_set(uint8_t set){
    HAL_GPIO_WritePin(LED_PORT,LED_PIN,set>0?GPIO_PIN_SET:GPIO_PIN_RESET);
}

void board_led_toggle(){
    HAL_GPIO_TogglePin(LED_PORT,LED_PIN);
}

void board_button_init(void){
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BUTTON_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(BUTTON_PORT, &GPIO_InitStruct);
}

#ifdef __cplusplus
}
#endif