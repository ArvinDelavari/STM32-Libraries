#ifndef _RCC_H
#define _RCC_H 110

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
	
/**
 * @addtogroup STM32Fxxx_HAL_Libraries
 * @{
 */

/**
 * @defgroup RCC
 * @brief    RCC Library for STM32Fxxx - http://stm32f4-discovery.com/2015/07/hal-library-01-rcc-for-stm32fxxx/
 * @{
 *
 * RCC library provides initialization of clock at the beginning. Function @ref RCC_InitSystem should be called at beginning of @ref main function to initialize system.
 *
 * @note  In case of STM32F7xx is used, this library also enables CACHE for Instructions and Data.
 *
 * \par Changelog
 *
\verbatim
 Version 1.0
  - Initial release

 Version 1.1
  - October 10, 2015
  - Added support for STM32F469 devices
\endverbatim
 *
 * \par Dependencies
 *
\verbatim
 - STM32Fxxx HAL
 - defines.h
\endverbatim
 */
#include "stm32fxxx_hal.h"
#include "defines.h"

/**
 * @defgroup RCC_Macros
 * @brief    RCC Library macros
 * @{
 */

/* Set default values if not defined by user */
#if !defined(RCC_OSCILLATORTYPE) || !defined(RCC_PLLM) || !defined(RCC_PLLN) || !defined(RCC_PLLP) || !defined(RCC_PLLQ) 
#define RCC_OSCILLATORTYPE    RCC_OSCILLATORTYPE_HSE
#define RCC_PLLM              8
#define RCC_PLLN              360
#define RCC_PLLP              2
#define RCC_PLLQ              7
#endif

/**
 * @}
 */

/**
 * @defgroup RCC_Typedefs
 * @brief    RCC Typedefs used for RCC library for initialization purposes
 * @{
 */

/**
 * @brief  RCC result enumeration
 */
typedef enum {
	RCC_Result_Ok = 0x00, /*!< Everything OK */
	RCC_Result_Error      /*!< An error occurred */
} RCC_Result_t;

/**
 * @} RCC_Typedefs
 */

/**
 * @defgroup RCC_Functions
 * @brief    RCC Functions
 * @{
 */

/**
 * @brief  Initializes system clocks
 * @note   This function should be called on the start of main program
 * @note   When STM32F7xx target is used, D and I caches are also enabled with this function
 * @param  None
 * @retval RCC System status
 */
RCC_Result_t RCC_InitSystem(void);

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
