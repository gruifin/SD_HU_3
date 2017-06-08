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
#include "API_IO.h"






typedef struct
{
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;
	uint8_t width;
	uint8_t colint;

}LINE;

typedef struct
{
	uint16_t xp;
	uint16_t yp;
	uint16_t width;
	uint16_t height;
	uint8_t fill;
	uint8_t	colint;
}ELLIPSE;

typedef struct
{
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;
	uint16_t x3;
	uint16_t y3;
	uint8_t fill;
	uint8_t colint;
}TRIANGLE;

typedef struct
{
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;
	uint16_t fill;
	uint8_t colint;
}SQUARE;

typedef struct
{
	char buff[200];
	uint16_t x;
	uint16_t y;
	char text[200];
	char font[20];
	char style[20];
	uint8_t colint;
}TEXT;

typedef struct
{
	uint16_t x;
	uint16_t y;
	uint16_t bitmap;
}BITMAP;
//--------------------------------------------------------------
// Defines
//--------------------------------------------------------------
/**
 * X size of the bitmap array
 */
#define ARRAY_X		32

/**
 * Y size of the bitmap array
 */
#define ARRAY_Y		32


#define TEXT_BUFFER 100
#define FONT_BUFFER 20
#define STYLE_BUFFER 20

#define STR_LENGTH 120

#define TYPE_LENGTH 20

#define COLOR_LENGTH 20


char buff[TYPE_LENGTH];
char color[COLOR_LENGTH];
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
int API_Draw_Line(LINE line);

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
int API_Draw_Ellipse(ELLIPSE ellip);

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
int API_Draw_Rectangle(SQUARE square);

/**
 * @brief Draws a triangle on the screen
 * @param[in]	x1			horizontal begin position of the triangle
 * @param[in]	y1			vertical begin position of the triangle
 * @param[in]	x2			horizontal middle position of the triangle
 * @param[in]	y2			vertical middle position of the triangle
 * @param[in]	x3			horizontal end position of the triangle
 * @param[in]	y3			vertical end position of the triangle
 * @param[in]	fill_empty	fill triangle if argument is true
 * @param[in]	color		color given in string format
 * @retval		error
 */
int API_Draw_Triangle(TRIANGLE triangle);

/**
 * @brief Draws a bitmap on the screen
 * @param[in]	x_lo	 	horizontal begin position of the bitmap
 * @param[in]	y_lo		vertical begin position of the bitmap
 * @param[in]	bitmap_id	id of the bitmap (1. angry_emoticon 2. happy_emoticon 3. arrow_down 4. arrow_left 5. arrow_up 6. arrow_right) (table toevoegen van welke id welke bitmap is)
 * @retval		error
 */
int API_Draw_Bitmap(BITMAP bitmap);

/**
 * @brief Draws a Font on the screen
 * @param[in]	x			horizontal begin position of the bitmap
 * @param[in]	y			vertical begin position of the bitmap
 * @param[in]	text		text that get puts on the screen
 * @param[in]	font_id		id of the font (1. ..... 2. .....)
 * @param[in]	style		style of the font (1. normal 2. bold 3. italic)
 * @param[in]	color		color given in string format
 * @retval		error
 */

void API_Draw_Font( TEXT txt);

/**
 * @brief Clears the screen with any given color
 * @param[in]	color		color of the screen
 * @retval		color		color of the screen
 */

int API_Draw_Clearscreen(uint8_t color);

/**
 * @brief Waits for a certain time defined by the user
 * @param[in]	time		the amount of time that the function has to wait
 * @retval		time		the amount of time that the function has to wait
 */
int API_Draw_Wait(int time);

