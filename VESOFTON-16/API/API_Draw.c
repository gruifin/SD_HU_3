#include "API_Draw.h"

char string[100];
int charcounter = 0;
uint32_t multiplier;

void TM_Delay_Init(void) {
    RCC_ClocksTypeDef RCC_Clocks;

    /* Get system clocks */
    RCC_GetClocksFreq(&RCC_Clocks);

    /* While loop takes 4 cycles */
    /* For 1 us delay, we need to divide with 4M */
    multiplier = RCC_Clocks.HCLK_Frequency / 4000000;
}

void TM_DelayMicros(uint32_t micros) {
    /* Multiply micros with multipler */
    /* Substract 10 */
    micros = micros * multiplier - 10;
    /* 4 cycles for one loop */
    while (micros--);
}

void TM_DelayMillis(uint32_t millis) {
    /* Multiply millis with multipler */
    /* Substract 10 */
    millis = 1000 * millis * multiplier - 10;
    /* 4 cycles for one loop */
    while (millis--);
}

void UART_init(void)
{

  /* --------------------------- System Clocks Configuration -----------------*/
  /* USART2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  /* GPIOA clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  /*-------------------------- GPIO Configuration ----------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect USART pins to AF */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);   // USART2_TX
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);  // USART2_RX

  USART_InitTypeDef USART_InitStructure;

/* USARTx configuration ------------------------------------------------------*/
/* USARTx configured as follow:
      - BaudRate = 115200 baud
      - Word Length = 8 Bits
      - One Stop Bit
      - No parity
      - Hardware flow control disabled (RTS and CTS signals)
      - Receive and transmit enabled
*/
USART_InitStructure.USART_BaudRate = 115200;
USART_InitStructure.USART_WordLength = USART_WordLength_8b;
USART_InitStructure.USART_StopBits = USART_StopBits_1;
USART_InitStructure.USART_Parity = USART_Parity_No;
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

USART_Init(USART2, &USART_InitStructure);
USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

USART_Cmd(USART2, ENABLE);

}

void UART_putchar(char c)
{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
		USART_SendData(USART2, c);

}

void UART_puts(char *s)
{
	volatile unsigned int i;
	for (i=0; s[i]; i++)
	{
		UART_putchar(s[i]);
		//while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
		//USART_SendData(USART2, s[i]);
	}
}


void UART_INT_init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void USART2_IRQHandler(void)
{
	// check if the USART2 receive interrupt flag was set
	if( USART_GetITStatus(USART2, USART_IT_RXNE))
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		int i;
		char c = USART2->DR & 0xFF;
//		LCD_XY(10,1);
//		LCD_put("UART:   ");
//		LCD_XY(15,1);
//		LCD_putchar(c);

		if(c > 64 && c < 91)
			c += 32;
		if(c <= 13)
		{
			for(i=0;i<charcounter;i++)
			{
				USART_SendData(USART2, string[i]); // Echo Char
			}
			charcounter = 0;
			USART_SendData(USART2, c); // Echo Char
		}
		else
		{
			string[charcounter] = c;
			charcounter++;
		}


		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); // Wait for Empty

	}
}


void UART_putint(unsigned int num)
{
    UART_putnum(num, 10);
}

// Stuurt meegegeven getal uit op de UART in het aangegeven getallenstelsel
void UART_putnum(unsigned int num, unsigned char deel)
{
    static unsigned char chars[16] = "0123456789ABCDEF";
    unsigned int rest;
    signed char c[16];
    signed int i=15;

    // Zet de integer om naar een string
    if(num==0)
    {
        c[i]='0';
        i--;
    }
    else
    {
        while(num>0)
        {
            rest=num%deel;
            num/=deel;
            c[i]=chars[rest];
            i--;

            if(i==0) // it ends here
                num=0;
        }
    }


    // Stuur de string uit
    while(i<15)
    {
        i++;
        // Wacht tot de buffer leeg is
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
        USART_SendData(USART2, c[i]);

    }
}

// Ontvang een karakter via de UART
// niet echt nodig als routine maar als wrapper voor compatabiliteit. Let op geen -1 als er geen char is ontvangen!

char UART_get(void)
{
    char uart_char = -1;
    if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE)== SET)  // check for data available
    	 uart_char= USART2->DR & 0xFF; // and read the data from peripheral
    return uart_char;
}


// void UART_gets
// args: char *readbuffer
//       int   echo, when TRUE, send read-char to UART
// remark: ARM sends -1 if buffer is empty
//         LF is cleared if set in terminal-program
void UART_gets(char *s, int echo)
{
	while (1)
	{
	 	*s = UART_get();

	 	if (*s==-1)             // check for data available
	 		continue;

	 	if (*s==0xff || *s==LF) // if no data or LF, continue
			continue;

		if (echo)              // if output-flag set
			UART_putchar(*s);  // to read what u entered

		if (*s==CR)            // if enter pressed
		{
			*s = '\0';         // ignore char and close string
		    return;            // buf ready, exit loop
		}
		s++;
	}
}

int API_DRAW_color_to_int(char *s){
	uint8_t color;
	if(strcmp(s,"blauw")==0){
		color = VGA_COL_BLUE;
	}
	else if(strcmp(s,"rood")==0){
		color = VGA_COL_RED;
	}
	else if(strcmp(s,"geel")==0){
		color =  VGA_COL_YELLOW;
	}
	else if(strcmp(s,"groen")==0){
		color = VGA_COL_GREEN;
	}
	else if(strcmp(s,"lichtrood")==0){
		color = VGA_COL_LIGHT_RED;
	}
	else if(strcmp(s,"magenta")==0){
		color = VGA_COL_MAGENTA;
	}
	else if(strcmp(s,"lichtmagenta")==0){
		color = VGA_COL_LIGHT_MAGENTA;
	}
	else if(strcmp(s,"lichtgroen")==0){
		color = VGA_COL_LIGHT_GREEN;
	}
	else if(strcmp(s,"lichtblauw")==0){
		color = VGA_COL_LIGHT_BLUE;
	}
	else if(strcmp(s,"cyaan")==0){
		color = VGA_COL_CYAN;
	}
	else if(strcmp(s,"lichtcyaan")==0){
		color = VGA_COL_LIGHT_CYAN;
	}
	else if(strcmp(s,"bruin")==0){
		color = VGA_COL_BROWN;
	}
	else if(strcmp(s,"grijs")==0){
		color = VGA_COL_GRAY;
	}
	else if(strcmp(s,"wit")==0){
		color = VGA_COL_WHITE;
	}
	else if(strcmp(s,"zwart")==0){
		color= VGA_COL_BLACK;
	}
	return color;
}

void API_Draw_Line(uint16_t x1, uint16_t y1,uint16_t x2,uint16_t y2,uint16_t width, uint8_t color)
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

			for (i=(-1*width); i < width; i++){
				for (k=(-1*width); k < width; k++){
				UB_VGA_SetPixel(x1+k*rx+(j*rx),y1+i*ry+(j*ry),color);
				}
			}

		}
}
void API_Draw_Ellipse(uint16_t xc, uint16_t yc, uint16_t width,uint16_t height, uint8_t fill,uint8_t color){
	for(int y=-height; y<=height; y++) {
		for(int x=-width; x<=width; x++) {
			int r= x*x*height*height+y*y*width*width;
			int fillcalc = height*width*(height*width-height*2-width*2);

			if(r <= height*height*width*width && r >= fillcalc && fill > 0){
				UB_VGA_SetPixel(xc+x, yc+y,color);
			}
			else if(r <= height*height*width*width && fill == 0){
				UB_VGA_SetPixel(xc+x, yc+y,color);
			}
	}
  }
}

void API_Draw_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t fill_empty, uint16_t width, uint8_t color)
{
	int i;
	int j;
	int rx = 1;
	int ry = 1;

	int lrd = abs(x2 - x1);
	int tbd = abs(y2 - y1);

	if(x2 < x1)
	{
		rx = -1;
	}

	if(y2 < y1)
	{
		ry = -1;
	}

	API_Draw_Line(x1,y1,x2,y1, width, color);
	API_Draw_Line(x1,y1,x1,y2, width, color);
	API_Draw_Line(x2,y1,x2,y2, width, color);
	API_Draw_Line(x1,y2,x2+1,y2, width, color);

	if (fill_empty == 1)
	{
		for(i = 0; i < lrd; i++)
		{
			for(j = 0; j < tbd; j++)
			{
				UB_VGA_SetPixel(x1 + (i*rx), y1 + (j*ry), color);
			}
		}
	}
}

void API_Draw_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3,uint8_t fill, uint8_t color)
{
	int i;
	int j;


	int lrd = abs(x2 - x1); //left right delta
	int tbd = abs(y3 - y1); //top bottom delta

	API_Draw_Line(x1,y1,x2,y2, 1, color);
	API_Draw_Line(x2,y2,x3,y3, 1, color);
	API_Draw_Line(x3,y3,x1,y1, 1, color);

	//if(fill == 1){

	for(i = 0; i < lrd; i++)
	{
		for(j = 0; j < tbd; j++)
		{
			API_Draw_Line(x3,y3,x1+i,y1, 0, color);
		}
	}

}

void API_Draw_Clearscreen(uint8_t color)
{
	UB_VGA_FillScreen(color);
}
