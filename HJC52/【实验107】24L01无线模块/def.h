//HL-1无线开发板配套NRF24L01使用说明
//接入模块之前请看图片，不能接错模块，否则会烧坏模块
//模块共有2排，10个焊针，HL-1开发板模块接口有14个，接入之前请一定要看清楚
//你的模块需要接到哪个位置上，正确的方法是接入右边10个座子上，同时焊好24L01位置
//上的三个焊点（连起来）。出货如果配套24L01的模块，出厂已焊接好。
//下载同一个程序到开发板芯片上，按下左下角第一个按钮，二个开发板会发出声音。
//按下左下角第二个按钮，D1流水灯发光管会点亮。
//程序不提供源码分析，如果把本源码用于项目开发，毕业设计，请自己修改程序。
#ifndef _DEF_
#define _DEF_

#include <reg52.h>
#include <intrins.h>


 //hard pin mapping
sbit 	MISO	=P1^7;
sbit 	MOSI	=P1^5;
sbit	SCK	    =P1^6;
sbit	CE	    =P1^4;
sbit	CSN		=P3^3;
sbit	IRQ		=P1^3;

sbit    LED1    =P2^3;
sbit    LED2    =P1^0;
sbit    KEY1    =P3^4;
sbit    KEY2    =P3^5;


/*

*/


#endif //_DEF_