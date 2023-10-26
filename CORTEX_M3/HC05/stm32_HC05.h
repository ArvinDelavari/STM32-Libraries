/*
 * File: stm32_HC05.h
 * Description: HC05 UART Driven Bluetooth module
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

#ifndef STM32_HC05_H_
#define STM32_HC05_H_

#include "stm32f1xx_hal.h"
#include <stdbool.h>

#define HC05_UART huart1 // Modify this to match your UART peripheral

typedef struct 
{
  UART_HandleTypeDef *huart;
  bool initialized;
} HC05_HandleTypeDef;

typedef enum 
{
  HC05_OK,
  HC05_ERROR,
  HC05_TIMEOUT
} HC05_StatusTypeDef;

void HC05_Init(HC05_HandleTypeDef *hc05);
HC05_StatusTypeDef HC05_SendCommand(HC05_HandleTypeDef *hc05, const char *command);
HC05_StatusTypeDef HC05_SetBaudRate(HC05_HandleTypeDef *hc05, uint32_t baudRate);
HC05_StatusTypeDef HC05_SetDeviceName(HC05_HandleTypeDef *hc05, const char *name);
HC05_StatusTypeDef HC05_SetDevicePin(HC05_HandleTypeDef *hc05, const char *pin);
HC05_StatusTypeDef HC05_EnterCommandMode(HC05_HandleTypeDef *hc05);
HC05_StatusTypeDef HC05_ExitCommandMode(HC05_HandleTypeDef *hc05);
HC05_StatusTypeDef HC05_Reset(HC05_HandleTypeDef *hc05);

#endif /* STM32_HC05_H_ */