#include <STC15F2K60S2.H>

void LED_Display(unsigned char i,ena)
{
	static unsigned char j = 0x00;
	static unsigned char k = 0xFF;
	if(ena)
		j|=(0x01<<i);
	else
		j&=~(0x01<<i);
	if(j!=k)
	{
		P0=~j;
		P2=P2&0x1f|0x80;
		P2&=0x1f;
		k=j;//避免电流声
	}
}
