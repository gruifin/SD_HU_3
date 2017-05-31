
#include "main.h"
#define CR 13 // carriage return char
#define LF 10 // linefeed char
void API_IO_Delay_Init(void);
void API_IO_DelayMicros(uint32_t micros);
void API_IO_DelayMillis(uint32_t millis);
void UART_init(void);
void UART_INT_init(void);
void UART_putchar(char c);
void UART_puts(char *s);
void UART_putnum(unsigned int num, unsigned char deel);
void UART_putint(unsigned int num);
char UART_get(void);
void UART_gets(char *s, int echo);
int API_DRAW_color_to_int(char *s);
int API_Draw_Line(uint16_t x1, uint16_t y1,uint16_t x2,uint16_t y2,uint16_t width, uint8_t color);
int API_Draw_Ellipse(uint16_t xc, uint16_t yc, uint16_t width,uint16_t height,uint8_t fill, uint8_t color);
int API_Draw_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t fill_empty, uint16_t width, uint8_t color);
int API_Draw_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3,uint8_t fill, uint8_t color);
int API_Draw_Clearscreen(uint8_t color);
int API_Draw_Wait(int time);
