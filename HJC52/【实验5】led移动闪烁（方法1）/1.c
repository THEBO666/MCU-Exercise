/**********************HL-1ʵ�鿪��������************************
*  ƽ̨��HL-1 V8.0 + Keil U3 + STC89C52
*  ���ƣ�ʹ��λLED��λ�ƶ�������ѭ��
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
#include <intrins.h>  //���ͷ�ļ�����������ĺ��ģ�������������λ��������
					  //�������е�_crol_(P1,y)

sbit led=P1^0;

void delay(unsigned int i)
{
	unsigned int j;
	unsigned char k;
	for(j=i;j>0;j--)
		for(k=125;k>0;k--);
}

void main()
{	P1=0xfe;
	delay(1000);
	while(1)
	{
	//	unsigned char m;
		//P1=0xfe;
	//	delay(1000);
	//	for(m=7;m>0;m--)
		{
			P1=_crol_(P1,1);   //P1������һλ��
			delay(1000);
		}
	}
}