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
******************************************************************

//注意事项：10天教程中的LCD1602第5脚由于当时设计错误，直接接到GND上了，接了低电平。
//本实验需要把LCD1602第5脚，读/写脚接到GND上，有两种方法，第一种，用杜邦线把P3.6脚接到GND上。
//另一种方法，定义一个 P3.6 IO口，在主函数中 把P3.6 写一个低电平就可以了。
//sbit WR = P3^6; 在后面主函数中加入 WR=0;就可以不用接杜邦线， P3.6到GND的杜邦线不要。
//WR=0;

程序功能：	敲入式地显示一段语句，由于语句超过了16*2个字节，故采取了
			分屏显示的方式，共分为六屏先后显示。
*************************************************************************/

#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit beep=P2^3;

uchar code table []="I want to bring ";
uchar code table1[]="out the secret  ";
uchar code table2[]="of nature and   ";
uchar code table3[]="apply them for  ";
uchar code table4[]="the happiness of";
uchar code table5[]="man.I don't know";
uchar code table6[]="of any better s-";
uchar code table7[]="-ervice to offer";
uchar code table8[]="for the short t-";
uchar code table9[]="-ime we are in  ";
uchar code table10[]="the world.      ";
uchar code table11[]="---Thomas Edison";

sbit lcden=P2^5;
sbit lcdrs=P1^0;
sbit rw=P1^1;
sbit dula=P2^6;
sbit wela=P2^7;
uchar num;

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void write_com(uchar com)
{
	lcdrs=0;
	P0=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}

void write_data(uchar date)
{
	lcdrs=1;
	P0=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}

void init()
{	
        rw=0;
        dula=0;
        wela=0;
	lcden=0;
	write_com(0x38);
	write_com(0x0e);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80);
}
void main()
{
	init();
	for(num=0;num<16;num++)    //第一屏
	{
		beep=0;
		write_data(table[num]);
		delay(100);
		beep=1;
		delay(50);
	}
	write_com(0x80+0x40);
		for(num=0;num<16;num++)
	{
		beep=0;
		write_data(table1[num]);
		delay(100);
		beep=1;
		delay(50);
	}
	write_com(0x01); //清屏
   write_com(0x80);	 //设置字符显示位置指针于第一行
	for(num=0;num<16;num++)    // 第二屏
	{	beep=0;
		write_data(table2[num]);
		delay(100);
		beep=1;
		delay(50);
	}
	write_com(0x80+0x40); //设置字符显示位置指针于第二行
		for(num=0;num<16;num++)
	{	beep=0;
		write_data(table3[num]);
		delay(100);
		beep=1;
		delay(50);
	}
   write_com(0x80);
	write_com(0x01);
	for(num=0;num<16;num++)    //第三屏
	{	beep=0;
		write_data(table4[num]);
		delay(100);
		beep=1;
		delay(50);
	}
	write_com(0x80+0x40);
		for(num=0;num<16;num++)
	{	beep=0;
		write_data(table5[num]);
		delay(100);
		beep=1;
		delay(50);
	}
	write_com(0x01);
   write_com(0x80);
	for(num=0;num<16;num++)   //第四屏
	{	beep=0;
		write_data(table6[num]);
		delay(100);
		beep=1;
		delay(50);
	}
	write_com(0x80+0x40);
		for(num=0;num<16;num++)
	{	beep=0;
		write_data(table7[num]);
		delay(100);
		beep=1;
		delay(50);
	}
	write_com(0x01);
   write_com(0x80);
	for(num=0;num<16;num++)   //第五屏
	{	beep=0;
		write_data(table8[num]);
		delay(100);
		beep=1;
		delay(50);
	}
	write_com(0x80+0x40);
		for(num=0;num<16;num++)
	{	beep=0;
		write_data(table9[num]);
		delay(100);
		beep=1;
		delay(50);
	}
	write_com(0x01);
   write_com(0x80);

   for(num=0;num<16;num++)   //第六屏
	{	beep=0;
		write_data(table10[num]);
		delay(100);
		beep=1;
		delay(50);
	}
	write_com(0x80+0x40);
		for(num=0;num<16;num++)
	{	beep=0;
		write_data(table11[num]);
		delay(100);
		beep=1;
		delay(50);
	}
	while(1);
}
