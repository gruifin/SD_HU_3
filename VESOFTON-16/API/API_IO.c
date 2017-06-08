//--------------------------------------------------------------
// File     : stm32_ub_vga_320x240.c
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.0
// Module   : GPIO, TIM, MISC, DMA
// Function : VGA out by GPIO (320x240 Pixel, 8bit color)
//
// signals  : PB11      = HSync-Signal
//            PB12      = VSync-Signal
//            PE8+PE9   = color Blue
//            PE10-PE12 = color Green
//            PE13-PE15 = color red
//
// uses     : TIM1, TIM2
//            DMA2, Channel6, Stream5
//--------------------------------------------------------------


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "API_IO.h"

char string[100];
int charcounter = 0;
uint32_t multiplier;


//--------------------------------------------------------------
// internal Functions
//--------------------------------------------------------------
void API_IO_InitIO(void);
void API_IO_InitTIM(void);
void API_IO_InitINT(void);
void API_IO_InitDMA(void);

/*
 * Function:	API_IO_Screen_Init
 * ----------------------------------
 * Initialize VGA-Module
 *
 * No arguments
 *
 * returns: no returns
 *
 */
void API_IO_Screen_Init(void)
{
	uint16_t xp,yp;

	VGA.hsync_cnt=0;
	VGA.start_adr=0;
	VGA.dma2_cr_reg=0;

	// RAM init total black
	for(yp=0;yp<VGA_DISPLAY_Y;yp++)
	{
		for(xp=0;xp<(VGA_DISPLAY_X+1);xp++)
		  VGA_RAM1[(yp*(VGA_DISPLAY_X+1))+xp]=0;
	}

	// init IO-Pins
	API_IO_InitIO();
	// init Timer
	API_IO_InitTIM();
	// init DMA
	API_IO_InitDMA();
	// init Interrupts
	API_IO_InitINT();

	//-----------------------
	// Register swap and safe
	//-----------------------
	// content of CR-Register read and save
	VGA.dma2_cr_reg=DMA2_Stream5->CR;
}

/*
 * Function:	API_IO_FillScreen
 * ----------------------------------
 * Fill the DMA RAM buffer with one color
 *
 * color:
 *
 * returns: no returns
 *
 */
void API_IO_FillScreen(uint8_t color)
{
	uint16_t xp,yp;

	for(yp=0;yp<VGA_DISPLAY_Y;yp++)
	{
		for(xp=0;xp<VGA_DISPLAY_X;xp++)
			API_IO_SetPixel(xp,yp,color);
	}
}

/*
 * Function:	API_IO_SetPixel
 * ----------------------------------
 * Sets pixels on the screen with the chosen color
 * Important : the last Pixel+1 from every line must be black (don't know why??)
 *
 * xp:
 * yp:
 * color:
 *
 * returns: no returns
 *
 */
void API_IO_SetPixel(uint16_t xp, uint16_t yp, uint8_t color)
{
	if(xp>=VGA_DISPLAY_X) xp=0;
	if(yp>=VGA_DISPLAY_Y) yp=0;

	// Write pixel to ram
	VGA_RAM1[(yp*(VGA_DISPLAY_X+1))+xp]=color;
}

/*
 * Function:	API_IO_InitIO
 * ----------------------------------
 * Initialize all IO-pins (internal function)
 *
 * No arguments
 *
 * returns: no returns
 *
 */
void API_IO_InitIO(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;


	//---------------------------------------------
	// init RGB-Pins (PE8 - PE15)
	// as normal GPIOs
	//---------------------------------------------

	// Clock Enable
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	// Config as Digital output
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
		GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIOE->BSRRH = VGA_GPIO_HINIBBLE;


	//---------------------------------------------
	// init of the H-Sync Pin (PB11)
	// using Timer2 and CH4
	//---------------------------------------------

	// Clock Enable
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	// Config Pins as Digital-out
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// alternative function connect with IO
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_TIM2);


	//---------------------------------------------
	// init of V-Sync Pin (PB12)
	// using GPIO
	//---------------------------------------------

	// Clock Enable
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	// Config of the Pins as Digital out
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIOB->BSRRL = GPIO_Pin_12;
}

/*
 * Function:	API_IO_InitTIM
 * ----------------------------------
 * Initialize Timer (internal function)
 *
 * No arguments
 *
 * returns: no returns
 *
 */
void API_IO_InitTIM(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;


	//---------------------------------------------
	// init of Timer1 for
	// Pixeldata via DMA
	//---------------------------------------------

	// Clock enable
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	// Timer1 init
	TIM_TimeBaseStructure.TIM_Period =  VGA_TIM1_PERIODE;
	TIM_TimeBaseStructure.TIM_Prescaler = VGA_TIM1_PRESCALE;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);


	//---------------------------------------------
	// init Timer2
	// CH4 for HSYNC-Signal
	// CH3 for DMA Trigger start
	//---------------------------------------------

	// Clock enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// Timer2 init
	TIM_TimeBaseStructure.TIM_Period = VGA_TIM2_HSYNC_PERIODE;
	TIM_TimeBaseStructure.TIM_Prescaler = VGA_TIM2_HSYNC_PRESCALE;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	// Timer2 Channel 3 ( for DMA Trigger start)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = VGA_TIM2_HTRIGGER_START-VGA_TIM2_DMA_DELAY;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

	// Timer2 Channel 4 (for HSYNC)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = VGA_TIM2_HSYNC_IMP;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);


	//---------------------------------------------
	// enable all Timers
	//---------------------------------------------

	// Timer1 enable
	TIM_ARRPreloadConfig(TIM1, ENABLE);

	// Timer2 enable
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

/*
 * Function:	API_IO_InitINT
 * ----------------------------------
 * Initialize interrupts (internal function)
 *
 * No arguments
 *
 * returns: no returns
 *
 */
void API_IO_InitINT(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//---------------------------------------------
	// init from DMA Interrupt
	// for TransferComplete Interrupt
	// DMA2, Stream5, Channel6
	//---------------------------------------------

	DMA_ITConfig(DMA2_Stream5, DMA_IT_TC, ENABLE);

	// NVIC config
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	//---------------------------------------------
	// init of Timer2 Interrupt
	// for HSync-Counter using Update
	// for DMA Trigger START using CH3
	//---------------------------------------------

	TIM_ITConfig(TIM2,TIM_IT_CC3,ENABLE);

	// NVIC config
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*
 * Function:	API_IO_InitDAM
 * ----------------------------------
 * Initialize Direct Memory Access (internal function)
 *
 * No arguments
 *
 * returns: no returns
 *
 */
void API_IO_InitDMA(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	//---------------------------------------------
	// DMA of Timer1 Update
	// (look at page 217 of the Ref Manual)
	// DMA=2, Channel=6, Stream=5
	//---------------------------------------------

	// Clock Enable (DMA)
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	// DMA init (DMA2, Channel6, Stream5)
	DMA_Cmd(DMA2_Stream5, DISABLE);
	DMA_DeInit(DMA2_Stream5);
	DMA_InitStructure.DMA_Channel = DMA_Channel_6;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)VGA_GPIOE_ODR_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&VGA_RAM1;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = VGA_DISPLAY_X+1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream5, &DMA_InitStructure);

	// DMA-Timer1 enable
	TIM_DMACmd(TIM1,TIM_DMA_Update,ENABLE);
}

/*
 * Function:	API_IO_Delay_Init
 * ----------------------------------
 * Initialize Delay
 *
 * No arguments
 *
 * returns: no returns
 *
 */
void API_IO_Delay_Init(void)
{
	RCC_ClocksTypeDef RCC_Clocks;

	/* Get system clocks */
	RCC_GetClocksFreq(&RCC_Clocks);

	/* While loop takes 4 cycles */
	/* For 1 us delay, we need to divide with 4M */
	multiplier = RCC_Clocks.HCLK_Frequency / 4000000;
}

/*
 * Function:	API_IO_DelayMicros
 * ----------------------------------
 * Delays the code for a certain amount of time
 *
 * micros:
 *
 * returns: no returns
 *
 */
void API_IO_DelayMicros(uint32_t micros)
{
    /* Multiply micros with multipler */
    /* Substract 10 */
    micros = micros * multiplier - 10;
    /* 4 cycles for one loop */
    while (micros--);
}

/*
 * Function:	API_IO_DelayMillis
 * ----------------------------------
 * Delays the code for a certain amount of time
 *
 * millis:
 *
 * returns: no returns
 *
 */
void API_IO_DelayMillis(uint32_t millis)
{
    /* Multiply millis with multipler */
    /* Substract 10 */
    millis = 1000 * millis * multiplier - 10;
    /* 4 cycles for one loop */
    while (millis--);
}

//--------------------------------------------------------------
// Interrupt of Timer2
//
//   CC3-Interrupt    -> starts from DMA
// Watch it.. higher troughput when interrupt flag is left alone
//--------------------------------------------------------------
void TIM2_IRQHandler(void)
{

	// Interrupt of Timer2 CH3 occurred (for Trigger start)
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);

	VGA.hsync_cnt++;
	if(VGA.hsync_cnt>=VGA_VSYNC_PERIODE)
	{
		// -----------
		VGA.hsync_cnt=0;
		// Adresspointer first dot
		VGA.start_adr=(uint32_t)(&VGA_RAM1[0]);
	}

		// HSync-Pixel
	if(VGA.hsync_cnt<VGA_VSYNC_IMP)
	{
		// HSync low
		GPIOB->BSRRH = GPIO_Pin_12;
		}
		else {
		// HSync High
		GPIOB->BSRRL = GPIO_Pin_12;
	}

	// Test for DMA start
	if((VGA.hsync_cnt>=VGA_VSYNC_BILD_START) && (VGA.hsync_cnt<=VGA_VSYNC_BILD_STOP))
	{
	// after FP start => DMA Transfer

	// DMA2 init
	DMA2_Stream5->CR=VGA.dma2_cr_reg;
	// set adress
	DMA2_Stream5->M0AR=VGA.start_adr;
	// Timer1 start
	TIM1->CR1|=TIM_CR1_CEN;
	// DMA2 enable
	DMA2_Stream5->CR|=DMA_SxCR_EN;

		// Test Adrespointer for high
		if((VGA.hsync_cnt & 0x01)!=0)
		{
		  // inc after Hsync
		  VGA.start_adr+=(VGA_DISPLAY_X+1);
		}
	}
}

//--------------------------------------------------------------
// DMA Interrupt ISR
//   after TransferCompleteInterrupt -> stop DMA
//
// still a bit buggy
//--------------------------------------------------------------
void DMA2_Stream5_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA2_Stream5, DMA_IT_TCIF5))
	{
		// TransferInterruptComplete Interrupt from DMA2
		DMA_ClearITPendingBit(DMA2_Stream5, DMA_IT_TCIF5);
		// stop after all pixels => DMA Transfer stop

		// Timer1 stop
		TIM1->CR1&=~TIM_CR1_CEN;
		// DMA2 disable
		DMA2_Stream5->CR=0;
		// switch on black
		GPIOE->BSRRH = VGA_GPIO_HINIBBLE;
	}
}

void API_IO_UART_init(void)
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

void API_IO_UART_putchar(char c)
{
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
		USART_SendData(USART2, c);
}

void API_IO_UART_puts(char *s)
{
	volatile unsigned int i;
	for (i=0; s[i]; i++)
	{
		API_IO_UART_putchar(s[i]);
		//while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
		//USART_SendData(USART2, s[i]);
	}
}

void API_IO_UART_INT_init(void)
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


void API_IO_UART_putint(unsigned int num)
{
	API_IO_UART_putnum(num, 10);
}

// Stuurt meegegeven getal uit op de UART in het aangegeven getallenstelsel
void API_IO_UART_putnum(unsigned int num, unsigned char deel)
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
char API_IO_UART_get(void)
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
void API_IO_UART_gets(char *s, int echo)
{
	while (1)
	{
	 	*s = API_IO_UART_get();

	 	if (*s==-1)             // check for data available
	 		continue;

	 	if (*s==0xff || *s==LFCHAR) // if no data or LF, continue
			continue;

		if (echo)              // if output-flag set
			API_IO_UART_putchar(*s);  // to read what u entered

		if (*s==CRCHAR)            // if enter pressed
		{
			*s = '\0';         // ignore char and close string
		    return;            // buf ready, exit loop
		}
		s++;
	}
}
