//--------------------------------------------------------------
// File     : stm32_ub_vga_320x240.c
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.0
// Module   : GPIO, TIM, MISC, DMA
// Function : VGA out by GPIO (320x240 Pixel, 8bit color)
//
// signals  : PB11      = HSync-Signal
//            PB12      = VSync-Signal
//            PE8+PE9   = color Blue
//            PE10-PE12 = color Green
//            PE13-PE15 = color red
//
// uses     : TIM1, TIM2
//            DMA2, Channel6, Stream5
//--------------------------------------------------------------

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
#include "main.h"


//--------------------------------------------------------------
// color designation
// 8bit color (R3G3B2)
// Red   (3bit) -> Bit7-Bit5
// Green (3bit) -> Bit4-Bit2
// Blue  (2bit) -> Bit1-Bit0
//--------------------------------------------------------------
#define  VGA_COL_BLACK          0x00
#define	 VGA_COL_BROWN			0x88
#define  VGA_COL_BLUE           0x03
#define	 VGA_COL_LIGHT_BLUE		0x6F
#define  VGA_COL_GRAY			0x92
#define  VGA_COL_GREEN          0x1C
#define	 VGA_COL_LIGHT_GREEN	0x7E
#define  VGA_COL_RED            0xE0
#define	 VGA_COL_LIGHT_RED		0xF2
#define  VGA_COL_WHITE          0xFF

#define  VGA_COL_CYAN           0x1F
#define	 VGA_COL_LIGHT_CYAN		0x9F
#define  VGA_COL_MAGENTA        0xE3
#define  VGA_COL_LIGHT_MAGENTA	0xF3
#define  VGA_COL_YELLOW         0xFC

//--------------------------------------------------------------
// define the VGA_display
//--------------------------------------------------------------
#define VGA_DISPLAY_X   320
#define VGA_DISPLAY_Y   240

#define STR_LENGTH 120

#define TYPE_LENGTH 20

#define COLOR_LENGTH 20

#define CRCHAR 13 // carriage return char
#define LFCHAR 10 // linefeed char

typedef struct {
	char buff[STR_LENGTH];
	char type[TYPE_LENGTH];
	uint8_t error;
}COMMAND_t;


//--------------------------------------------------------------
// VGA Structure
//--------------------------------------------------------------
typedef struct {
  uint16_t hsync_cnt;   // counter
  uint32_t start_adr;   // start_adres
  uint32_t dma2_cr_reg; // Register constant CR-Register
}VGA_t;
VGA_t VGA;



//--------------------------------------------------------------
// Display RAM
//--------------------------------------------------------------
uint8_t VGA_RAM1[(VGA_DISPLAY_X+1)*VGA_DISPLAY_Y];



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

//--------------------------------------------------------------
// Global Function call
//--------------------------------------------------------------

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

void API_IO_DelayMicros(uint32_t micros);

void API_IO_DelayMillis(uint32_t millis);

void API_IO_UART_init(void);

void API_IO_UART_INT_init(void);

void API_IO_UART_putchar(char c);

void API_IO_UART_puts(char *s);

void API_IO_UART_putnum(unsigned int num, unsigned char deel);

void API_IO_UART_putint(unsigned int num);

char API_IO_UART_get(void);

void API_IO_UART_gets(char *s, int echo);

//--------------------------------------------------------------
#endif // __STM32F4_UB_VGA_SCREEN_H
