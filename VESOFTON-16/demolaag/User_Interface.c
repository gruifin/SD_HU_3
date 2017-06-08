/*******************************************************************************
 * Begin of file User_Interface.c
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


#include "main.h"

int main(void)
{

	while(1)
	{
		IO_Init();

		IO_readString(command.buff,command.type);

		command.error = LL_EXEC(command.buff,command.type);

		if (command.error > 0)
			IO_WRITE_ERROR(command.error);
    }
}
