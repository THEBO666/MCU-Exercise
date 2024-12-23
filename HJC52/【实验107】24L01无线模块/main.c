//HL-1无线开发板配套NRF24L01使用说明
//接入模块之前请看图片，不能接错模块，否则会烧坏模块
//模块共有2排，10个焊针，HL-1开发板模块接口有14个，接入之前请一定要看清楚
//你的模块需要接到哪个位置上，正确的方法是接入右边10个座子上，同时焊好24L01位置
//上的三个焊点（连起来）。出货如果配套24L01的模块，出厂已焊接好。
//下载同一个程序到开发板芯片上，按下左下角第一个按钮，二个开发板会发出声音。
//按下左下角第二个按钮，D1流水灯发光管会点亮。
//程序不提供源码分析，如果把本源码用于项目开发，毕业设计，请自己修改程序。


#include ".\\nRF24L01\\nRF24L01.h"
#include "def.h"

void Delay(unsigned int s)
{
	unsigned int i;
	for(i=0; i<s; i++);
	for(i=0; i<s; i++);
}


void main(void)
{
	unsigned char leng =0;
	unsigned char tf =0;
	unsigned char TxBuf[20]={0};	 // 
	unsigned char RxBuf[20]={0};	

    init_io() ;

	LED1 = 0;
	LED2 = 0;
	//TxBuf[0] = 8 ;
	TxBuf[1] = 1 ;
	TxBuf[2] = 1 ;
	nRF24L01_TxPacket(TxBuf);	// Transmit Tx buffer data
	Delay(6000);
	LED1 = 1;
    LED2 = 1;

	while(1)
	{
	    //SetRX_Mode();
    	if(KEY1 ==0 ) 
	  	{
		   	LED1 = 0; 
		    TxBuf[1] = 1 ;
		    tf = 1 ; 
			//while(KEY1 ==0);
	    }
	   if(KEY2 ==0 )
	   {
			LED2 = 0;
			TxBuf[2] = 1 ;
			tf = 1 ; 
			//while(KEY2 ==0);
	   }

	   if (tf==1)
       {	
			nRF24L01_TxPacket(TxBuf);	// Transmit Tx buffer data
			TxBuf[1] = 0x00;
			TxBuf[2] = 0x00;
			tf=0;
			Delay(1000);
			LED1 = 1;
			LED2 = 1;

			//setRxMode();
	   }

		SetRX_Mode();
   		if(nRF24L01_RxPacket(RxBuf))
		{
						
			if(	RxBuf[1]==1)
			{	 	
				LED1 = 0;
			}
			if(	RxBuf[2]==1)
			{
				LED2 = 0;
			}
			Delay(1000);
			LED1 = 1;
			LED2 = 1;
		}

		RxBuf[1] = 0x00;
		RxBuf[2] = 0x00;
	}
	
}
