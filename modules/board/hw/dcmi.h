#ifndef __DCMI_H__
#define __DCMI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "board.h"

extern DCMI_HandleTypeDef hdcmi;

void MX_DCMI_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DCMI_H__ */

