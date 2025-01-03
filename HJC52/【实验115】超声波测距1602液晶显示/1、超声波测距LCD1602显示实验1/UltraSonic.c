/**********************慧净电子51实验开发板例程*******************
*  平台：HL-1 V9.6 + Keil U3 + STC89C52
*  名称：超声波测距
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hjmcu.com
*  编写：慧净
*  日期：2008-8-08
*   QQ : 121350852 398115088
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://hjdz.5d6d.net
******************************************************************/
/**********************************包含头文件**********************************/
#include <reg52.h>
#include "1602.h"
/************************************宏定义************************************/
#define VELOCITY_30C	3495       //30摄氏度时的声速，声速V= 331.5 + 0.6*温度； 
#define VELOCITY_23C	3453       //23摄氏度时的声速，声速V= 331.5 + 0.6*温度； 
/************************************位定义************************************/
sbit INPUT  = P3^2;                //回声接收端口
sbit OUTPUT = P1^5;                //超声触发端口
sbit Beep   = P2^3 ;			   // 蜂鸣器　
/********************************定义变量和数组********************************/
long int distance=0;               //距离变量
uchar table[]="    Welcome to   ";
uchar table0[]="  www.hjmcu.com  ";
uchar table1[]="There's no echo.";
uchar table2[]="  www.hjmcu.com  ";
uchar table3[]="Distance:";
uchar count;
/***********************************函数声明***********************************/
extern void initLCD();
extern void write_date(uchar date);
extern void write_com(uchar com);
extern void delay(uint x);
/******************************************************************************/
/* 函数名称  : Delay_xMs                                                      */
/* 函数描述  : 延时函数                                                       */
/* 输入参数  : x                                                              */
/* 参数描述  : 延时时间                                                       */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Delay_xMs(unsigned int x)
{
    unsigned int i,j;
    for(i = 0;i < x;i++ )
    {
        for(j = 0;j < 3;j++ )
        {
            ;
        }
    }
}
/******************************************************************************/
/* 函数名称  : Alarm                                                          */
/* 函数描述  : 蜂鸣器发声函数                                                 */
/* 输入参数  : t                                                              */
/* 参数描述  : 发声的次数                                                     */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Alarm(uchar t)
{
	uchar i;
	for(i = 0;i < t;i++)
	{
		Beep = 0;
		Delay_xMs(1000);
		Beep = 1;
		Delay_xMs(1000);
	}
}	
/******************************************************************************/
/* 函数名称  : delayt                                                         */
/* 函数描述  : 延时函数                                                       */
/* 输入参数  : x                                                              */
/* 参数描述  : 延时时间数据                                                   */
/* 返回值    : 无                                                             */
/******************************************************************************/	
void delayt(uint x)
{
    uchar j;
    while(x-- > 0)
    {
  	    for(j = 0;j < 125;j++)
        {
            ;
        }
    }
}
/******************************************************************************/
/* 函数名称  : Init_MCU                                                       */
/* 函数描述  : 初始化单片机函数                                               */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Init_MCU(void)
{
	TMOD = 0x01;	  //定时器2初始化,设置为16位自动重装模式
 	TL0 = 0x66;
	TH0 = 0xfc;	      //1ms
    ET0 = 1;	      //开定时器2
	EA = 1;		      //总中断使能
}
/******************************************************************************/
/* 函数名称  : Init_Parameter                                                 */
/* 函数描述  : 初始化参数和IO口函数                                           */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Init_Parameter(void)
{
	 OUTPUT =1;
	 INPUT = 1;
	 count = 0;
	 distance = 0;
}
/******************************************************************************/
/* 函数名称  : display_char                                                   */
/* 函数描述  : 显示字符串函数                                                 */
/* 输入参数  : point,address                                                  */
/* 参数描述  : 写入的字符串的地址指针 1602显示对应的地址                      */
/* 返回值    : 无                                                             */
/******************************************************************************/
void display_char(uchar *point,uchar address)
{
	uchar i;
	write_com(0x80 + address);
	for(i = 0;i < 16; i++)
	{
		write_date(*point);
		point++;
	}
}
/******************************************************************************/
/* 函数名称  : display                                                        */
/* 函数描述  : 显示数字                                                       */
/* 输入参数  : number，address                                                */
/* 参数描述  : number写入的数据，address地址                                  */
/* 返回值    : 无                                                             */
/******************************************************************************/	
void display(int number,uchar address)
{
	uchar b,c,d,e;
	b= (number / 1000);
	c= (number / 100) % 10;
	d = (number / 10) % 10;
	e = number % 10;

	write_com(0x80 + address);
    write_date(b + 48);
	write_date(c + 48);
	write_date(d + 48);
	write_date(46);           //小数点的ASCII
	write_date(e + 48);
    write_date(99);           //"c"的ASCII
	write_date(109);          //"m"的ASCII
}
/******************************************************************************/
/* 函数名称  : Trig_SuperSonic                                                */
/* 函数描述  : 发出声波函数                                                   */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Trig_SuperSonic(void)//出发声波
{
	 OUTPUT = 1;
	 delayt(1);
	 OUTPUT = 0;
}
/******************************************************************************/
/* 函数名称  : Measure_Distance                                               */
/* 函数描述  : 计算距离函数                                                   */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Measure_Distance(void)
{
	uchar l;
	uint h,y;
	TR0 = 1;
	while(INPUT)
    {
        ;
    }	
	TR0 = 0;
	l = TL0;
	h = TH0;
	y = (h << 8) + l;
	y = y - 0xfc66;//us部分
	distance = y + 1000 * count;//计算总时间
	TL0 = 0x66;
	TH0 = 0xfc;
	delayt(30);
	distance = VELOCITY_30C * distance / 20000;
}
/******************************************************************************/
/* 函数名称  : main                                                           */
/* 函数描述  : 主函数                                                         */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/					
void main(void)
{	
    rw = 0;
	initLCD();
	Init_MCU();
	Init_Parameter();
	Alarm(2);
	display_char(table,0x00);
	display_char(table0,0x40);
	Delay_xMs(30000);
	display_char(table2,0x00);
	display_char(table1,0x40);

	while(1)
	{
		 Trig_SuperSonic();         //触发超声波发射
		 while(INPUT == 0)          //等待回声
         {
             ;
         }
		 Measure_Distance();        //计算脉宽并转换为距离
		 display_char(table3,0x40);
		 display(distance,0x49);    //显示距离
		 Init_Parameter();          // 参数重新初始化
		 delayt(100);               //延时，两次发射之间要至少有10ms间隔
	 }	
}
/******************************************************************************/
/* 函数名称  : timer0                                                         */
/* 函数描述  : T0中断处理函数                                                 */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/
void timer0 (void) interrupt 1
{
	TF0 = 0;
	TL0 = 0x66;
	TH0 = 0xfc;
	count++;
	if(count == 18)//超声波回声脉宽最多18ms
	{
		TR0 =0;
		TL0 = 0x66;
		TH0 = 0xfc;
		count = 0;
	}
}
/******************************************************************************/
