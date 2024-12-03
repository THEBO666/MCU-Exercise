#include <STC89C5xRC.H>

unsigned char code SMG[]={0x3F,
0x06,
0x5B,
0x4F,
0x66,
0x6D,
0x7D,
0x07,
0x7F,
0x6F,
0x00,
};
sbit duan=P2^0;
sbit wei=P2^1;
unsigned char code weiTable[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

void Seg_Display(unsigned char i,j,k)
{
	//duan=0;
	//P0=0x00;
	//duan=1;
	//
	duan=0;
	wei=0;
	P0=weiTable[i];
	wei=1;
	wei=0;
	duan=0;
	P0=SMG[j];
	if(k)        //0000 0110    
		P0|=0x80;//1111 1111
	duan=1;
	duan=0;
}