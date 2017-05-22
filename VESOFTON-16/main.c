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
	char string[100];
	SystemInit(); // System speed to 168MHz
	UART_init();
	TM_Delay_Init();
  while(1)
  {
	 UART_gets(string,1);
	 TM_DelayMillis(100);
	 while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	 char command[20];
	 int i = 0;
	 while(string[i] != '.'){
		 command[i]=string[i];
		 i++;
	 }
	 UART_puts(command);
  }
}

