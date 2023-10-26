/*
 * File: stm32_POT.h
 * Description: ADC Potentiometer Library
 * Author: Arvin Delavari
 * 
 * This code is provided under an open source license and is free to use, modify, and distribute.
 * The specific license terms and conditions can be found in the accompanying LICENSE file.
 * 
 * Disclaimer:
 * This code is provided as-is, without any warranties or guarantees of any kind.
 * Users are responsible for understanding the code's functionality and behavior and testing it in their specific application.
 * The author and contributors are not liable for any damages or issues arising from the use of this code.
 */

#ifndef STM32_POT_H
#define STM32_POT_H

#include "stm32f1xx_hal.h"

void Potentiometer_Init(void);
uint16_t Potentiometer_Read(void);

#endif /* STM32_POT_H */