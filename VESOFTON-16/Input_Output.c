#include "API_IO.h"

void IO_Init()
{
	SystemInit();
	API_IO_Screen_Init();
	API_IO_Delay_Init();
	API_IO_UART_init();
}

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
