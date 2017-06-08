//--------------------------------------------------------------
// File     : main.h
//--------------------------------------------------------------

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
void IO_Init();
void IO_readString(char *buff,char *command);
int LL_EXEC(char *string, char *command);
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
