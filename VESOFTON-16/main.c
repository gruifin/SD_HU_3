#include "main.h"

int main(void){
	SystemInit();
	UB_VGA_Screen_Init();
	UB_VGA_FillScreen(VGA_COL_CYAN);
	UB_VGA_DrawEllipse(220,220,40,20,VGA_COL_BLUE,1);



	while(1){

	}
}

