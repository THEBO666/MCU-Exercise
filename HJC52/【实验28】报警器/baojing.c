/**********************HJ-3Gʵ�鿪��������************************
*  ƽ̨��HJ-3G V6.0 + Keil U3 + STC89C52
*  ���ƣ�����HJ-3G ʵ����ϵ�S2����ʱ��һֱ���ţ����ᷢ��Ƶ��Ϊ1000HZ��2000HZ����
			���źţ�ͨ�����������������ھȻ��������ı�������
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

#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char 
#define uint unsigned int

sbit beep=P2^3;
sbit kaiguan=P3^4;

void delay()		   //���0.5ms���ҵ���ʱ
{
	uchar a;
	for(a=450;a>0;a--)
	{
		_nop_();
	}
}
void main()
{
	while(1)
	{
		if(!kaiguan)
		{
			uint m;
			for(m=800;m>0;m--)	  //����ʱ��0.5ms*800
			{
				beep=~beep;		
				delay();		 //2000HZ���źš�
			}
			for(m=500;m>0;m--)	 //����ʱ��0.5ms*2*500
			{
				beep=~beep;
				delay();
				delay();		//1000HZ���źš�
			}
		}
	}
}