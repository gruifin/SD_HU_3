//--------------------------------------------------------------
// File     : main.c
// Datum    : 30.03.2016
// Version  : 1.0
// Autor    : UB
// mods by	: J.F. van der Bent
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.x
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : VGA_core DMA LIB 320x240, 8bit color
//--------------------------------------------------------------

#include "main.h"

int main(void)
{

	SystemInit(); // System speed to 168MHz
	UART_init();
	TM_Delay_Init();
  while(1)
  {
	 char string[100];
	 UART_gets(string,0);
	 TM_DelayMicros(100);
	 char command[20];
	 int i = 0;
	 for (i = 0; i < 100; ++i){
		 if (string[i] == ',') {
			strncpy(command,string,i);
			command[i] = NULL;
			break;
		}

	 }
	// UART_puts(command);
	 //UART_putint(strcmp(command,"lijn"));
	 if (strcmp(command,"lijn")== 0) {
		int j;
		int k;
		int newpos;
		int c = 0;
		char buff[10];
		uint16_t x1;
		uint16_t y1;
		uint16_t x2;
		uint16_t y2;
		uint8_t width;
		uint8_t color;
		for(j=0;j < 100; j++){

			 switch (c) {
				case 1:
					buff[k] = string[j];
					k++;
					break;
				case 2:
					x1 =atoi(buff);
					UART_putint(x1);
				default:
					break;
			 }
			//UART_putint(c);
			if (string[j] == ',')
			{
			 k = 0;
			 c++;
			}

		}
	}
  }
}

