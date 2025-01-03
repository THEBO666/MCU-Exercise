/**********************HL-1实验开发板例程************************
*  平台：HL-1 V6.2 + Keil U3 + STC89C52RD
*  名称：步进电机
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hlmcu.com
*  编写：慧净
*  日期：2008-8-08
*   QQ : 121350852 398115088
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://hjdz.5d6d.com
******************************************************************/
//本实验需要购买步进电机模块
/*-----------------------------------------------
  名称：步进电机
  内容：本程序用于测试4相步进电机常规驱动 4个按键分别控制加速、减速、开启、停止
        
		数码管显示 01-18速度等级，数字越大，速度越大
 ------------------------------------------------*/

#include <reg52.h>

#define KeyPort P3
#define DataPort P0 //定义数据端口 程序中遇到DataPort 则用P0 替换
sbit LATCH1=P2^6;//定义锁存使能端口 段锁存
sbit LATCH2=P2^7;//                 位锁存

unsigned char code dofly_DuanMa[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};// 显示段码值0~9
unsigned char code dofly_WeiMa[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//分别对应相应的数码管点亮,即位码
unsigned char TempData[8]; //存储显示值的全局变量

sbit A1=P1^0; //定义步进电机连接端口
sbit B1=P1^1;
sbit C1=P1^2;
sbit D1=P1^3;


#define Coil_AB1 {A1=1;B1=1;C1=0;D1=0;}//AB相通电，其他相断电
#define Coil_BC1 {A1=0;B1=1;C1=1;D1=0;}//BC相通电，其他相断电
#define Coil_CD1 {A1=0;B1=0;C1=1;D1=1;}//CD相通电，其他相断电
#define Coil_DA1 {A1=1;B1=0;C1=0;D1=1;}//D相通电，其他相断电
#define Coil_A1 {A1=1;B1=0;C1=0;D1=0;}//A相通电，其他相断电
#define Coil_B1 {A1=0;B1=1;C1=0;D1=0;}//B相通电，其他相断电
#define Coil_C1 {A1=0;B1=0;C1=1;D1=0;}//C相通电，其他相断电
#define Coil_D1 {A1=0;B1=0;C1=0;D1=1;}//D相通电，其他相断电
#define Coil_OFF {A1=0;B1=0;C1=0;D1=0;}//全部断电

unsigned char Speed=1;
bit StopFlag;
void Display(unsigned char FirstBit,unsigned char Num);
void Init_Timer0(void);
unsigned char KeyScan(void);
/*------------------------------------------------
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //大致延时1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
/*------------------------------------------------
                    主函数
------------------------------------------------*/
main()
{
 unsigned int i=512;//旋转一周时间
 unsigned char num;
 Init_Timer0();
 Coil_OFF
 while(1)  //正向
  { 
   num=KeyScan();    //循环调用按键扫描
   if(num==1)//第一个按键,速度等级增加
      {
	   if(Speed<18)
	   Speed++;
	  }	
   else if(num==2)//第二个按键，速度等级减小
      {
	   if(Speed>1)
	   Speed--;
	  }	
   else if(num==3)
     {
      Coil_OFF
	  StopFlag=1;
	  }
   else if(num==4)
     {
	  StopFlag=0;
	  }
  TempData[0]=dofly_DuanMa[Speed/10];//分解显示信息，如要显示68，则68/10=6  68%10=8  
  TempData[1]=dofly_DuanMa[Speed%10];
  }
}

/*------------------------------------------------
 显示函数，用于动态扫描数码管
 输入参数 FirstBit 表示需要显示的第一位，如赋值2表示从第三个数码管开始显示
 如输入0表示从第一个显示。
 Num表示需要显示的位数，如需要显示99两位数值则该值输入2
------------------------------------------------*/
void Display(unsigned char FirstBit,unsigned char Num)
{
      static unsigned char i=0;
	  

	   DataPort=0;   //清空数据，防止有交替重影
       LATCH1=1;     //段锁存
       LATCH1=0;

       DataPort=dofly_WeiMa[i+FirstBit]; //取位码 
       LATCH2=1;     //位锁存
       LATCH2=0;

       DataPort=TempData[i]; //取显示数据，段码
       LATCH1=1;     //段锁存
       LATCH1=0;
       
	   i++;
       if(i==Num)
	      i=0;


}
/*------------------------------------------------
                    定时器初始化子程序
------------------------------------------------*/
void Init_Timer0(void)
{
 TMOD |= 0x01;	  //使用模式1，16位定时器，使用"|"符号可以在使用多个定时器时不受影响		     
 //TH0=0x00;	      //给定初值
 //TL0=0x00;
 EA=1;            //总中断打开
 ET0=1;           //定时器中断打开
 TR0=1;           //定时器开关打开
 PT0=1;           //优先级打开
}
/*------------------------------------------------
                 定时器中断子程序
------------------------------------------------*/
void Timer0_isr(void) interrupt 1 
{
 static unsigned char times,i;
 TH0=(65536-1000)/256;		  //重新赋值 1ms
 TL0=(65536-1000)%256;
 
 Display(0,8);
 if(!StopFlag)
   {
  if(times==(20-Speed))//最大值18，所以最小间隔值20-18=2
   {
   times=0;
   switch(i)
       {
	    case 0:Coil_A1;i++;break;
		case 1:Coil_B1;i++;break;
		case 2:Coil_C1;i++;break;
		case 3:Coil_D1;i++;break;
		case 4:i=0;break;
	    default:break;
	   }
    }
 times++;
  }
}

/*------------------------------------------------
按键扫描函数，返回扫描键值
------------------------------------------------*/
unsigned char KeyScan(void)
{
 unsigned char keyvalue;
 if(KeyPort!=0xff)
   {
    DelayMs(10);
    if(KeyPort!=0xff)
	   {
	    keyvalue=KeyPort;
	    while(KeyPort!=0xff);
		switch(keyvalue)
		{
		 case 0xfe:return 1;break;
		 case 0xfd:return 2;break;
		 case 0xfb:return 3;break;
		 case 0xf7:return 4;break;
		 case 0xef:return 5;break;
		 case 0xdf:return 6;break;
		 case 0xbf:return 7;break;
		 case 0x7f:return 8;break;
		 default:return 0;break;
		}
	  }
   }
   return 0;
}

