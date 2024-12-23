/**********************HL-1实验开发板例程************************
*  平台：HL-1 V6.2 + Keil U3 + STC89C52RD
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
#define uchar unsigned char 
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
sbit rs=P3^5;
sbit wr=P3^6;

sbit lcden=P3^4;
sbit s1=P3^0;//功能键
sbit s2=P3^1;//增加键
sbit s3=P3^2;//减小键
sbit s4=P3^2;//闹钟查看键
sbit rd=P3^7;
sbit beep=P2^3;//蜂鸣器
sbit dscs=P1^4;
sbit dsas=P1^5;
sbit dsrw=P1^6;
sbit dsds=P1^7;
sbit dsirq=P3^3;
bit flag1,flag_ri;//定义两个位变量
uchar count,s1num,flag,t0_num;//其它变量定义
char miao,shi,fen,year,month,day,week,amiao,afen,ashi;
uchar code table[]=" 20  -  -      ";//液晶固定显示内容
uchar code table1[]="      :  :  ";
void write_ds(uchar,uchar);//函数申明
void set_alarm(uchar,uchar,uchar);void read_alarm();
uchar read_ds(uchar);void set_time();
