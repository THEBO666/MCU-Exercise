/**********************HL-1ʵ�鿪��������************************
*  ƽ̨��HL-1 V8.0 + Keil U3 + STC89C52
*  ���ƣ�ʹ��λLED��λ�ƶ�������ѭ�����÷�������������ֵ�ķ���
*  ��˾���۾����ӿƼ����޹�˾
*  �Ա���http://shop37031453.taobao.com       
*  ��վ��www.hjmcu.com
*  ��д���۾�
*  ���ڣ�2008-8-08
*   QQ : 121350852 398115088
*  ����:11.0592MHZ
*  ˵������ѿ�Դ�����ṩԴ���������������ֱ�ӵ��۾���̳����
*  ��̳��http://hjdz.5d6d.net
******************************************************************/

#include <reg51.h>



unsigned char table[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

void delay(unsigned int i)
{
	unsigned int j;
	unsigned char k;
	for(j=i;j>0;j--)
		for(k=125;k>0;k--);
}

void main()
{
	while(1)
	{
		unsigned char m;
		for(m=0;m<8;m++)
		{
			P1=table[m];
			delay(2000);
		}
	}
}