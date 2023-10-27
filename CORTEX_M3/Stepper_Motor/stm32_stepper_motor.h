/*
 * File: stm32_stepper_motor.h
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

#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <string.h>

#define     FORWARD         GPIO_PIN_SET
#define     BACKWARD        GPIO_PIN_RESET
#define     releaseMotor    GPIO_PIN_SET
#define     SELECTED        GPIO_PIN_SET

GPIO_TypeDef* dirPinPort;
uint16_t dirPin;
GPIO_TypeDef* stepPinPort;
uint16_t stepPin;
GPIO_TypeDef* enablePinPort;
uint16_t enablePin;
GPIO_TypeDef* MS1Port;
uint16_t MS1;
GPIO_TypeDef* MS2Port;
uint16_t MS2;
GPIO_TypeDef* MS3Port;
uint16_t MS3;

void delay_microseconds(uint32_t us);
void set_driver_type(char* driver);
void motor_setup(uint16_t stepPin, GPIO_TypeDef* stepPinPort, uint16_t dirPin, GPIO_TypeDef* dirPinPort, uint16_t enablePin, GPIO_TypeDef* enablePinPort, uint16_t MS1, GPIO_TypeDef* MS1Port, uint16_t MS2, GPIO_TypeDef* MS2Port, uint16_t MS3, GPIO_TypeDef* MS3Port);
void motorDirection(int Direction);
void setMicrostep(int microStep);
void step_motor(int steps, int delay_us);
void enable_motor();
void disable_motor();

#endif /* STEPPER_MOTOR_H */