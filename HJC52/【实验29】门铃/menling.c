/**********************HJ-3Gʵ�鿪��������************************
*  ƽ̨��HJ-3G V6.0 + Keil U3 + STC89C52
*  ���ƣ�ģ��������壻���йر����幦�ܡ�
		  ������HJ-3G�ϵ�S2���󣬷������ᷢ��ʮ�ζ��ݵġ��ཡ�����Ϊ���С�
		  S3���ڹرջ��ߴ����塣
		  �����崦�ڹر�ʱ������S2�����к���Ч����
*  ��˾���۾����ӿƼ����޹�˾
*  �Ա���http://shop37031453.taobao.com       
*  ��վ��www.hlmcu.com
*  ��д��
*  ���ڣ�2008-8-08
*   QQ : 121350852  398115088
*  ����:11.0592MHZ
*  ˵������ѿ�Դ�����ṩԴ���������������ֱ�ӵ��۾���̳����
*  ��̳��http://hjdz.5d6d.com
******************************************************************/
#include<reg52.h>

#define uchar unsigned char 
uchar k,ok=1;//Ĭ�Ͽ��������忪��
unsigned int j;
sbit s2=P3^4;
sbit s3=P3^5;
sbit beep=P2^3;

void delay(unsigned int i)
{
	for(j=i;j>0;j--)
	for(k=125;k>0;k--);
}

void main()
{
	while(1)
	{
		if(ok==1)
		{
			if(s3==0)
			{
				while(s3==0);
				ok=0;
			 }
		}
		else
		{
			if(s3==0)
			{
				while(s3==0);
				ok=1;
			 }
		}
		if((s2==0)&(ok==1))
		{	uchar i=5;
			for(i=5;i>0;i--)
			{
				beep=0;
				delay(800);
				beep=1;
				delay(800);
				beep=0;
				delay(1200);
				beep=1;
				delay(1300);
			}
		}
	}
}


