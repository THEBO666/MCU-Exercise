/**********************HL-1ʵ�鿪��������************************
*  ƽ̨��HL-1 V6.2 + Keil U3 + STC89C52RD
*  ��˾���۾����ӿƼ����޹�˾
*  �Ա���http://shop37031453.taobao.com       
*  ��վ��www.hlmcu.com
*  ��д���۾�
*  ���ڣ�2008-8-08
*   QQ : 121350852 398115088
*  ����:11.0592MHZ
*  ˵������ѿ�Դ�����ṩԴ���������������ֱ�ӵ��۾���̳����
*  ��̳��http://hjdz.5d6d.com
******************************************************************/
#define uchar unsigned char 
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
sbit rs=P3^5;
sbit wr=P3^6;
sbit lcden=P3^4;
sbit s1=P3^0;
sbit s2=P3^1;
sbit s3=P3^2;
sbit rd=P3^7;
sbit beep=P2^3;
sbit dscs=P1^4;
sbit dsas=P1^5;
sbit dsrw=P1^6;
sbit dsds=P1^7;
sbit dsirq=P3^3;
uchar count,s1num,flag,flag1;
char miao,shi,fen;
uchar code table[]="  2007-7-30 MON";
uchar code table1[]="      :  :  ";
void write_ds(uchar,uchar);
void set_alarm(uchar,uchar,uchar);
uchar read_ds(uchar);void set_time();
