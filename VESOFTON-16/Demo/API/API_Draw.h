/*******************************************************************************
 * Begin of file API_Draw.h
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
// Includes
//--------------------------------------------------------------
#include "User_Interface.h"
#include "API_IO.h"


/** @brief Structure for line parameters  */
typedef struct
{
	/** @brief	horizontal begin position of the line  */
	uint16_t x1;

	/** @brief	vertical begin position of the line  */
	uint16_t y1;

	/** @brief	horizontal end position of the line  */
	uint16_t x2;

	/** @brief	vertical end position of the line  */
	uint16_t y2;

	/** @brief	weight of the line  */
	uint8_t width;

	/** @brief	color of the line  */
	uint8_t colint;

}LINE;

/** @brief Structure for ellipse parameters  */
typedef struct
{
	/** @brief	horizontal center position of the ellipse  */
	uint16_t xp;

	/** @brief	vertical center position of the ellipse  */
	uint16_t yp;

	/** @brief	the width of the ellipse  */
	uint16_t width;

	/** @brief	the height of the ellipse */
	uint16_t height;

	/** @brief	fill ellipse if argument is true  */
	uint8_t fill;

	/** @brief	color of the ellipse  */
	uint8_t	colint;
}ELLIPSE;


/** @brief Structure for triangle parameters  */
typedef struct
{
	/** @brief	horizontal begin position of the triangle  */
	uint16_t x1;

	/** @brief	vertical begin position of the triangle  */
	uint16_t y1;

	/** @brief	horizontal middle position of the triangle  */
	uint16_t x2;

	/** @brief	vertical middle position of the triangle  */
	uint16_t y2;

	/** @brief	horizontal end position of the triangle  */
	uint16_t x3;

	/** @brief	vertical end position of the triangle  */
	uint16_t y3;

	/** @brief	fill triangle if argument is true  */
	uint8_t fill;

	/** @brief	color of the triangle  */
	uint8_t colint;
}TRIANGLE;

/** @brief Structure for rectangle parameters  */
typedef struct
{
	/** @brief	horizontal begin position of the rectangle  */
	uint16_t x1;

	/** @brief	vertical begin position of the rectangle  */
	uint16_t y1;

	/** @brief	horizontal end position of the rectangle  */
	uint16_t x2;

	/** @brief	vertical end position of the rectangle  */
	uint16_t y2;

	/** @brief	fill rectangle if argument is true  */
	uint16_t fill;

	/** @brief	color of the rectangle  */
	uint8_t colint;
}SQUARE;

/** @brief Structure for text parameters  */
typedef struct
{
	/** @brief	fills buffer for API_Draw_Font  */
	char buff[200];

	/** @brief	horizontal begin position of the bitmap  */
	uint16_t x;

	/** @brief	vertical begin position of the bitmap  */
	uint16_t y;

	/** @brief	text that get puts on the screen  */
	char text[200];

	/** @brief	id of the font  */
	char font[20];

	/** @brief	style of the font  */
	char style[20];

	/** @brief	color of the text  */
	uint8_t colint;
}TEXT;

/** @brief Structure for bitmap parameters  */
typedef struct
{
	/** @brief	horizontal begin position of the bitmap  */
	uint16_t x;

	/** @brief	vertical begin position of the bitmap  */
	uint16_t y;

	/** @brief	id of the bitmap
	 *
	 *<table>
     *   <caption id="Bitmap">Bitmap</caption>
     *   <tr>
     *     <th>Bitmap id</th>
     *     <td>6</td>
     *     <td>5</td>
     *     <td>4</td>
     *     <td>3</td>
     *     <td>2</td>
     *     <td>1</td>
     *   </tr>
     *   <tr>
     *     <td><b>Name</b></td>
     *     <td>angry_emoticon</td>
     *     <td>happy_emoticon</td>
     *     <td>arrow_down</td>
     *     <td>arrow_left</td>
     *     <td>arrow_up</td>
     *      <td>arrow_right </td>
     *   </tr>
     * </table>
	 * */
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

/**
 * Size of the text buffer
 */
#define TEXT_BUFFER 100

/**
 * Size of the font buffer
 */
#define FONT_BUFFER 20

/**
 * Size of the style buffer
 */
#define STYLE_BUFFER 20

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
 * @retval		error
 */
int API_Draw_Line(LINE line);

/**
 * @brief Draws an Ellipse on the screen
 * @retval		error
 */
int API_Draw_Ellipse(ELLIPSE ellip);

/**
 * @brief Draws a rectangle on the screen
 * @retval		error
 */
int API_Draw_Rectangle(SQUARE square);

/**
 * @brief Draws a triangle on the screen
 * @retval		error
 */
int API_Draw_Triangle(TRIANGLE triangle);

/**
 * @brief Draws a bitmap on the screen
 * @retval		error
 */
int API_Draw_Bitmap(BITMAP bitmap);

/**
 * @brief Draws a Font on the screen
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

