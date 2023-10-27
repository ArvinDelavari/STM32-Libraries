/*
 * File: stm32_stepper_motor.c
 * Description: Stepper motor library written for A4988/LV8729/TB6600 and other similar drivers 
 * which can operate from 1 to 128 microsteps
 * 
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

#include "stm32_stepper_motor.h"

TIM_HandleTypeDef htim;

// Microsecond delay function
void delay_microseconds(uint32_t us)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = us - 1;

  while ((HAL_GetTick() - tickstart) < wait) { /* wait */}
}

char*   driver;
uint8_t microStep;
uint8_t A4988  = 0;
uint8_t TB6600 = 0;
uint8_t LV8729 = 0; 

void set_driver_type (char* driver)
{
  if (strcmp(driver, "A4988") == 0)
  {
    A4988  = GPIO_PIN_SET;
    TB6600 = GPIO_PIN_RESET;
    LV8729 = GPIO_PIN_RESET;
  }
  else if (strcmp(driver, "TB6600") == 0)
  {
    TB6600 = GPIO_PIN_SET;
    A4988  = GPIO_PIN_RESET;
    LV8729 = GPIO_PIN_RESET;
  }
  else if (strcmp(driver, "LV8729") == 0)
  {
    LV8729 = GPIO_PIN_SET;
    A4988  = GPIO_PIN_RESET;
    TB6600 = GPIO_PIN_RESET;
  }
}

void motor_setup (uint16_t stepPin, GPIO_TypeDef* stepPinPort, uint16_t dirPin, GPIO_TypeDef* dirPinPort, uint16_t enablePin, GPIO_TypeDef* enablePinPort, uint16_t MS1, GPIO_TypeDef* MS1Port, uint16_t MS2, GPIO_TypeDef* MS2Port, uint16_t MS3, GPIO_TypeDef* MS3Port)
{
  dirPinPort    = dirPinPort;
  dirPin        = dirPin;
  stepPinPort   = stepPinPort;
  stepPin       = stepPin;
  enablePinPort = enablePinPort;
  enablePin     = enablePin;
  MS1Port       = MS1Port;
  MS1           = MS1;
  MS2Port       = MS2Port;
  MS2           = MS2;
  MS3Port       = MS3Port;
  MS3           = MS3;
  
  HAL_GPIO_WritePin(dirPinPort, dirPin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(stepPinPort, stepPin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(enablePinPort, enablePin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MS1Port, MS1, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MS2Port, MS2, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MS3Port, MS3, GPIO_PIN_RESET);
}

void motor_direction(int Direction)
{
  HAL_GPIO_WritePin(dirPinPort, dirPin, (GPIO_PinState)Direction);
}

void setMicrostep(int microStep)
{
  if (A4988 == SELECTED || TB6600 == SELECTED)
  {
    if (microStep == 1)
    {
      HAL_GPIO_WritePin(MS1Port, MS1, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MS2Port, MS2, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MS3Port, MS3, GPIO_PIN_RESET);
      printf("Move Mode: Full-Step\n");
    }
    else if (microStep == 2)
    {
      HAL_GPIO_WritePin(MS1Port, MS1, GPIO_PIN_SET);
      HAL_GPIO_WritePin(MS2Port, MS2, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MS3Port, MS3, GPIO_PIN_RESET);
      printf("Move Mode: 1/2-Step\n");
    }
    else if (microStep == 4)
    {
      HAL_GPIO_WritePin(MS1Port, MS1, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MS2Port, MS2, GPIO_PIN_SET);
      HAL_GPIO_WritePin(MS3Port, MS3, GPIO_PIN_RESET);
      printf("Move Mode: 1/4-Step\n");
    }
    else if (microStep == 8)
    {
      HAL_GPIO_WritePin(MS1Port, MS1, GPIO_PIN_SET);
      HAL_GPIO_WritePin(MS2Port, MS2, GPIO_PIN_SET);
      HAL_GPIO_WritePin(MS3Port, MS3, GPIO_PIN_RESET);
      printf("Move Mode: 1/8-Step\n");
    }
    else if (microStep == 16)
    {
      HAL_GPIO_WritePin(MS1Port, MS1, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MS2Port, MS2, GPIO_PIN_SET);
      HAL_GPIO_WritePin(MS3Port, MS3, GPIO_PIN_SET);
      printf("Move Mode: 1/16-Step\n");
    }
    else
    {
      printf("Invalid microstep value!\n");
    }
  }
  else if (LV8729 == SELECTED)
  {
    // Handle microstep setting for LV8729 driver
    // You can implement the specific logic for the LV8729 driver here
  }
  else
  {
    printf("No driver selected!\n");
  }
}

void step_motor(int steps, int delay_us)
{
  GPIO_PinState direction = (steps > 0) ? FORWARD : BACKWARD;
  steps = abs(steps);
  HAL_GPIO_WritePin(dirPinPort, dirPin, direction);
  for (int i = 0; i < steps; i++)
  {
    HAL_GPIO_WritePin(stepPinPort, stepPin, GPIO_PIN_SET);
    delay_microseconds(delay_us);
    HAL_GPIO_WritePin(stepPinPort, stepPin, GPIO_PIN_RESET);
    delay_microseconds(delay_us);
  }
}

void enable_motor()
{
  HAL_GPIO_WritePin(enablePinPort, enablePin, GPIO_PIN_RESET);
  printf("Motor Enabled\n");
}

void disable_motor()
{
  HAL_GPIO_WritePin(enablePinPort, enablePin, GPIO_PIN_SET);
  printf("Motor Disabled\n");
}