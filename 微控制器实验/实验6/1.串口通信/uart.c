#include <STC89C5xRC.H>

void UartInit(void)		//9600bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	TMOD = 0x20;		//设置定时器模式
	TL1 = 0xFD;			//设置定时初始值
	TH1 = 0xFD;			//设置定时初始值
	TR1 = 1;			//定时器1开始计时
	//ES=1;
	//EA=1;
}
void Uart_SendByte(char dat)
{
	SBUF=dat;
	while(TI==0);
	TI=0;
}

void Uart_SendString(char *dat)
{
	while(*dat!='\0')
		Uart_SendByte(*dat++);
}