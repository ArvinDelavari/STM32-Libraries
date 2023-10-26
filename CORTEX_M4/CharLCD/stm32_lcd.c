#include "stm32_lcd.h"

static void LCD_WriteNibble(uint8_t data);
static void LCD_WriteByte(uint8_t data, uint8_t rs);
static void LCD_Delay(uint32_t delay);

void LCD_Init(void)
{
  LCD_Delay(40);

  // Function Set: Set interface to 4-bit mode, 2-line display, 5x8 font
  LCD_WriteNibble(0x03);
  LCD_Delay(5);
  LCD_WriteNibble(0x03);
  LCD_Delay(1);
  LCD_WriteNibble(0x03);
  LCD_Delay(1);
  LCD_WriteNibble(0x02);

  // Display On/Off Control: Turn display on, cursor off, blink off
  LCD_WriteByte(0x0C, 0);
  LCD_Delay(1);

  // Entry Mode Set: Set text direction to increment, shift off
  LCD_WriteByte(0x06, 0);
  LCD_Delay(1);

  // Display Clear: Clear display and return cursor to home
  LCD_Clear();

  // Display Control: Set text direction to increment, shift off
  LCD_WriteByte(0x02, 0);
  LCD_Delay(1);
}

void LCD_Clear(void)
{
  LCD_WriteByte(0x01, 0);
  LCD_Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
  uint8_t offset = 0x40 * row + col;
  LCD_WriteByte(0x80 | offset, 0);
  LCD_Delay(1);
}

void LCD_WriteString(char *str)
{
  while (*str)
  {
    LCD_WriteByte(*str++, 1);
    LCD_Delay(1);
  }
}

static void LCD_WriteNibble(uint8_t data)
{
  HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

  HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);
  LCD_Delay(1);
  HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);
}

static void LCD_WriteByte(uint8_t data, uint8_t rs)
{
  HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, rs ? GPIO_PIN_SET : GPIO_PIN_RESET);

  LCD_WriteNibble((data >> 4) & 0x0F);
  LCD_WriteNibble(data & 0x0F);
}

static void LCD_Delay(uint32_t delay)
{
  uint32_t i;
  for (i = 0; i < delay; i++)
  {
    __NOP();
  }
}