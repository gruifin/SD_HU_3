/*******************************************************************************
 * Begin of file API_Draw.h
 * Author: Wilmar van Dijk, Ludo Teirlinck en Jasper de Zoete
 * Created on May 24, 2016, 04:27 PM
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
// Includes
//--------------------------------------------------------------
#include "main.h"

//--------------------------------------------------------------
// Defines
//--------------------------------------------------------------
#define ARRAY_X		32
#define ARRAY_Y		32

/**
 * @brief Converts incoming string into a integer
 * @param[in]	s			color given in string format
 * @retval		color		color in integer format
 */
int API_Draw_Color_To_Int(char *s);

/**
 * @brief Draws a line on the screen
 * @param[in]	x1			horizontal begin position of the line
 * @param[in]	y1			vertical begin position of the line
 * @param[in]	x2			horizontal end position of the line
 * @param[in]	y2			vertical end position of the line
 * @param[in]	weight		weight of the line
 * @param[in]	color		color of the line
 * @retval		error
 */
int API_Draw_Line(uint16_t x1, uint16_t y1,uint16_t x2,uint16_t y2,uint16_t width, uint8_t color);

/**
 * @brief Draws an Ellipse on the screen
 * @param[in]	xc			horizontal center position of the ellipse
 * @param[in]	yc			vertical center position of the ellipse
 * @param[in]	width		the width of the ellipse
 * @param[in]	height		the height of the ellipse
 * @param[in]	fill		fill ellipse if argument is true
 * @param[in]	color		color given in string format
 * @retval		error
 */
int API_Draw_Ellipse(uint16_t xc, uint16_t yc, uint16_t width, uint16_t height, uint8_t fill, uint8_t color);

/**
 * @brief Draws a rectangle on the screen
 * @param[in]	x1			horizontal begin position of the rectangle
 * @param[in]	y1			vertical begin position of the rectangle
 * @param[in]	x2			horizontal end position of the rectangle
 * @param[in]	y2			vertical end position of the rectangle
 * @param[in]	fill_empty	fill rectangle if argument is true
 * @param[in]	weight		weight of the rectangle
 * @param[in]	color		color given in string format
 * @retval		error
 */
int API_Draw_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t fill_empty, uint16_t width, uint8_t color);

/**
 * @brief Draws a triangle on the screen
 * @param[in]	x1			color given in string format
 * @param[in]	y1			color given in string format
 * @param[in]	x2			color given in string format
 * @param[in]	y2			color given in string format
 * @param[in]	x3			color given in string format
 * @param[in]	y3			color given in string format
 * @param[in]	fill_empty	color given in string format
 * @param[in]	color		color given in string format
 * @retval		error
 */
int API_Draw_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t fill_empty, uint8_t color);

/**
 * @brief Draws a bitmap on the screen
 * @param[in]	x_lo		color given in string format
 * @param[in]	y_lo		color given in string format
 * @param[in]	bitmap_id	color given in string format (table toevoegen van welke id welke bitmap is)
 * @retval		error
 */
int API_Draw_Bitmap(uint16_t x_lo, uint16_t y_lo, uint16_t bitmap_id);

/**
 * @brief Draws a Font on the screen
 * @param[in]	x			color given in string format
 * @param[in]	y			color given in string format
 * @param[in]	text		color given in string format
 * @param[in]	font_id		color given in string format
 * @param[in]	style		color given in string format
 * @param[in]	color		color given in string format
 * @retval		error
 */
void API_Draw_Font( uint16_t x, uint16_t y, char *text, char* font_id, uint8_t color, char* style);

/**
 * @brief Clears the screen with any given color
 * @param[in]	color		color given in string format
 * @retval		error
 */
int API_Draw_Clearscreen(uint8_t color);

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
int API_Draw_Wait(int time);

