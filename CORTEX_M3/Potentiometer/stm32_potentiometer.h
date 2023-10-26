#ifndef STM32_POTENTIOMETER_H
#define STM32_POTENTIOMETER_H

#include "stm32f1xx_hal.h"

void Potentiometer_Init(void);
uint16_t Potentiometer_Read(void);

#endif /* STM32_POTENTIOMETER_H */