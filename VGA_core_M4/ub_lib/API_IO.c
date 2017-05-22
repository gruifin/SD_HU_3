#include "stm32_ub_vga_screen.h"
#include <math.h>
#include "stdlib.h"

void UB_VGA_Line(uint16_t x1, uint16_t y1,uint16_t x2,uint16_t y2,uint16_t width, uint8_t color)
{
	float xd = abs(x2-x1);
	float yd = abs(y2-y1);
	float rx  = xd/yd;
	float ry = yd/xd;
	int i;
	int j;
	int k;
	int d;
	if(yd>xd){
		d = yd;
		ry = 1;
	}else{
		d = xd;
		rx = 1;
	}
	if(x2 < x1){
	rx = -1*rx;
	}
	if(y2 < y1){
	ry = -1*ry;
	}
		for(j = 0; j < d; j++){
			if(width != 0){
			for (i=(-1*width); i < width; i++){
				for (k=(-1*width); k < width; k++){
				UB_VGA_SetPixel(x1+k*ry+(j*rx),y1+i*rx+(j*ry),color);
				}
			}
			}else{
				UB_VGA_SetPixel(x1+(j*rx),y1+(j*ry),color);
			}
		}
}
