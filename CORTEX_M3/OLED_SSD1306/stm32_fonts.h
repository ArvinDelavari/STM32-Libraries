#ifndef _FONTS_H
#define _FONTS_H 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup STM32Fxxx_HAL_Libraries
 * @{
 */

/**
 * @defgroup FONTS
 * @brief    Fonts library for all my LCD libraries
 * @{
 *
 * Default fonts library. It is used in all LCD based libraries.
 *
 * \par Supported fonts
 * 
 * Currently, these fonts are supported:
 *  - 7 x 10 pixels
 *  - 11 x 18 pixels
 *  - 16 x 26 pixels
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
 - string.h
\endverbatim
 */
#include "stm32fxxx_hal.h"
#include "defines.h"
#include "string.h"

/**
 * @defgroup FONTS_Typedefs
 * @brief    Library Typedefs
 * @{
 */

/**
 * @brief  Font structure used on my LCD libraries
 */
typedef struct {
	uint8_t FontWidth;    /*!< Font width in pixels */
	uint8_t FontHeight;   /*!< Font height in pixels */
	const uint16_t *data; /*!< Pointer to data font data array */
} FONT_t;

/** 
 * @brief  String width and height in unit of pixels 
 */
typedef struct {
	uint16_t Width;       /*!< String width in units of pixels */
	uint16_t Height;      /*!< String height in units of pixels */
} FONT_SIZE_t;

/**
 * @}
 */

/**
 * @defgroup FONTS_FontVariables
 * @brief    Library font variables
 * @{
 */

/**
 * @brief  7 x 10 pixels font size structure 
 */
extern FONT_t Font_7x10;

/**
 * @brief  11 x 18 pixels font size structure 
 */
extern FONT_t Font_11x18;

/**
 * @brief  16 x 26 pixels font size structure 
 */
extern FONT_t Font_16x26;

/**
 * @}
 */
 
/**
 * @defgroup FONTS_Functions
 * @brief    Library functions
 * @{
 */

/**
 * @brief  Calculates string length and height in units of pixels depending on string and font used
 * @param  *str: String to be checked for length and height
 * @param  *SizeStruct: Pointer to empty @ref FONTS_SIZE_t structure where informations will be saved
 * @param  *Font: Pointer to @ref FontDef_t font used for calculations
 * @retval Pointer to string used for length and height
 */
char* FONT_GetStringSize(char* str, FONT_SIZE_t* SizeStruct, FONT_t* Font);

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

