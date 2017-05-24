#include "main.h"

int main(void){
	SystemInit();
	UB_VGA_Screen_Init();
	UB_VGA_FillScreen(VGA_COL_CYAN);
	UART_init();



	while(1){


		 char string[100];
		 UART_gets(string,0);
		 char command[20];
		 int i = 0;
		 for (i = 0; i < 100; ++i){
			 if (string[i] == ',') {
				strncpy(command,string,i);
				command[i] = NULL;
				break;
			}

		 }
		 if (strcmp(command,"lijn")== 0) {
			int j;
			int k;
			int c = 0;
			char buff[10];
			uint16_t x1;
			uint16_t y1;
			uint16_t x2;
			uint16_t y2;
			uint8_t width;
			char color[10];
			for(j=0;j < 100; j++){
				if (string[j] == ',')
				{
					c++;
					switch (c) {
						case 2:
							x1 =atoi(buff);
						case 3:
							y1 =atoi(buff);
						case 4:
							x2 =atoi(buff);
						case 5:
							y2 =atoi(buff);
						case 6:
							width =atoi(buff);


						default:
							break;
				 }
					k = 0;
					memset(buff,0,10);
				}
				else if (string[j] == NULL && c == 6) {
					strcpy(color,buff);
					UART_putint(x1);
					UART_puts("\r\n");
					UART_putint(y1);
					UART_puts("\r\n");
					UART_putint(x2);
					UART_puts("\r\n");
					UART_putint(y2);
					UART_puts("\r\n");
					UART_putint(width);
					UART_puts("\r\n");
					UART_puts(color);
					UART_puts("\r\n");
					API_Draw_Line(x1,y1,x2,y2,width,VGA_COL_MAGENTA);
					break;
				}

				else{
				buff[k] = string[j];
				k++;

			}
			}
		}
		 else if (strcmp(command,"ellips")== 0) {
		 		int j;
		 		int k;
		 		int c = 0;
		 		char buff[10];
		 		uint16_t xp;
		 		uint16_t yp;
		 		uint16_t width;
		 		uint16_t height;
		 		uint8_t fill;
		 		char color[10];
		 		for(j=0;j < 100; j++){
		 			if (string[j] == ',')
		 			{
		 				c++;
		 				switch (c) {
		 					case 2:
		 						xp =atoi(buff);
		 					case 3:
		 						yp =atoi(buff);
		 					case 4:
		 						width =atoi(buff);
		 					case 5:
		 						height =atoi(buff);
		 					case 6:
		 						fill =atoi(buff);


		 					default:
		 						break;
		 			 }
		 				k = 0;
		 				memset(buff,0,10);
		 			}
		 			else if (string[j] == NULL && c == 6) {
		 				strcpy(color,buff);
		 				UART_putint(xp);
		 				UART_puts("\r\n");
		 				UART_putint(yp);
		 				UART_puts("\r\n");
		 				UART_putint(width);
		 				UART_puts("\r\n");
		 				UART_putint(height);
		 				UART_puts("\r\n");
		 				UART_putint(fill);
		 				UART_puts("\r\n");
		 				UART_puts(color);
		 				UART_puts("\r\n");
		 				UB_VGA_DrawEllipse(xp,yp,width,height,fill,VGA_COL_GREEN);
		 				break;
		 			}

		 			else{
		 			buff[k] = string[j];
		 			k++;

		 		}
		 		}
		 	}
	  }
}

