/*************************HL-1开发板实验例程**********************
*  平台：HL-1 V8.0 + Keil U3 + STC89C52
*  名称：4*4键盘检测程序,按下键后相应的代码显示在数码管上
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hjmcu.com
*  编写：慧净
*  日期：2008-8-08
*   QQ : 121350852    398115088
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://hjdz.5d6d.net
******************************************************************/

#include<reg51.h>
sbit beep=P2^3;
sbit dula=P2^6;
sbit wela=P2^7;
         unsigned char i=100;
unsigned char j,k,temp,key;
void delay(unsigned char i)
{
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
display(unsigned char num)
{
         P0=table[num];
         dula=1;
         dula=0;
         P0=0xc0;
         wela=1;
         wela=0;
}
void main()
{
  dula=0;
  wela=0;
  while(1)
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
               key=0;
               break;

          case 0xde:
               key=1;
               break;

          case 0xbe:
               key=2;
               break;

          case 0x7e:
               key=3;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
           beep=0;
         }
         beep=1;
        display(key);
         P1=0xfe;
      }
    }
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
               key=4;
               break;

          case 0xdd:
               key=5;
               break;

          case 0xbd:
               key=6;
               break;

          case 0x7d:
               key=7;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
           beep=0;
         }
         beep=1;
         display(key);
      }
      }
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
               key=8;
               break;

          case 0xdb:
               key=9;
               break;

          case 0xbb:
               key=10;
               break;

          case 0x7b:
               key=11;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
           beep=0;
         }
         beep=1;
        display(key);
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
               key=12;
               break;

          case 0xd7:
               key=13;
               break;

          case 0xb7:
               key=14;
               break;

          case 0x77:
               key=15;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
           beep=0;
         }
         beep=1;
        display(key);
      }
    }
  }
}
