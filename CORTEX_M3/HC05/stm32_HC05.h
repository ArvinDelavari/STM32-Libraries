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