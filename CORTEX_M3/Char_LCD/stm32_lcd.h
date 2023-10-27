/*
 * File: stm32_lcd.h
 * Description: 2x16 Character LCD Library
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

#ifndef STM32_LCD_H
#define STM32_LCD_H

#include "stm32f1xx_hal.h"

#define LCD_RS_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_0
#define LCD_EN_GPIO_Port GPIOA
#define LCD_EN_Pin GPIO_PIN_1
#define LCD_D4_GPIO_Port GPIOA
#define LCD_D4_Pin GPIO_PIN_2
#define LCD_D5_GPIO_Port GPIOA
#define LCD_D5_Pin GPIO_PIN_3
#define LCD_D6_GPIO_Port GPIOA
#define LCD_D6_Pin GPIO_PIN_4
#define LCD_D7_GPIO_Port GPIOA
#define LCD_D7_Pin GPIO_PIN_5

void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_WriteString(char *str);

#endif /* STM32_LCD_H */