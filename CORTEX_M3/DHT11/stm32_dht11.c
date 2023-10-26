#include "stm32_dht11.h"

static void DHT11_Delay(uint32_t delay);
static DHT11_StatusTypeDef DHT11_ReadBit(DHT11_HandleTypeDef *dht11, uint8_t *bit);

DHT11_StatusTypeDef DHT11_Init(DHT11_HandleTypeDef *dht11)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  // Enable GPIO clock
  if (dht11->GPIOx == GPIOA)
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
  }
  else if (dht11->GPIOx == GPIOB)
  {
    __HAL_RCC_GPIOB_CLK_ENABLE();
  }
  else if (dht11->GPIOx == GPIOC)
  {
    __HAL_RCC_GPIOC_CLK_ENABLE();
  }
  else if (dht11->GPIOx == GPIOD)
  {
    __HAL_RCC_GPIOD_CLK_ENABLE();
  }
  else if (dht11->GPIOx == GPIOE)
  {
    __HAL_RCC_GPIOE_CLK_ENABLE();
  }
  else if (dht11->GPIOx == GPIOF)
  {
    __HAL_RCC_GPIOF_CLK_ENABLE();
  }
  else if (dht11->GPIOx == GPIOG)
  {
    __HAL_RCC_GPIOG_CLK_ENABLE();
  }
  else
  {
    return DHT11_ERROR;
  }

  // Configure GPIO pin as output
  GPIO_InitStruct.Pin = dht11->GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(dht11->GPIOx, &GPIO_InitStruct);

  // Initialize the pin to high level
  HAL_GPIO_WritePin(dht11->GPIOx, dht11->GPIO_Pin, GPIO_PIN_SET);

  return DHT11_OK;
}

DHT11_StatusTypeDef DHT11_ReadData(DHT11_HandleTypeDef *dht11, uint8_t *humidity, uint8_t *temperature)
{
  uint8_t data[5] = {0};
  uint8_t i, j;

  // Start signal
  HAL_GPIO_WritePin(dht11->GPIOx, dht11->GPIO_Pin, GPIO_PIN_RESET);
  DHT11_Delay(18000);
  HAL_GPIO_WritePin(dht11->GPIOx, dht11->GPIO_Pin, GPIO_PIN_SET);
  DHT11_Delay(40);

  // Check response from DHT11
  if (HAL_GPIO_ReadPin(dht11->GPIOx, dht11->GPIO_Pin) != GPIO_PIN_RESET)
  {
    return DHT11_ERROR;
  }

  DHT11_Delay(80);

  // Check acknowledge from DHT11
  if (HAL_GPIO_ReadPin(dht11->GPIOx, dht11->GPIO_Pin) != GPIO_PIN_SET)
  {
    return DHT11_ERROR;
  }

  // Read data bits
  for (i = 0; i < 5; i++)
  {
    for (j = 0; j < 8; j++)
    {
      if (DHT11_ReadBit(dht11, &data[i]) != DHT11_OK)
      {
        return DHT11_TIMEOUT;
      }
    }
  }

  // Checksum verification
  if (data[0] + data[1] + data[2] + data[3] != data[4])
  {
    return DHT11_ERROR;
  }

  // Assign humidity and temperature values
  *humidity = data[0];
  *temperature = data[2];

  return DHT11_OK;
}

static void DHT11_Delay(uint32_t delay)
{
  uint32_t i;
  for (i = 0; i < delay; i++)
  {
    __NOP();
  }
}

static DHT11_StatusTypeDef DHT11_ReadBit(DHT11_HandleTypeDef *dht11, uint8_t *bit)
{
  uint32_t timeout = 0;

  // Set pin as output
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = dht11->GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(dht11->GPIOx, &GPIO_InitStruct);

  // Send start signal
  HAL_GPIO_WritePin(dht11->GPIOx, dht11->GPIO_Pin, GPIO_PIN_RESET);
  DHT11_Delay(50);
  HAL_GPIO_WritePin(dht11->GPIOx, dht11->GPIO_Pin, GPIO_PIN_SET);
  DHT11_Delay(30);

  // Set pin as input
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(dht11->GPIOx,dht11->GPIO_Pin, &GPIO_InitStruct);

  // Wait for response
  timeout = 0;
  while (HAL_GPIO_ReadPin(dht11->GPIOx, dht11->GPIO_Pin) == GPIO_PIN_RESET)
  {
    timeout++;
    if (timeout > DHT11_TIMEOUT_VALUE)
    {
      return DHT11_TIMEOUT;
    }
  }

  // Read the bit value
  timeout = 0;
  while (HAL_GPIO_ReadPin(dht11->GPIOx, dht11->GPIO_Pin) == GPIO_PIN_SET)
  {
    timeout++;
    if (timeout > DHT11_TIMEOUT_VALUE)
    {
      return DHT11_TIMEOUT;
    }
  }

  // Determine the bit value
  *bit = (timeout > DHT11_THRESHOLD_VALUE) ? 1 : 0;

  return DHT11_OK;
}