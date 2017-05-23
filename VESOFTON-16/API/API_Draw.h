
#include "main.h"
#define CR 13 // carriage return char
#define LF 10 // linefeed char
void TM_Delay_Init(void);
void TM_DelayMicros(uint32_t micros);
void TM_DelayMillis(uint32_t millis);
void UART_init(void);
void UART_INT_init(void);
void UART_putchar(char c);
void UART_puts(char *s);
void UART_putnum(unsigned int num, unsigned char deel);
void UART_putint(unsigned int num);
char UART_get(void);
void UART_gets(char *s, int echo);
void UB_VGA_DrawEllipse(uint16_t xc, uint16_t yc, uint16_t width,uint16_t height,uint8_t color, uint8_t fill);
