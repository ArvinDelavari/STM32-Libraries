#ifndef STM32_DHT11_H
#define STM32_DHT11_H

#include "stm32f1xx_hal.h"

typedef struct
{
  GPIO_TypeDef *GPIOx;
  uint16_t GPIO_Pin;
} DHT11_HandleTypeDef;

typedef enum
{
  DHT11_OK = 0,
  DHT11_ERROR = 1,
  DHT11_TIMEOUT = 2
} DHT11_StatusTypeDef;

DHT11_StatusTypeDef DHT11_Init(DHT11_HandleTypeDef *dht11);
DHT11_StatusTypeDef DHT11_ReadData(DHT11_HandleTypeDef *dht11, uint8_t *humidity, uint8_t *temperature);

#endif /* STM32_DHT11_H */