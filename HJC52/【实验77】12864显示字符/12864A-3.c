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
/*******************************************************************/
/*                                                                 */
/* 单片机开发系统演示程序 - 128*64LCD显示显示  */
/*                                                                 */
//;*  LCD型号：TS12864A-3（带汉字库）或兼容型号    控制器ST7920      */
//;*  MCU:AT89S52 ,晶体频率：11.0592MHz                              */
/*                                                                 */
/*******************************************************************/

#include <reg51.h>
#include <intrins.h>
	
#define uchar unsigned char
#define uint  unsigned int
/*12864端口定义*/
#define LCD_data  P0             //数据口
sbit LCD_RS  =  P1^0;            //寄存器选择输入 
sbit LCD_RW  =  P1^1;            //液晶读/写控制
sbit LCD_EN  =  P2^5;            //液晶使能控制
sbit LCD_PSB =  P1^2;            //串/并方式控制
sbit wela    =  P2^6;
sbit dula    =  P2^7;

uchar code dis1[] = {"慧净电子"};
uchar code dis2[] = {"www.hjmcu.com"};
uchar code dis3[] = {"HL-1  学习板 "};
uchar code dis4[] = {"是您最好的选择！ "};

#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};
uchar IRDIS[2];
uchar IRCOM[4];
void delay0(uchar x);  //x*0.14MS
void beep();
void  dataconv();
void lcd_pos(uchar X,uchar Y);  //确定显示位置
/*******************************************************************/
/*                                                                 */
/*  延时函数                                                       */
/*                                                                 */
/*******************************************************************/
void delay(int ms)
{
    while(ms--)
	{
      uchar i;
	  for(i=0;i<250;i++)  
	   {
	    _nop_();			   
		_nop_();
		_nop_();
		_nop_();
	   }
	}
}		
/*******************************************************************/
/*                                                                 */
/*检查LCD忙状态                                                    */
/*lcd_busy为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据。      */
/*                                                                 */
/*******************************************************************/
bit lcd_busy()
 {                          
    bit result;
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    delayNOP();
    result = (bit)(P0&0x80);
    LCD_EN = 0;
    return(result); 
 }
/*******************************************************************/
/*                                                                 */
/*写指令数据到LCD                                                  */
/*RS=L，RW=L，E=高脉冲，D0-D7=指令码。                             */
/*                                                                 */
/*******************************************************************/
void lcd_wcmd(uchar cmd)
{                          
   while(lcd_busy());
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    _nop_();
    _nop_(); 
    P0 = cmd;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0;  
}
/*******************************************************************/
/*                                                                 */
/*写显示数据到LCD                                                  */
/*RS=H，RW=L，E=高脉冲，D0-D7=数据。                               */
/*                                                                 */
/*******************************************************************/
void lcd_wdat(uchar dat)
{                          
   while(lcd_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0; 
}
/*******************************************************************/
/*                                                                 */
/*  LCD初始化设定                                                  */
/*                                                                 */
/*******************************************************************/
void lcd_init()
{ 

    LCD_PSB = 1;         //并口方式
    
    lcd_wcmd(0x34);      //扩充指令操作
    delay(5);
    lcd_wcmd(0x30);      //基本指令操作
    delay(5);
    lcd_wcmd(0x0C);      //显示开，关光标
    delay(5);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delay(5);
}
/*********************************************************/
/*														 */
/* 主程序           									 */
/*                                                       */
/*********************************************************/
  main()
 {
    uchar i;
    delay(10);                 //延时
    wela=0;
	dula=0; 
    lcd_init();                //初始化LCD             
  
    lcd_pos(0,0);             //设置显示位置为第一行的第1个字符
     i = 0;
    while(dis1[i] != '\0')
     {                         //显示字符
       lcd_wdat(dis1[i]);
       i++;
     }
    lcd_pos(1,0);             //设置显示位置为第二行的第1个字符
     i = 0;
    while(dis2[i] != '\0')
     {
       lcd_wdat(dis2[i]);      //显示字符
       i++;
     }
 	 lcd_pos(2,0);             //设置显示位置为第三行的第1个字符
     i = 0;
    while(dis3[i] != '\0')
     {
       lcd_wdat(dis3[i]);      //显示字符
       i++;
     }
	 lcd_pos(3,0);             //设置显示位置为第四行的第1个字符
     i = 0;
    while(dis4[i] != '\0')
     {
       lcd_wdat(dis4[i]);      //显示字符
       i++;
     }
     while(1);
}



/*********************************************************/
/*														 */
/* 延时x*0.14ms子程序									 */
/*                                                       */
/*********************************************************/

void delay0(uchar x)    //x*0.14MS
{
  uchar i;
  while(x--)
 {
  for (i = 0; i<13; i++) {}
 }
}
/*********************************************************/
/*                                                       */
/* 设定显示位置                                          */
/*                                                       */
/*********************************************************/
void lcd_pos(uchar X,uchar Y)
{                          
   uchar  pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;  
   lcd_wcmd(pos);     //显示地址
}