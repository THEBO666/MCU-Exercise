#include <STC89C5xRC.H>
#include "uart.h"
#include <INTRINS.H>

char *str="hello world";
void Delay1000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 154;
	k = 122;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Uart_Pro()
{
	Uart_SendString(str);
}

void main()
{
	UartInit();
	while(1)
	{
		Uart_Pro();
		Delay1000ms();
	}
	
}