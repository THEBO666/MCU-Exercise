/**********************HL-1ʵ�鿪��������************************
*  ƽ̨��HL-1 V8.0 + Keil U3 + STC89C52
*  ���ƣ�TFT�������Գ���
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
#include <intrins.h>
#include <sys\sys.h>
#include <lcd\lcd.h> 
/* www.hjmcu.com �۾�����
������Ի���:HL-1 HJ-3G HJ-C52�������+STC89C52оƬ  51��Ƭ����ʾ�ٶȱȽ�����
���鵽�۾�������1Tָ�����ڵ�STC��Ƭ����51�ں�STC12LE5A60S2)+33M����
*/	

main()
{ 

	while(1)
	{
		 Lcd_Init();   //tft��ʼ��
		 LCD_Clear(RED);
		 delayms(3000);
		 LCD_Clear(GREEN);
		 delayms(3000);
		 LCD_Clear(BLUE);
		 delayms(3000);

    }


}
