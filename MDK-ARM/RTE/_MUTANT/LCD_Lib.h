/**
 * @author  Tilen Majerle
 * @email   tilen@majerle.eu
 * @website http://stm32f4-discovery.com
 * @link    http://stm32f4-discovery.com/2014/06/library-16-interfacing-hd44780-lcd-controller-with-stm32f4/
 * @version v1.2
 * @ide     Keil uVision
 * @license GNU GPL v3
 * @brief   HD44780 LCD driver library for STM32F4xx
 *	
@verbatim
   ----------------------------------------------------------------------
    Copyright (C) Tilen Majerle, 2015
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
		
		 * | Edited  By : Didi Alfandi 22/09/2021 (Roof-inno)
   ----------------------------------------------------------------------
@endverbatim
 */
#ifndef TM_HD44780_H
#define TM_HD44780_H 120
/**
 * @addtogroup TM_STM32F4xx_Libraries
 * @{
 */

/**
 * @defgroup TM_HD44780
 * @brief    HD44780 LCD driver library for STM32F4xx - http://stm32f4-discovery.com/2014/06/library-16-interfacing-hd44780-lcd-controller-with-stm32f4/
 * @{
 *
 *	It also supports all HD44780 compatible LCD drivers.
 *
 *	\par Default pinout
 *	
@verbatim
LCD		STM32F4XX		DESCRIPTION

GND		GND				Ground
VCC		+5V				Power supply for LCD
V0		Potentiometer	Contrast voltage. Connect to potentiometer
RS		PB2				Register select, can be overwritten in your project's defines.h file
RW		GND				Read/write
E			PB7				Enable pin, can be overwritten in your project's defines.h file
D0		-				Data 0 - doesn't care
D1		-				Data 1 - doesn't care
D2		-				Data 2 - doesn't care
D3		-				Data 3 - doesn't  care
D4		PC12			Data 4, can be overwritten in your project's defines.h file
D5		PC13			Data 5, can be overwritten in your project's defines.h file
D6		PB12			Data 6, can be overwritten in your project's defines.h file
D7		PB13			Data 7, can be overwritten in your project's defines.h file
A		+3V3			Back light positive power
K		GND				Ground for back light
@endverbatim	
 *	
 * If you want to change pinout, do this in your defines.h file with lines below and set your own settings:
 *	
@verbatim
//RS - Register select pin
#define HD44780_RS_PORT     GPIOB
#define HD44780_RS_PIN      GPIO_PIN_2
//E - Enable pin
#define HD44780_E_PORT      GPIOB
#define HD44780_E_PIN       GPIO_PIN_7
//D4 - Data 4 pin
#define HD44780_D4_PORT     GPIOC
#define HD44780_D4_PIN      GPIO_PIN_12
//D5 - Data 5 pin
#define HD44780_D5_PORT     GPIOC
#define HD44780_D5_PIN      GPIO_PIN_13
//D6 - Data 6 pin
#define HD44780_D6_PORT     GPIOB
#define HD44780_D6_PIN      GPIO_PIN_12
//D7 - Data 7 pin
#define HD44780_D7_PORT     GPIOB
#define HD44780_D7_PIN      GPIO_PIN_13
@endverbatim
 *
 * \par Changelog
 *
@verbatim
 Version 1.2
  - March 11, 2015
  - Added support for my new GPIO library

 Version 1.1
  - November 08, 2014
  - D6 and D7 default pins changed from PC14,15 to PB12,13, because RTC crystal is on PC14,15
 
 Version 1.0
  - First release
@endverbatim
 *
 * \par Dependencies
 *
@verbatim
 - STM32F4xx
 - STM32F4xx RCC
 - defines.h
@endverbatim
 */
#include "stm32f4xx.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
#include "stdbool.h"
//#include "defines.h"
//#include "tm_stm32f4_delay.h"
//#include "tm_stm32f4_gpio.h"

/**
 * @defgroup TM_HD44780_Macros
 * @brief    Library defines
 * @{
 */

/* 4 bit mode */
/* Control pins, can be overwritten */
/* RS - Register select pin */
#ifndef LCD_RS_PIN
#define LCD_RS_PORT				GPIOD
#define LCD_RS_PIN				GPIO_PIN_10
#endif
/* E - Enable pin */
#ifndef LCD_E_PIN
#define LCD_E_PORT				GPIOD
#define LCD_E_PIN					GPIO_PIN_11
#endif
/* Data pins */
/* D4 - Data 4 pin */
#ifndef LCD_D4_PIN
#define LCD_D4_PORT				GPIOD
#define LCD_D4_PIN				GPIO_PIN_12
#endif
/* D5 - Data 5 pin */
#ifndef LCD_D5_PIN
#define LCD_D5_PORT				GPIOD
#define LCD_D5_PIN				GPIO_PIN_13
#endif
/* D6 - Data 6 pin */
#ifndef LCD_D6_PIN
#define LCD_D6_PORT				GPIOD
#define LCD_D6_PIN				GPIO_PIN_14
#endif
/* D7 - Data 7 pin */
#ifndef LCD_D7_PIN
#define LCD_D7_PORT				GPIOD
#define LCD_D7_PIN				GPIO_PIN_15
#endif

#define GPIO_SetPinValue(GPIOx, GPIO_Pin, val)	((val) ? GPIO_SetPinHigh(GPIOx, GPIO_Pin) : GPIO_SetPinLow(GPIOx, GPIO_Pin))
#define GPIO_SetPinLow(GPIOx, GPIO_Pin)	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET)
#define GPIO_SetPinHigh(GPIOx, GPIO_Pin) HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET)
/**
 * @}
 */

/**
 * @defgroup TM_HD44780_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Initializes HD44780 LCD
 * @brief  cols: width of lcd
 * @param  rows: height of lcd
 * @retval None
 */
void LCD_Init(uint8_t cols, uint8_t rows);

/**
 * @brief  Turn display on
 * @param  None
 * @retval None
 */
void LCD_DisplayOn(void);

/**
 * @brief  Turn display off
 * @param  None
 * @retval None
 */
void LCD_DisplayOff(void);

/**
 * @brief  Clears entire LCD
 * @param  None
 * @retval None
 */
void LCD_Clear(void);

/**
 * @brief  Puts string on lcd
 * @param  x location
 * @param  y location
 * @param  *str: pointer to string to display
 * @retval None
 */
 
void LCD_CursorSet(uint8_t col, uint8_t row);
 
//void LCD_Puts(char* str);
void LCD_Puts(bool mode, char* str);
/**
 * @brief  Disable cursor blink
 * @param  None
 * @retval None
 */
 
void LCD_Putsxy(uint8_t x, uint8_t y, char* str);

/**
 * @brief  Enables cursor blink
 * @param  None
 * @retval None
 */
void LCD_BlinkOn(void);

/**
 * @brief  Disables cursor blink
 * @param  None
 * @retval None
 */
void LCD_BlinkOff(void);

/**
 * @brief  Shows cursor
 * @param  None
 * @retval None
 */
void LCD_CursorOn(void);

/**
 * @brief  Hides cursor
 * @param  None
 * @retval None
 */
void LCD_CursorOff(void);

/**
 * @brief  Scrolls display to the left
 * @param  None
 * @retval None
 */
void LCD_ScrollLeft(void);

/**
 * @brief  Scrolls display to the right
 * @param  None
 * @retval None
 */
void LCD_ScrollRight(void);

/**
 * @brief  Creates custom character
 * @param  location: Location where to save character on LCD. LCD supports up to 8 custom characters, so locations are 0 - 7
 * @param *data: Pointer to 8-bytes of data for one character
 * @retval None
 */
void LCD_CreateChar(uint8_t location, uint8_t* data);

/**
 * @brief  Puts custom created character on LCD
 * @param  location: Location on LCD where character is stored, 0 - 7
 * @retval None
 */
void LCD_PutCustom(uint8_t x, uint8_t y, uint8_t location);

/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @}
 */

#endif

