/**********************HJ-C52实验开发板例程************************
*  名称：PWM调光    
*  公司：慧净电子科技有限公司
*  网站：http://shop37031453.taobao.com/          www.hlmcu.com
*  编写：慧净电子会员
*  日期：2008-8-08
*   QQ : 121350852 398115088
*  晶振:11.0592MHZ
*  内容：通过PWM（脉宽调制）调节LED的亮度
*  硬件事项：LED边上的，J1要用短路帽短接
******************************************************************/
#include<reg52.h> //包含头文件，一般情况不需要改动，
                  //头文件包含特殊功能寄存器的定义

/*-------------------------IO口定义----------------------------*/
sbit P20 = P2^0;//这是为了关闭开发板上的数码管实际应用去掉
sbit P21 = P2^1;//这是为了关闭开发板上的数码管实际应用去掉
sbit CS88 = P2^2;//这是为了关闭开发板上的点阵实际应用去掉


sbit LED0=P1^0;// 用sbit 关键字 定义 LED到P1.0端口，LED是自己任意定义且容易记忆的符号


void Delay(unsigned int t); //函数声明
/*------------------------------------------------
                    主函数
------------------------------------------------*/
void main (void)
{
                  
unsigned int CYCLE=600,PWM_LOW=0;//定义周期并赋值

	P1=0x00;//这是为了关闭开发板上的数码管实际应用去掉
	P20=0; //这是为了关闭开发板上的数码管实际应用去掉
	P21=0; //这是为了关闭开发板上的数码管实际应用去掉
	CS88=0; //这是为了关闭开发板上的点阵实际应用去掉
	P1=0xFF;//P1口置1
	
while (1)         //主循环
  {
 LED0=1;
 Delay(60000);        //特意加延时，可以看到熄灭的过程
 for(PWM_LOW=1;PWM_LOW<CYCLE;PWM_LOW++){ //PWM_LOW表示低
 //电平时间，这个循环中低电平时长从1累加到CYCLE（周期）的值，即600次

   		LED0=0;        //点亮LED  
   		Delay(PWM_LOW);//延时长度，600次循环中从1加至599
   		LED0=1;        //熄灭LED
  	    Delay(CYCLE-PWM_LOW);//延时长度，600次循环中从599减至1
     
   }
 LED0=0;
 for(PWM_LOW=CYCLE-1;PWM_LOW>0;PWM_LOW--){ //与逐渐变亮相反的过程

   		LED0=0;
   		Delay(PWM_LOW);
   		LED0=1;
  	    Delay(CYCLE-PWM_LOW);
     
   }
                     //主循环中添加其他需要一直工作的程序
  }
}
/*------------------------------------------------
 延时函数，含有输入参数 unsigned int t，无返回值
 unsigned int 是定义无符号整形变量，其值的范围是
 0~65535
------------------------------------------------*/
void Delay(unsigned int t)
{
 while(--t);
}