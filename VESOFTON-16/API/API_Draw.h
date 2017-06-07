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
// Includes
//--------------------------------------------------------------
#include "main.h"

//--------------------------------------------------------------
// Defines
//--------------------------------------------------------------
#define ARRAY_X		32
#define ARRAY_Y		32

int API_Draw_Color_To_Int(char *s);
/**
 * @brief Converts incoming string into a integer
 * @param[in]	s			color given in string format
 * @retval		color		color in integer format
 */
int API_Draw_Line(uint16_t x1, uint16_t y1,uint16_t x2,uint16_t y2,uint16_t width, uint8_t color);
/**
 * @brief Draws an line on the screen
 * @param[in]	x1			color given in string format
 * @param[in]	y1			color given in string format
 * @param[in]	x2			color given in string format
 * @param[in]	y2			color given in string format
 * @param[in]	weight		color given in string format
 * @param[in]	color		color given in string format
 * @retval		error
 */
int API_Draw_Ellipse(uint16_t xc, uint16_t yc, uint16_t width,uint16_t height,uint8_t fill, uint8_t color);
// Doxygen documentatie
int API_Draw_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t fill_empty, uint16_t width, uint8_t color);
// Doxygen documentatie
int API_Draw_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3,uint8_t fill, uint8_t color);
// Doxygen documentatie
int API_Draw_Bitmap(uint16_t x_lo, uint16_t y_lo, uint16_t bitmap_id);
// Doxygen documentatie
void API_Draw_Font( uint16_t x, uint16_t y, char *text, char* font_id, uint8_t color, char* style);
// Doxygen documentatie
int API_Draw_Clearscreen(uint8_t color);
// Doxygen documentatie
int API_Draw_Wait(int time);
