#include "stm32_potentiometer.h"

ADC_HandleTypeDef hadc1;

void Potentiometer_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;

  // Enable ADC clock
  __HAL_RCC_ADC1_CLK_ENABLE();

  // Configure ADC
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  // Configure ADC channel
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

uint16_t Potentiometer_Read(void)
{
  ADC_ChannelConfTypeDef sConfig;
  uint16_t adc_value = 0;

  // Start ADC conversion
  if (HAL_ADC_Start(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  // Wait for ADC conversion to complete
  if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) != HAL_OK)
  {
    Error_Handler();
  }

  // Read ADC value
  adc_value = HAL_ADC_GetValue(&hadc1);

  // Stop ADC conversion
  if (HAL_ADC_Stop(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  return adc_value;
}