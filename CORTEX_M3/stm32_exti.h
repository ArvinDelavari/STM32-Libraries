#ifndef _EXTI_H
#define _EXTI_H 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup STM32Fxxx_HAL_Libraries
 * @{
 */

/**
 * @defgroup EXTI
 * @brief    External interrupts library for STM32Fxxx devices - http://stm32f4-discovery.com/2015/07/hal-library-4-exti-for-stm32fxxx/
 * @{
 *
 * This library allows you to easy enable external interrupt on specific pin.
 * 
 * You only need to specify GPIOx, pin and interrupt trigger you want to use and you are ready to use.
 * There are predefined function names that you use to handle this interrupts.
 * 
 * There are 16 external interrupts possible, GPIO lines 0 to 15.
 * Each GPIO_PIN_x from all GPIOx is connected to one line. In other words, PC0, PA0, PB0, PJ0,...
 * are all connected to line 0, and so on. But you can use only one pin for one line at a time.
 * So only PA0 at one time, or PD0 or PC0, but one a time.
 * 
 * You can still use more lines at the same time. So let's say PA0 is line0 and PC13 is line13.
 * This 2 interrupts can be used simultaneously without problems.
 *
 * \par Handling interrupts
 *
 * Next step is handling interrupts.
 * There are 16 interrupt lines, but only 7 interrupt handlers.
 * Lines0 to 4 have each own handler, then lines 5 to 9 have one common
 * and lines 10 to 15 have one common.
 * 
 * I write these functions in my library and use my own to handle specific line for you for easly.
 * Sometimes there is need for use default handler names in your own, but 2 functions with same name 
 * can not be used, so I made some settings.
 * 
 * If you open defines.h file and add any of lines below, you will disable handler line for interrupts.
 * By default, all handlers for lines are enabled. Disabled then with adding lines below in defines.h file:
 * 
\code
//These works for STM32F4xx and STM32F7xx series
//Disable EXTI0_IRQHandler function
#define EXTI_DISABLE_DEFAULT_HANDLER_0
//Disable EXTI1_IRQHandler function
#define EXTI_DISABLE_DEFAULT_HANDLER_1
//Disable EXTI2_IRQHandler function
#define EXTI_DISABLE_DEFAULT_HANDLER_2
//Disable EXTI3_IRQHandler function
#define EXTI_DISABLE_DEFAULT_HANDLER_3
//Disable EXTI4_IRQHandler function
#define EXTI_DISABLE_DEFAULT_HANDLER_4
//Disable EXTI9_5_IRQHandler function
#define EXTI_DISABLE_DEFAULT_HANDLER_9_5
//Disable EXTI15_10_IRQHandler function
#define EXTI_DISABLE_DEFAULT_HANDLER_15_10

//These works for STM32F0xx series
//Disable EXTI0_1_IRQHandler function
#define EXTI_DISABLE_DEFAULT_HANDLER_0_1
//Disable EXTI2_3_IRQHandler function
#define EXTI_DISABLE_DEFAULT_HANDLER_2_3
//Disable EXTI4_15_IRQHandler function
#define EXTI_DISABLE_DEFAULT_HANDLER_4_15
\endcode
 * 
 * If you need higher priority for external interrupts in NVIC, add lines below in defines.h file and edit them
\code
//Set custom NVIC priority
#define EXTI_NVIC_PRIORITY      0x04
\endcode
 *
 * \par Changelog
 *
\verbatim
 Version 1.0
  - First release
\endverbatim
 *
 * \par Dependencies
 *
\verbatim
 - STM32Fxxx HAL
 - defines.h
 - attributes.h
 - TM GPIO
\endverbatim
 */
#include "stm32fxxx_hal.h"
#include "attributes.h"
#include "defines.h"
#include "stm32_gpio.h"

/**
 * @defgroup EXTI_Macros
 * @brief    Library defines
 * @{
 */

/**
 * @brief  Default EXTI preemption priority for EXTI lines used in NVIC
 */
#ifndef EXTI_NVIC_PRIORITY
#define EXTI_NVIC_PRIORITY     0x03
#endif

 /**
 * @}
 */

/**
 * @defgroup EXTI_Typedefs
 * @brief    Library Typedefs
 * @{
 */

/**
 * @brief  Result enumeration
 */
typedef enum {
	EXTI_Result_Ok = 0x00, /*!< Everything ok */
	EXTI_Result_Error      /*!< An error has occured */
} EXTI_Result_t;

/**
 * @brief  Interrupt trigger enumeration	
 */
typedef enum {
	EXTI_Trigger_Rising = 0x00, /*!< Trigger interrupt on rising edge on line, pull down resistor active */
	EXTI_Trigger_Falling,       /*!< Trigger interrupt on falling edge on line, pull up resistor active */
	EXTI_Trigger_Rising_Falling /*!< Trigger interrupt on any edge on line, no pull resistor active */
} EXTI_Trigger_t;

/**
 * @}
 */

/**
 * @defgroup EXTI_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Attach external interrupt on specific GPIO pin 
 * @note   This function automatically enables the clock for GPIO peripheral and also sets pull resistors depending on trigger you use.
 * 	          - Falling edge: pull up is enabled
 * 	          - Rising edge: pull down is enabled
 * 	          - Any edge: no pull activated
 *
 * @note   You can attach only one GPIOx to specific GPIO_PIN.
 *         In other words, GPIO_PIN_5 can not be attached to GPIOA and GPIOB at the same time.
 *         If you will try that, my function will return error to you, because you have to detach GPIO_Line first and attach back on other GPIO port.
 *
 * @param  *GPIOx: GPIO port where you want EXTI interrupt line
 * @param  GPIO_Line: GPIO pin where you want EXTI interrupt line. Use OR (|) operator if you want to attach
 *            interrupt on more than one GPIO pin at the same GPIOx at the same time.
 * @param  trigger: Pin trigger source. This parameter can be a value of @ref EXTI_Trigger_t enumeration
 * @retval Attach result:
 *            - @arg EXTI_Result_Ok: Everything ok, interrupt attached
 *            - @arg EXTI_Result_Error: An error occurred, interrupt was not attached
 * @note   If you use more than one GPIO_Pin with OR (|) operator at single call and if GPIO_Pin can't be attached because
 *         there is already one GPIO_Pin at this line, function will return error and other pins might not be initialized.
 *         If function return @arg EXTI_Result_Ok, then all pins are attached correctly.
 */
EXTI_Result_t EXTI_Attach(GPIO_TypeDef* GPIOx, uint16_t GPIO_Line, EXTI_Trigger_t trigger);

/**
 * @brief  Detach GPIO pin from interrupt lines
 * @param  GPIO_Line: GPIO line you want to disable. Valid GPIO is GPIO_Pin_0 to GPIO_Pin_15. 
 *         Use OR (|) operator if you want to detach interrupt in more than one GPIO pin at the same GPIOx at the same time.
 * @retval Detaching result:
 *            - @arg EXTI_Result_Ok: Everything ok
 *            - @arg EXTI_Result_Error: An error occurred
 */
EXTI_Result_t EXTI_Detach(uint16_t GPIO_Line);

/**
 * @brief  Clears all interrupts on EXTI line
 * @note   It clears bits for external pins (bit 0 to bit 15) only!
 *         It has no effect for internally connected peripherals (like RTC) to EXTI line
 * @param  None
 * @retval None
 */
void EXTI_DeInit(void);

/**
 * @brief  Creates software interrupt for specific external GPIO line
 * @note   This also works for others EXTI lines from 16 to 23
 * @param  GPIO_Line: GPIO line where you want software interrupt
 * @retval None
 * @note   Defined as macro for faster execution
 */
#define EXTI_SoftwareInterrupt(GPIO_Line)	(EXTI->SWIER |= (GPIO_Line))

/**
 * @brief  EXTI Global handler
 * @note   This function is called from TM EXTI library each time any interrupt occurs on EXTI line.
 * @note   With __weak parameter to prevent link errors if not defined by user.
 * @param  GPIO_Pin: GPIO Line where interrupt occurred so you can identify what to do
 * @retval None
 */
void EXTI_Handler(uint16_t GPIO_Pin);

/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif
