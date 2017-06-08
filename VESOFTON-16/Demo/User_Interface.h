/*******************************************************************************
 * Begin of file User_Interface.h
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
#ifndef __STM32F4_UB_MAIN_H
#define __STM32F4_UB_MAIN_H

#define STR_LENGTH 120
#define TYPE_LENGTH 20

typedef struct
{
	char buff[STR_LENGTH];
	char type[TYPE_LENGTH];
	int error;
}COMMAND;
COMMAND command;

/**
 * @brief Initialize API_IO
 */
void IO_Init();

/**
 * @brief Reads incoming string
 * @param[in]	buff
 * @param[in]	command
 */
void IO_readString(char *buff,char *command);

/**
 * @brief Logic layer execute (chose which command)
 *
 * @param[in]	buff
 * @param[in]	command
 */
int LL_EXEC(char *string, char *command);

/**
 * @brief Function writes error to UART
 * @param[in]	error
 */
void IO_WRITE_ERROR(int error);
//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f4xx.h"
#include <math.h>
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"
#include "string.h"
#include "stdlib.h"

//--------------------------------------------------------------
#endif // __STM32F4_UB_MAIN_H
