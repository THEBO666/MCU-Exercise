/**********************HJ-3Gʵ�鿪��������************************
*  ƽ̨��HJ-3G V6.0 + Keil U3 + STC89C52
*  ���ƣ���HJ-3G ʵ���������������������ʾ����3
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

sbit dula=P2^6;		//��ѡ�źŵ�����������
sbit wela=P2^7;		//λѡ�źŵ�����������

unsigned char code table[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};
						//����ܸ�λ�����
void delay(unsigned int i)
{
	unsigned int m,n;
	for(m=i;m>0;m--)
		for(n=90;n>0;n--);
}

void main()
{
	unsigned char num;
	while(1)
	{
		for(num=0;num<6;num++)
		{
			P0=table[num];	   
			wela=1;
			wela=0;

			P0=0x4f;	  //���֡�3���Ĵ���
			dula=1;
			dula=0;
			delay(1000);
		}
	}
}

