#include "main.h"

int main(void){
	SystemInit();
	UB_VGA_Screen_Init();
	UB_VGA_FillScreen(VGA_COL_GREEN);
	TM_Delay_Init();
	UART_init();
	API_Draw_Rectangle(10,10,300,200,1,0,VGA_COL_BLACK);


	while(1){

		 char string[100];
		 UART_gets(string,0);
		 char command[20];
		 int i = 0;
		 for (i = 0; i < 100; ++i){
			 if (string[i] == ',') {
				strncpy(command,string,i);
				command[i] = 0;
				break;
			}

		 }

		 if (strcmp(command,"lijn")== 0) {
			int j;
			int k = 0;
			int c = 0;
			char buff[20];
			uint16_t x1;
			uint16_t y1;
			uint16_t x2;
			uint16_t y2;
			uint8_t width;
			char color[20];
			int colint;
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
				else if (string[j] == 0 && c == 6) {
					strcpy(color,buff);
					colint = API_DRAW_color_to_int(color);
					API_Draw_Line(x1,y1,x2,y2,width,colint);
	 				memset(buff,0,10);
					break;
				}

				else if(c>=1){
				buff[k] = string[j];
				k++;

			}
			}
		}
		 else if (strcmp(command,"ellips")== 0) {
		 		int j;
		 		int k = 0;
		 		int c = 0;
		 		char buff[20];
		 		uint16_t xp;
		 		uint16_t yp;
		 		uint16_t width;
		 		uint16_t height;
		 		uint8_t fill;
		 		char color[20];
		 		int	colint;
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
		 			else if (string[j] == 0 && c == 6) {
		 				strcpy(color,buff);
		 				colint = API_DRAW_color_to_int(color);
		 				API_Draw_Ellipse(xp,yp,width,height,fill,colint);
		 				memset(buff,0,10);
		 				break;
		 			}

		 			else if(c>=1){
		 			buff[k] = string[j];
		 			k++;

		 		}
		 		}
		 	}
		 else if (strcmp(command,"driehoek")== 0) {
		 			int j;
		 			int k = 0;
		 			int c = 0;
		 			char buff[20];
		 			uint16_t x1;
		 			uint16_t y1;
		 			uint16_t x2;
		 			uint16_t y2;
		 			uint16_t x3;
		 			uint16_t y3;
		 			int fill;
		 			char color[20];
		 			int colint;
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
		 							x3 =atoi(buff);
		 						case 7:
		 							y3 =atoi(buff);
		 						case 8:
		 							fill =atoi(buff);

		 						default:
		 							break;
		 				 }
		 					UART_putint(c);
		 					k = 0;
		 					memset(buff,0,10);
		 				}
		 				else if (string[j] == 0 && c == 8) {
		 					strcpy(color,buff);
		 					colint = API_DRAW_color_to_int(color);
		 					API_Draw_Triangle(x1,y1,x2,y2,x3,y3,fill,colint);
			 				memset(buff,0,10);
		 					break;
		 				}

		 				else if (c>=1){
		 				buff[k] = string[j];
		 				k++;

		 			}
		 			}

		 		}
		 else if (strcmp(command,"rechthoek")== 0) {
		 			int j;
		 			int k = 0;
		 			int c = 0;
		 			char buff[20];
		 			uint16_t x1;
		 			uint16_t y1;
		 			uint16_t x2;
		 			uint16_t y2;
		 			uint16_t fill;
		 			char color[20];
		 			int colint;
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
		 							fill =atoi(buff);
		 						default:
		 							break;

		 				 }

		 					k = 0;
		 					memset(buff,0,10);
		 				}
		 				else if (string[j] == 0 && c == 6) {

		 					strcpy(color,buff);
		 					colint = API_DRAW_color_to_int(color);

		 					API_Draw_Rectangle(x1,y1,x2,y2,fill,1,colint);
		 					break;
		 				}

		 				else if(c >= 1){
		 				buff[k] = string[j];
		 				k++;
		 				}


		 			}
		 		}
		 else if (strcmp(command,"clearscherm")== 0) {
				 			int j;
				 			int k =0;
				 			int c = 0;
				 			char buff[20];
				 			char color[20];
				 			int colint;
				 			for(j=0;j < 100; j++){
				 				if (string[j] == ',')
				 				{	c++;
				 					UART_putint(c);
				 					k = 0;
				 					memset(buff,0,10);
				 				}
				 				else if (string[j] == 0 && c == 1) {
				 					strcpy(color,buff);
				 					colint = API_DRAW_color_to_int(color);
				 					API_Draw_Clearscreen(colint);
					 				memset(buff,0,10);
				 					break;
				 				}

				 				else if (c>=1){
				 				buff[k] = string[j];
				 				k++;

				 			}
				 			}
				 		}

	  }
}

