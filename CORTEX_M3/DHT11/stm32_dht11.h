/*
 * File: stm32_dht11.h
 * Description: DHT11 Temperature and Humidity Sensor
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