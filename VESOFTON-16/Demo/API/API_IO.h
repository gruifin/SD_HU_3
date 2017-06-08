/*******************************************************************************
 * Begin of file API_IO.h
 * Author: Wilmar van Dijk, Ludo Teirlinck en Jasper de Zoete
 *
 *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
 *
 * CPU: STM32F407
 * IDE: CooCox CoIDE 1.7.8
 *
 *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~**/
/** @file
 * @brief Common definition used by all files and public API.
 *
 ******************************************************************************/

//--------------------------------------------------------------
#ifndef __STM32F4_UB_VGA_SCREEN_H
#define __STM32F4_UB_VGA_SCREEN_H


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "misc.h"
#include "stm32f4xx_dma.h"
#include "User_Interface.h"

/**
 * @brief Pixel color black.
 *
 * The color value for a single pixel is stored in an 8-bit unsigned integer.
 * The @ref color_designation table specified how the three, red, green, and
 * blue, colors are stored.
 *
 * <table>
 *   <caption id="color_designation">Color Designation</caption>
 *   <tr>
 *     <th>Bit number</th>
 *     <td>7</td>
 *     <td>6</td>
 *     <td>5</td>
 *     <td>4</td>
 *     <td>3</td>
 *     <td>2</td>
 *     <td>1</td>
 *     <td>0</td>
 *   </tr>
 *   <tr>
 *     <td><b>Color</b></td>
 *     <td colspan="3" align="center">Red</td>
 *     <td colspan="3" align="center">Green</td>
 *     <td colspan="2" align="center">Blue</td>
 *   </tr>
 * </table>
 */
#define  VGA_COL_BLACK          0x00

/**
 * @brief Pixel color brown.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define	 VGA_COL_BROWN			0x88

/**
 * @brief Pixel color blue.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define  VGA_COL_BLUE           0x03

/**
 * @brief Pixel color light blue.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define	 VGA_COL_LIGHT_BLUE		0x6F

/**
 * @brief Pixel color gray.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define  VGA_COL_GRAY			0x92

/**
 * @brief Pixel color green.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define  VGA_COL_GREEN          0x1C

/**
 * @brief Pixel color light green.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define	 VGA_COL_LIGHT_GREEN	0x7E

/**
 * @brief Pixel color red.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define  VGA_COL_RED            0xE0

/**
 * @brief Pixel color light red.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define	 VGA_COL_LIGHT_RED		0xF2

/**
 * @brief Pixel white.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define  VGA_COL_WHITE          0xFF

/**
 * @brief Pixel color cyan.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define  VGA_COL_CYAN           0x1F

/**
 * @brief Pixel light cyan.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define	 VGA_COL_LIGHT_CYAN		0x9F

/**
 * @brief Pixel magenta.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define  VGA_COL_MAGENTA        0xE3

/**
 * @brief Pixel light magenta.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define  VGA_COL_LIGHT_MAGENTA	0xF3

/**
 * @brief Pixel color yellow.
 *
 * @see VGA_COL_BLACK for a description on how the color for a single pixel is
 * stored.
 */
#define  VGA_COL_YELLOW         0xFC

/**
 * Width of the VGA display
 */
#define VGA_DISPLAY_X   320

/**
 * Height of the VGA display
 */
#define VGA_DISPLAY_Y   240

/**
 * Size (string length) of the fill buffer
 */
#define STR_LENGTH 120

/**
 * Size of the type buffer
 */
#define TYPE_LENGTH 20

/**
 * Size of the color buffer
 */
#define COLOR_LENGTH 20

/**
 * Value of the carriage return char
 */
#define CRCHAR 13

/**
 * Value of the linefeed char
 */
#define LFCHAR 10

//--------------------------------------------------------------
// Timer-1
// Function  = Pixelclock (Speed for  DMA Transfer)
//
// basefreq = 2*APB2 (APB2=84MHz) => TIM_CLK=168MHz
// Frq       = 168MHz/1/12 = 14MHz
//
//--------------------------------------------------------------
#define VGA_TIM1_PERIODE      11
#define VGA_TIM1_PRESCALE      0

//--------------------------------------------------------------
// Timer-2
// Function  = CH4 : HSync-Signal on PB11
//             CH3 : Trigger point for DMA start
//
// basefreq = 2*APB1 (APB1=48MHz) => TIM_CLK=84MHz
// Frq       = 84MHz/1/2668 = 31,48kHz => T = 31,76us
// 1TIC      = 11,90ns
//
//--------------------------------------------------------------
#define  VGA_TIM2_HSYNC_PERIODE   2667
#define  VGA_TIM2_HSYNC_PRESCALE     0

#define  VGA_TIM2_HSYNC_IMP       320  // HSync-length (3,81us)
#define  VGA_TIM2_HTRIGGER_START  480  // HSync+BackPorch (5,71us)
#define  VGA_TIM2_DMA_DELAY        60  // ease the delay when DMA START (Optimization = none)
//#define  VGA_TIM2_DMA_DELAY        30  // ease the delay when DMA START (Optimization = -O1)

//--------------------------------------------------------------
// VSync-Signal
// Trigger   = Timer2 Update (f=31,48kHz => T = 31,76us)
// 1TIC      = 31,76us
//--------------------------------------------------------------
#define  VGA_VSYNC_PERIODE        525
#define  VGA_VSYNC_IMP  2
#define  VGA_VSYNC_BILD_START      36
#define  VGA_VSYNC_BILD_STOP      514   // (16,38ms)

//--------------------------------------------------------------
// Adress from PORTE (Reg ODR) callback DMA
// (see Page 53+204 of the Manual)
//
// Data-Bit0 => PE8
// Data-Bit7 => PE15
//--------------------------------------------------------------
#define VGA_GPIOE_BASE_ADR     ((uint32_t)0x40021000) // ADR from Port-E
#define VGA_GPIO_ODR_OFFSET    ((uint32_t)0x00000014) // ADR from Register ODR
#define VGA_GPIO_BYTE_OFFSET   ((uint32_t)0x00000001) // Data for 8bit
#define VGA_GPIOE_ODR_ADDRESS   (VGA_GPIOE_BASE_ADR | VGA_GPIO_ODR_OFFSET | VGA_GPIO_BYTE_OFFSET)

//--------------------------------------------------------------
// Define for black on PE8 - PE15
//--------------------------------------------------------------
#define VGA_GPIO_HINIBBLE  ((uint16_t)0xFF00) // GPIO_Pin_8 to GPIO_Pin_15

/** @brief Structure for the buffers  */
typedef struct {
	/** @brief	fill buffer  */
	char buff[STR_LENGTH];

	/** @brief	type of the  */
	char type[TYPE_LENGTH];
	uint8_t error;
}COMMAND_t;


/** @brief VGA structure  */
typedef struct {
	/** @brief	counter  */
	uint16_t hsync_cnt;

	/** @brief	start_adres  */
	uint32_t start_adr;

	/** @brief	Register constant CR-Register  */
	uint32_t dma2_cr_reg;
}VGA_t;
VGA_t VGA;

//--------------------------------------------------------------
// Display RAM
//--------------------------------------------------------------
uint8_t VGA_RAM1[(VGA_DISPLAY_X+1)*VGA_DISPLAY_Y];

/**
 * @brief Initialize VGA-Module
 */
void API_IO_Screen_Init(void);

/**
 * @brief Fill the DMA RAM buffer with one color
 * @param[in]	color		color in integer format
 */
void API_IO_FillScreen(uint8_t color);

/**
 * @brief Sets pixels on the screen with the chosen color
 * @param[in]	xp			horizontal position of the pixel
 * @param[in]	yp			vertical position of the pixel
 * @param[in]	color		color in integer format
 */
void API_IO_SetPixel(uint16_t xp, uint16_t yp, uint8_t color);

/**
 * @brief Initialize Delay
 */
void API_IO_Delay_Init(void);

/**
 * @brief Delays in microseconds
 */
void API_IO_DelayMicros(uint32_t micros);

/**
 * @brief Delays in milliseconds
 */
void API_IO_DelayMillis(uint32_t millis);

/**
 * @brief Initialize the UART
 */
void API_IO_UART_init(void);

/**
 * @brief Initialize the UART interrupt
 */
void API_IO_UART_INT_init(void);

/**
 * @brief UART writes a char
 * @params[in]	c		the char that has to be put
 */
void API_IO_UART_putchar(char c);

/**
 * @brief UART writes a string
 * @params[in]	s		the string that has to be put
 */
void API_IO_UART_puts(char *s);

/**
 * @brief UART writes an unsigned in given number system
 * @params[in]	num		the integer that has to be put
 * @params[in]	deel	the number system in which the integer has to put
 */
void API_IO_UART_putnum(unsigned int num, unsigned char deel);

/**
 * @brief UART writes an unsigned integer
 * @params[in]	num		the integer that has to be put
 */
void API_IO_UART_putint(unsigned int num);

/**
 * @brief UART receives incoming char
 */
char API_IO_UART_get(void);

/**
 * @brief UART receives incoming string
 * @params[in]	s		string that is received
 * @params[in]	echo	when True, send read-char to UART
 */
void API_IO_UART_gets(char *s, int echo);

//--------------------------------------------------------------
#endif // __STM32F4_UB_VGA_SCREEN_H
