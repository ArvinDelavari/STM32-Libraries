#define STM32F1xx
/* 4 bit mode */
/* Control pins, can be overwritten */
/* RS - Register select pin */
#ifndef HD44780_RS_PIN
#define HD44780_RS_PORT                GPIOA
#define HD44780_RS_PIN                GPIO_PIN_1
#endif
/* E - Enable pin */
#ifndef HD44780_E_PIN
#define HD44780_E_PORT                GPIOA
#define HD44780_E_PIN                GPIO_PIN_11
#endif
/* Data pins */
/* D4 - Data 4 pin */
#ifndef HD44780_D4_PIN
#define HD44780_D4_PORT                GPIOA
#define HD44780_D4_PIN                GPIO_PIN_4
#endif
/* D5 - Data 5 pin */
#ifndef HD44780_D5_PIN
#define HD44780_D5_PORT                GPIOA
#define HD44780_D5_PIN                GPIO_PIN_5
#endif
/* D6 - Data 6 pin */
#ifndef HD44780_D6_PIN
#define HD44780_D6_PORT                GPIOA
#define HD44780_D6_PIN                GPIO_PIN_6
#endif
/* D7 - Data 7 pin */
#ifndef HD44780_D7_PIN
#define HD44780_D7_PORT                GPIOA
#define HD44780_D7_PIN                GPIO_PIN_7
#endif
