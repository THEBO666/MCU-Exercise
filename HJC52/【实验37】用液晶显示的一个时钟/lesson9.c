/**********************HJ-3G实验开发板例程************************
*  平台：HJ-3G V6.0 + Keil U3 + STC89C52
*  名称：
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hlmcu.com
*  编写：
*  日期：2008-8-08
*   QQ : 121350852  398115088
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://hjdz.5d6d.com
******************************************************************/

//注意事项：10天教程中的LCD1602第5脚由于当时设计错误，直接接到GND上了，接了低电平。
//本实验需要把LCD1602第5脚，读/写脚接到GND上，有两种方法，第一种，用杜邦线把P3.6脚接到GND上。
//另一种方法，定义一个 P3.6 IO口，在主函数中 把P3.6 写一个低电平就可以了。
//sbit WR = P3^6; 在后面主函数中加入 WR=0;就可以不用接杜邦线， P3.6到GND的杜邦线不要。
//WR=0;

#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
sbit rs=P1^0;
sbit rw=P1^1;
sbit lcden=P2^5;
sbit s1=P3^0;
sbit s2=P3^1;
sbit s3=P3^2;
sbit rd=P3^7;
uchar count,s1num;
char miao,shi,fen;
uchar code table[]="  2008-8-18 MON";
uchar code table1[]="    00:00:00";
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void write_com(uchar com)
{
	rs=0;
	lcden=0;
	P0=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;	
}

void write_date(uchar date)
{
	rs=1;
	lcden=0;
	P0=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;	
}

void init()
{

	uchar num;
	dula=0;
	wela=0;
	lcden=0;
//	fen=59;
//	miao=53;
//	shi=23;	       
    rw=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80);
	for(num=0;num<15;num++)
		{
			write_date(table[num]);
			delay(5);
		}
	write_com(0x80+0x40);
	for(num=0;num<12;num++)
		{
			write_date(table1[num]);
			delay(5);
		}
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
}

void write_sfm(uchar add,uchar date)
{
	uchar shi,ge;
	shi=date/10;
	ge=date%10;
	write_com(0x80+0x40+add);
	write_date(0x30+shi);
	write_date(0x30+ge);
}

void keyscan()
{
	rd=0;
	if(s1==0)	
	{
		delay(5);
		if(s1==0)
		{	s1num++;
			while(!s1);
			if(s1num==1)
			{
				TR0=0;
				write_com(0x80+0x40+10);
				write_com(0x0f);
			}
	}
			if(s1num==2)
			{
				write_com(0x80+0x40+7);
			}
			if(s1num==3)
			{
				write_com(0x80+0x40+4);
			}
			if(s1num==4)
			{
				s1num=0;
				write_com(0x0c);
				TR0=1;
			}

				
		}
		if(s1num!=0)
		{
			if(s2==0)
			{
				delay(5);
				if(s2==0)
				{
					while(!s2);
					if(s1num==1)
					{
						miao++;
						if(miao==60)
							miao=0;
						write_sfm(10,miao);
						write_com(0x80+0x40+10);
						
						
					}
					if(s1num==2)
					{
						fen++;
						if(fen==60)
							fen=0;
						write_sfm(7,fen);
						write_com(0x80+0x40+7);
					}
					if(s1num==3)
					{
						shi++;
						if(shi==24)
							shi=0;
						write_sfm(4,shi);
						write_com(0x80+0x40+4);
					}
				}
			}
			if(s3==0)
			{
				delay(5);
				if(s3==0)
				{
					while(!s3);
					if(s1num==1)
					{
					/*	if(miao==0)
						{
							miao=59;
							write_sfm(10,miao);
							write_com(0x80+0x40+10);
						}*/
						miao--;
						if(miao==-1)
							miao=59;
						write_sfm(10,miao);
						write_com(0x80+0x40+10);
					}
					if(s1num==2)
					{
						fen--;
						if(fen==-1)
							fen=59;
						write_sfm(7,fen);
						write_com(0x80+0x40+7);
					}
					if(s1num==3)
					{
						shi--;
						if(shi==-1)
							shi=23;
						write_sfm(4,shi);
						write_com(0x80+0x40+4);
					}
				}
			}
		}
}
void main()
{
	init();
	while(1)
	{
		keyscan();
		
	}
//	while(1);
}

void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	count++;
if(count==18)
		{
			count=0;
			miao++;
			if(miao==60)
			{
				miao=0;
				fen++;
				if(fen==60)
				{
					fen=0;
					shi++;
					if(shi==24)
					{
						shi=0;
					}
					write_sfm(4,shi);
				}
				write_sfm(7,fen);
			}
			write_sfm(10,miao);
			
		}	
}

