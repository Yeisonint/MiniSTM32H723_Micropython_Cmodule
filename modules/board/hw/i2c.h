#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "board.h"

// extern HAL_StatusTypeDef HAL_I2CEx_ConfigAnalogFilter(I2C_HandleTypeDef *hi2c, uint32_t AnalogFilter);
// extern HAL_StatusTypeDef HAL_I2CEx_DigitalFilter_Config(I2C_HandleTypeDef *hi2c, uint32_t AnalogFilter);
extern I2C_HandleTypeDef hi2c1;
void MX_I2C1_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

