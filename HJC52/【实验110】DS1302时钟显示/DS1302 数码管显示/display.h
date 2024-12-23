#ifndef _display_2003_7_21_
#define _display_2003_7_21_
#define uchar unsigned char
sbit we=P2^7;
sbit du=P2^6;
delay1()
{
	int x,y;
	for(x=1;x>0;x--)
		for(y=110;y>0;y--);
}

void display(uchar sw,uchar wan,uchar qian,uchar bai,uchar shi,uchar ge)
{
	we=1;
	P0=0xfe;
	we=0;
	P0=0;
	du=1;
	P0=sw;
	du=0;
	delay1();

	we=1;
	P0=0xfd;
	we=0;
	P0=0;
	du=1;
	P0=wan;
	du=0;
	delay1();

	we=1;
	P0=0xfb;
	we=0;
	P0=0;
	du=1;
	P0=qian;
	du=0;
	delay1();

	we=1;
	P0=0xf7;
	we=0;
	P0=0;
	du=1;
	P0=bai;
	du=0;
	delay1();

	we=1;
	P0=0xef;
	we=0;
	P0=0;
	du=1;
	P0=shi;
	du=0;
	delay1();

	we=1;
	P0=0xdf;
	we=0;
	P0=0;
	du=1;
	P0=ge;
	du=0;
	delay1();
}
#endif
