/*******************************************************************************
 * Begin of file Input_Output.c
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

#include "API_IO.h"

/**
 * @brief Initialize API_IO
 */
void IO_Init()
{
	SystemInit();
	API_IO_Screen_Init();
	API_IO_Delay_Init();
	API_IO_UART_init();
}

/**
 * @brief Reads incoming string
 * @param[in]	buff		horizontal begin position of the line
 * @param[in]	command		vertical begin position of the line
 */
void IO_readString(char *buff,char *command)
{
	 API_IO_UART_gets(buff,1);
	 for (int i = 0; i < STR_LENGTH; ++i){
		 if (buff[i] == ',') {
			strncpy(command,buff,i);
			command[i] = 0;
			break;
		}

	 }
}

/**
 * @brief Function writes error to UART
 * @param[in]	error			horizontal begin position of the line
 */
void IO_WRITE_ERROR(int error)
{
	 switch (error)
	 {
		case 1:
			API_IO_UART_puts("Wrong Command Received");
			API_IO_UART_puts("\r\n");
			break;
		case 2:
			API_IO_UART_puts("Out Of Bounds");
			API_IO_UART_puts("\r\n");
			break;
		default:
		break;
	}
}
