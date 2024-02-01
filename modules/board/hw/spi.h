#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "board.h"

extern SPI_HandleTypeDef hspi4;

void MX_SPI4_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

