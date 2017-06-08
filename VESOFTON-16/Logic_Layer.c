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

#include "API_Draw.h"
int counter = 0;
int error = 0;
int comma = 0;



int LL_EXEC(char *string, char *command)
{
		 if (strcmp(command,"lijn")== 0) {
			LINE lijn;
			for(int j=0;j < STR_LENGTH; j++){
				if (string[j] == ',')
				{
					comma++;
					switch (comma) {
						case 2:
							lijn.x1 =atoi(buff);
							break;
						case 3:
							lijn.y1 =atoi(buff);
							break;
						case 4:
							lijn.x2 =atoi(buff);
							break;
						case 5:
							lijn.y2 =atoi(buff);
							break;
						case 6:
							lijn.width =atoi(buff);
							break;
						default:
							break;
				 }
					counter = 0;
					memset(buff,0,20);
				}
				else if (string[j] == 0 && comma == 6) {
					strcpy(color,buff);
					lijn.colint = API_Draw_Color_To_Int(color);
				    error = API_Draw_Line(lijn);
	 				memset(buff,0,20);
	 				memset(color,0,COLOR_LENGTH);
	 				comma = 0;
	 				counter = 0;
					break;
				}

				else if(comma >=1){
				buff[counter] = string[j];
				counter++;

			}
			}
		}
		 else if (strcmp(command,"ellips")== 0) {
			 	ELLIPSE elli;
		 		for(int j=0;j < STR_LENGTH; j++){
		 			if (string[j] == ',')
		 			{
		 				comma++;
		 				switch (comma) {
		 					case 2:
		 						elli.xp =atoi(buff);
		 						break;
		 					case 3:
		 						elli.yp =atoi(buff);
		 						break;
		 					case 4:
		 						elli.width =atoi(buff);
		 						break;
		 					case 5:
		 						elli.height =atoi(buff);
		 						break;
		 					case 6:
		 						elli.fill =atoi(buff);
		 						break;

		 					default:
		 						break;
		 			 }
		 				counter = 0;
		 				memset(buff,0,20);
		 			}
		 			else if (string[j] == 0 && comma == 6) {
		 				strcpy(color,buff);
		 				elli.colint = API_Draw_Color_To_Int(color);
		 				error= API_Draw_Ellipse(elli);
		 				memset(buff,0,TYPE_LENGTH);
		 				memset(color,0,COLOR_LENGTH);
		 				break;
		 			}

		 			else if(comma>=1){
		 			buff[counter] = string[j];
		 			counter++;

		 		}
		 		}
		 	}
		 else if (strcmp(command,"driehoek")== 0) {
			 	 	TRIANGLE tri;
		 			for(int j=0;j < STR_LENGTH; j++){
		 				if (string[j] == ',')
		 				{
		 					comma++;
		 					switch (comma) {
		 						case 2:
		 							tri.x1 =atoi(buff);
		 							break;
		 						case 3:
		 							tri.y1 =atoi(buff);
		 							break;
		 						case 4:
		 							tri.x2 =atoi(buff);
		 							break;
		 						case 5:
		 							tri.y2 =atoi(buff);
		 							break;
		 						case 6:
		 							tri.x3 =atoi(buff);
		 							break;
		 						case 7:
		 							tri.y3 =atoi(buff);
		 							break;
		 						case 8:
		 							tri.fill =atoi(buff);
		 							break;

		 						default:
		 							break;
		 				 }
		 					counter = 0;
		 					memset(buff,0,20);
		 				}
		 				else if (string[j] == 0 && comma == 8) {
		 					strcpy(color,buff);
		 					tri.colint = API_Draw_Color_To_Int(color);
		 					error=API_Draw_Triangle(tri);
			 				memset(buff,0,TYPE_LENGTH);
			 				memset(color,0,COLOR_LENGTH);
		 					break;
		 				}

		 				else if (comma>=1){
		 				buff[counter] = string[j];
		 				counter++;

		 			}
		 			}

		 		}
		 else if (strcmp(command,"rechthoek")== 0) {
			 	 	SQUARE sq;
		 			for(int j=0;j < STR_LENGTH; j++){

		 				if (string[j] == ',')
		 				{
		 					comma++;
		 					switch (comma) {

		 						case 2:
		 							sq.x1 =atoi(buff);
		 							break;
		 						case 3:
		 							sq.y1 =atoi(buff);
		 							break;
		 						case 4:
		 							sq.x2 =atoi(buff);
		 							break;
		 						case 5:
		 							sq.y2 =atoi(buff);
		 							break;
		 						case 6:
		 							sq.fill =atoi(buff);
		 							break;
		 						default:
		 							break;

		 				 }

		 					counter = 0;
		 					memset(buff,0,20);
		 				}
		 				else if (string[j] == 0 && comma == 6) {

		 					strcpy(color,buff);
		 					sq.colint = API_Draw_Color_To_Int(color);
		 					error = API_Draw_Rectangle(sq);
			 				memset(buff,0,TYPE_LENGTH);
			 				memset(color,0,COLOR_LENGTH);
		 					break;
		 				}

		 				else if(comma >= 1){
		 				buff[counter] = string[j];
		 				counter++;
		 				}


		 			}
		 		}
		 else if (strcmp(command,"bitmap")== 0) {
			 	 BITMAP bit;
		 		 			for(int j=0;j < STR_LENGTH; j++){

		 		 				if (string[j] == ',')
		 		 				{
		 		 					comma++;
		 		 					switch (comma) {

		 		 						case 2:
		 		 							bit.bitmap =atoi(buff);
		 		 							break;
		 		 						case 3:
		 		 							bit.x =atoi(buff);
		 		 							break;
		 		 						default:
		 		 							break;

		 		 				 }
		 		 					counter = 0;
		 		 					memset(buff,0,20);
		 		 				}
		 		 				else if (string[j] == 0 && comma == 3) {
		 		 					bit.y = atoi(buff);
		 		 					error = API_Draw_Bitmap(bit);
		 			 				memset(buff,0,20);
		 		 					break;
		 		 				}

		 		 				else if(comma >= 1){
		 		 				buff[counter] = string[j];
		 		 				counter++;
		 		 				}


		 		 			}
		 		 		}
		 else if (strcmp(command,"tekst")== 0) {
			 	 TEXT txt;
		 		 for(int j=0;j < STR_LENGTH; j++){

		 						if (string[j] == ',')
		 		 		 				{
		 		 		 					comma++;
		 		 		 					switch (comma) {

		 		 		 						case 2:
		 		 		 							txt.x =atoi(buff);
		 		 		 							break;
		 		 		 						case 3:
		 		 		 							txt.y =atoi(buff);
		 		 		 							break;
		 		 		 						case 4:
		 		 		 							strcpy(txt.text,buff);
		 		 		 							break;
		 		 		 						case 5:
				 				 					strcpy(color,buff);
				 				 					txt.colint = API_Draw_Color_To_Int(color);
		 		 		 							break;
		 		 		 						case 6:
		 		 		 							strcpy(txt.font,buff);
		 		 		 						default:
		 		 		 							break;

		 		 		 				 }

		 		 		 					counter = 0;
		 		 		 					memset(buff,0,200);
		 		 		 				}
		 		 		 				else if (string[j] == 0 && comma == 7) {
		 		 		 					strcpy(txt.style,buff);
		 		 		 					API_Draw_Font(txt);
		 		 			 				memset(buff,0,TYPE_LENGTH);
		 		 			 				memset(color,0,COLOR_LENGTH);
		 		 		 					break;
		 		 		 				}

		 		 		 				else if(comma >= 1){
		 		 		 				buff[counter] = string[j];
		 		 		 				counter++;
		 		 		 				}


		 		 		 			}
		 		 		 		}
		 else if (strcmp(command,"clearscherm")== 0) {
				 			for(int j=0;j < STR_LENGTH; j++){
				 				if (string[j] == ',')
				 				{	comma++;
				 					counter = 0;
				 					memset(buff,0,20);
				 				}
				 				else if (string[j] == 0 && comma == 1) {
				 					strcpy(color,buff);
				 					API_Draw_Clearscreen(API_Draw_Color_To_Int(color));
					 				memset(buff,0,TYPE_LENGTH);
					 				memset(color,0,COLOR_LENGTH);
				 					break;
				 				}

				 				else if (comma>=1){
				 				buff[counter] = string[j];
				 				counter++;

				 			}
				 			}
				 		}
		 else if (strcmp(command,"wacht")== 0) {
					 			for(int j=0;j < STR_LENGTH; j++){
					 				if (string[j] == ',')
					 				{	comma++;
					 					counter = 0;
					 					memset(buff,0,20);
					 				}
					 				else if (string[j] == 0 && comma == 1) {
					 					API_Draw_Wait(atoi(buff));
						 				memset(buff,0,20);
					 					break;
					 				}

					 				else if (comma>=1){
					 				buff[counter] = string[j];
					 				counter++;

					 			}
					 			}
					 		}

		 else{
			error = 1;
		 }
		 return error;
}


