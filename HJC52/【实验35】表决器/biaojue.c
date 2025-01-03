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

程序功能：表决器，模拟三位评委的表决，并做出判断，将结果显示于1602上。
		  共用到HJ-3G学习板上左二列的S6,S7,S10,S11,S14,S15,S18七个按键。
		  其中S18为清零键，对1602进行清屏和对相关变量清零。
		  每位评委操控两个按键，分别代表“通过”和“不通过”。
		  第一位评委控制S6（通过）与S7（不通过）；
		  第二位评委控制S10（通过）与S11（不通过）；
		  第三位评委控制S14（通过）与S15（不通过）；
		  当按“通过”次数多于“不通过”时，1602将显示“yes”，否则显示“no”。
		  在一个回合中，每位评委只有一次按键的权利，一旦按下，其操控的两个
		  按键均将被封锁，再按也不会有任何作用。除非按下清零键S18清零后开始下一回合。

************************************************************************************/

#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
sbit rs=P1^0;
sbit rw=P1^1;
sbit beep=P2^3;
sbit lcden=P2^5;

bit ok1,ok2,ok3,clear;

uchar pass,nopass,temp;
uchar table[]="yes";
uchar table1[]="no";
uchar table2[]="agree";
uchar table3[]="disagree";
uchar table4[]="   ";
uchar table5[]="  ";

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
        rw=0;
//	uchar a;
	dula=0;
	wela=0;
	write_com(0x38);
	delay(20);
	write_com(0x0c);
	delay(20);
	write_com(0x06);
	delay(20);
	write_com(0x01);
	delay(20);
		
}

void yes()
{
	uchar a;
	write_com(0x80+12);
	delay(20);
	for(a=0;a<3;a++)
	{
		write_date(table[a]);
		delay(20);
	}
}

void no()
{
	uchar a;
	write_com(0x80+0x40+12);
	delay(20);
	for(a=0;a<2;a++)
	{
		write_date(table1[a]);
		delay(20);
	}
}

void agree()
{
	uchar a;
	write_com(0x80);
	delay(20);
	for(a=0;a<5;a++)
	{
		write_date(table2[a]);
		delay(20);
	}
}

void disagree()
{
	uchar a;
	write_com(0x80+0x40);
	delay(20);
	for(a=0;a<8;a++)
	{
		write_date(table3[a]);
		delay(20);
	}
}

void keyscan()
{
    if(!ok1)
	{ 
	P3=0xfe;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delay(10);
      if(temp!=0xf0)
      {
        temp=P3;
		switch(temp)
        {
          case 0xee:
               pass++;
			   ok1=1;		//一号评委已判决。
               break;

          case 0xde:
               nopass++;
			   ok1=1;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
           beep=0;
         }
         beep=1;
      }
    }
	}
	if(!ok2)
	{
    P3=0xfd;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delay(10);
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xed:
               pass++;
			   ok2=1;
               break;

          case 0xdd:
               nopass++;
			   ok2=1;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
           beep=0;
         }
         beep=1;
      }
      }
	  }
	if(!ok3)
	{
    P3=0xfb;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delay(10);
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xeb:
               pass++;
			   ok3=1;
               break;

          case 0xdb:
               nopass++;
			   ok3=1;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
           beep=0;
         }
         beep=1;
      }
      }
	  }
	      P3=0xf7;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delay(10);
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xe7:
               clear=1;
               break;
          
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
           beep=0;
         }
         beep=1;
      }
    }
}

void main()
{
	uchar a,b;
	init();
	while(1)
	{	
		agree();
		disagree();
		keyscan();
		if(pass||nopass)
		{
			write_com(0x80+10);
			delay(20);
			write_date(0x30+pass);
			write_com(0x80+0x40+10);
			delay(20);
			write_date(0x30+nopass);
		}
		a=pass+nopass;
		if(a==3)
		{
			if(pass>nopass)
			yes();
			if(pass<nopass)
			no(); 
		}
		if(clear)
		{
			ok1=0;	ok2=0;	ok3=0;	
			pass=0;	nopass=0;	clear=0;	a=0;
			agree();
			disagree();
			write_com(0x80+10);
			delay(20);
			write_date(0x30+pass);
			write_com(0x80+0x40+10);
			delay(20);
			write_date(0x30+nopass);
	
			write_com(0x80+12);
			for(b=0;b<3;b++)
			{
				write_date(table4[b]);
				delay(20);
			}
			write_com(0x80+0x40+12);
			for(b=0;b<2;b++)
			{
				write_date(table5[b]);
				delay(20);
			} 
		} 	   
	}
}