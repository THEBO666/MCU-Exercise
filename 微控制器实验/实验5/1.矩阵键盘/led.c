#include <STC89C5xRC.H>

void Led_Display(unsigned char i,ena)
{
	static unsigned char j1=0x00;
	static unsigned char k1=0xff;
	if(ena)
		j1|=(0x01<<i);
	else
		j1&=~(0x01<<i);
	if(j1!=k1)
	{
		P1=~j1;
		k1=j1;
	}
}