#include "main.h"

int main(void){
	SystemInit();
	UB_VGA_Screen_Init();
	UB_VGA_FillScreen(VGA_COL_CYAN);
	TM_Delay_Init();
	int i;
	int x1 = 160;
	int y1 = 120;
	int width = 50;
	int height = 50;
	int color = VGA_COL_MAGENTA;

		for(int y=-height; y<=height; y++) {
			for(int x=-width; x<=width; x++) {
				if(x*x*height*height+y*y*width*width <= height*height*width*width && x*x*height*height+y*y*width*width >= height*width*(height*width-height*2-width*2)){
					//int oldcolor= VGA_RAM1[(y1+y*(VGA_DISPLAY_X+1))+x1+x];
					UB_VGA_SetPixel(x1+x, y1+y,color);

				}
					//TM_DelayMillis(50);
			}
		}


	while(1){

	}
}
