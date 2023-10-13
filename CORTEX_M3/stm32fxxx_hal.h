#ifndef _STM32Fxxx_H
#define _STM32Fxxx_H

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup STM32Fxxx_HAL_Libraries
 */

/**

 * \par Libraries structure
 *
 * Each library is structured in the same way where you have these parts:
 *  - Header file:
 *    - Library description with link on website
 *    - Includes section
 *    - Defines section for different configurations in library
 *    - Enumerations and structures section
 *    - Function declaration section
 *  - Source file:
 *    - Function implementations
 *
 * Each library includes at least these 2 files:
 *  - stm32fxxx_hal.h file:
 *    This file was done by me for better organization between several STM32 families to use with my libraries for future use.
 *    It sets some basic defines, which can also be set using compiler's preprocessor defines. Check file for more information with detailed description.
 *
 *  - defines.h file:
 *    <b>This file is totally based on user and should also be created by user</b>.
 *
 *    It is used for library configuration settings, so you don't have to edit library file. 
 *    If you edit library file, then if new version is out, it will be overwritten what you don't wanna have.
 *
 *    Check example below for meaning.
 *
\code
//------------------------------------
//tm_stm32_exti.h file:
//------------------------------------
//Content in this file is similar to this below:

//Include defines.h file for user configuration
#include "defines.h"

//Set default NVIC preemption priority if not defined by user to 0x03
#ifndef EXTI_NVIC_PRIORITY
#define EXTI_NVIC_PRIORITY     0x03
#endif

//------------------------------------
//defines.h file: (set by user)
//------------------------------------

//User wants to change that, use defines.h file like this:
#ifndef DEFINES_FILE
#define DEFINES_FILE

//Let's set EXTI NVIC preemption priority to highest, so we will do:
#define EXTI_NVIC_PRIORITY    0x00

#endif
\endcode
 *
 * Code above shows how you can use defines.h file to change default library settings.
 *
 * \par HAL Source from ST
 *
 * TM HAL libraries works on STM32Cube provided from ST and are not included in package of libraries.
 *
 * @note  You have to go to ST website and download STM32Cube package for your family and use that STM32Fxxx_HAL_Drivers libraries in your project together with my libraries.
 *        On my Github, you have example how they are used together.
 *
 * \par About defines.h file
 *
 * Please check above about this.
 *
 */

/**
 * @defgroup HAL_Family
 * @brief    In stm32fxxx_hal.h file you have to specify STM32 family used for HAL drivers.
 * @{
 */

/* Defines for family used with libraries */
/* Uncomment line for your family used with HAL libraries */
//#define STM32F0xx /*!< Use STM32F0xx libraries */
//#define STM32F4xx /*!< Use STM32F4xx libraries */
//#define STM32F7xx /*!< Use STM32F7xx libraries */

/**
 * @}
 */

/* Include project config file */
#include "defines.h"

/* Check if HAL drivers enabled */
#ifndef USE_HAL_DRIVER
#define USE_HAL_DRIVER
#endif

/* Include proper header file */
/* STM32F7xx */
/*
#if defined(STM32F0xx) || defined(STM32F0XX)
#ifndef STM32F0xx
#define STM32F0xx
#endif
#ifndef STM32F0XX
#define STM32F0XX
#endif
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"
#endif
*/
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
/* STM32F4xx */
/*#if defined(STM32F4xx) || defined(STM32F4XX)
#ifndef STM32F4xx
#define STM32F4xx
#endif
#ifndef STM32F4XX
#define STM32F4XX
#endif
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#endif
*/
/* STM32F7xx */
/*#if defined(STM32F7xx) || defined(STM32F7XX)
#ifndef STM32F7xx
#define STM32F7xx
#endif
#ifndef STM32F7XX
#define STM32F7XX
#endif
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#endif
*/
/* Check if anything defined */
/*
#if !defined(STM32F0xx) && !defined(STM32F4xx) && !defined(STM32F7xx)
#error "There is not selected STM32 family used. Check stm32fxxx_hal.h file for configuration!"
#endif*/
/* Init main libraries used everywhere */
#include "defines.h"
#include "stm32_rcc.h"
#include "stm32_gpio.h"

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
