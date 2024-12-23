/**********************51实验开发板例程************************
*  平台：HL-1 HJ-C52 + Keil U4 + STC89C52
*  名称：TFT1.8彩屏实验1显示慧净网址+汉字+数字
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hjmcu.com
*  编写：慧净
*  日期：2008-8-08
*   QQ : 121350852 398115088
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://hjdz.5d6d.net
*  模块链接方法：接到HL-1 HJ-C52 LCD12864接口，将板子电位器W1 同LCD1602对比度一样，一定要注意16脚的方向位置，不能接错，如果接错烧掉彩屏，慧净不负责
******************************************************************/
#include <reg51.h>
#include <intrins.h>
#define X_add 128
#define Y_add 160

#define WINDOW_XADDR 0x44 // Horizontal Start Address Set,DL SETTING START POSITION,DH SETTING END POSITION
#define WINDOW_YADDR 0x45 // Vertical Start Address Set,DL SETTING START POSITION,DH SETTING END POSITION
#define GRAM_ADDR	 0x21 // GRAM Address Set,DL SETTING Horizontal Address,DH SETTING Vertical Address
                          // you can write initial GRAM address into internal Address Counter
#define GRAMWR 		 0x22 // memory write
#define uint unsigned int
#define uchar unsigned char


/**************************LCD color setting**************************/
//颜色由18为数据构成，每一基色由6bit组成 BBBBBBGGGGGGRRRRRR，最大可达64*64*64（62K）色
//在8位数据和16为数据口模式下DB0和DB9不使用，故颜色设置为BBBBBBGGXGGGRRRRRX，X表示无效位
//通常颜色中B、G、R的排列为RRRRRRGGGGGGBBBBBB，可通过初始化函数的命令修改如下
//write_com(0x03);   //ENTRY MODE
//write_data(0x00);  //BGR=1,颜色的顺序为BBBBBBGGGGGGRRRRRR;BGR=0,颜色的顺序为RRRRRRGGGGGGBBBBBB
//write_data(0x30);
#define White          0xFFFF
#define Black          0x0000
#define Red            0x001F
#define Yellow         0x051F
#define Blue           0xF800
#define Magenta        0xF81F//紫色
#define Green          0x03E0
#define Green1         0x07E0//浅绿
#define Blue2          0x0FE0//浅蓝

/**************************TFT接口定义**************************/
//8位指令/数据口
//可以直接插接到北方蓝芯系列单片机实验仪的主板上的TFT接口排座上，第1PIN对齐，TFT接口排座上的16PIN空出
#define Data_port P0
#define  nop _nop_()

sbit CS=P1^5;  //注意，本IO口为低电平，把HL-1学习板上的W1电位器调节到右边，使CS脚位低电平就可以了
sbit RST=P1^4;
sbit RS=P1^0;
sbit WR_=P1^1;
sbit RD_=P2^5;


void write_data(uchar in_data);
void write_com(uchar in_com);
void  write_data_U16(uint y);
void delay(uint time);
void initial();
static void LCD_SetPos(unsigned char xSTART,unsigned char xEND,unsigned char ySTART,unsigned char yEND);
void ClearScreen(unsigned int bColor);//	清屏
void LCD_PutChar8x16(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor);



void main(void)
{
    initial();
	ClearScreen(Blue);
	LCD_PutString(8,0,"www.hjmcu.com",White,Blue);
    LCD_PutString(15,16,"慧净电子科技",Magenta,Blue);
	LCD_PutString(15,32,"开发有限公司",Magenta,Blue);
	LCD_PutString(22,50,"I LOVE NBC ",Black,Blue);
	LCD_PutString(10,68,"慧净科技",Green1,Blue);
	LCD_PutString(50,84,"与您同行",Red,Blue);
	LCD_PutString(20,100,"1234567890",Green,Blue);
	LCD_PutString(10,114,"abcdefghijklm",Magenta,Blue);
	LCD_PutString(10,128,"nopqrstuvwxyz",Magenta,Blue);
	LCD_PutString(0,142,"`,./<>';:[]{}\|?)",Yellow,Blue);
	//LCD_PutString(0,142,"`,./<>';:[]{}\|?)(-=+*&^%$",Yellow,Blue);
	while(1);
}
/*************************************************************
函数名称:delay
功    能:
参    数:无
返 回 值:无
*************************************************************/
void delay(uint time)
{
	uint i;
	while(time--)
	for(i=0;i<10;i++);
}

/*************************************************************
函数名称:写数据/命令相关函数
功    能:
参    数:无
返 回 值:无
*************************************************************/
void write_data(uchar Data)//写8位数据
{
     RS=1;
     CS=0;
     Data_port=Data;
     WR_=0;
     WR_=1;
     CS=1;
}

void  write_data_U16(uint y)//写16位数据
{
	uchar m,n;
	m=y>>8;
	n=y;
	write_data(m);
    write_data(n);
}

void write_com(uchar Com)//写命令
{
	RS=0;
	CS=0;
	Data_port=Com;
	WR_=0;
	WR_=1;
	CS=1;
}

/*************************************************************
函数名称:TFT initial
功    能:tft控制寄存器初始化
参    数:无
返 回 值:无
*************************************************************/
void initial()
{
 
    RST=0;
    delay(10);
    RST=1;
    WR_=1;RD_=1;

    write_com(0xb4);   
    write_data(0x00);
    write_data(0x10);

    write_com(0x07);   
    write_data(0x00);
    write_data(0x00);

    write_com(0x13);   
    write_data(0x00);
    write_data(0x00);
    delay(50);

    write_com(0x12);   
    write_data(0x00);
    write_data(0x71);

    write_com(0x13);   
    write_data(0x08);
    write_data(0x0b);

    write_com(0x14);   
    write_data(0x59);
    write_data(0xcf);

    write_com(0x10);   
    write_data(0x19);
    write_data(0x10);

    write_com(0x01);   
    write_data(0x01);
    write_data(0x14);

    write_com(0x02); 
    write_data(0x01);
    write_data(0x00);

    write_com(0x03);   //ENTRY MODE
    write_data(0x10);  //BGR=1,颜色的顺序为BBBBBBGGGGGGRRRRRR;BGR=0,颜色的顺序为RRRRRRGGGGGGBBBBBB
    write_data(0x30);

    write_com(0x08);   //
    write_data(0x03);
    write_data(0x02);

    write_com(0x0b);   //FRAME CYCLE CONTROL
    write_data(0x00);
    write_data(0x00);

    write_com(0x0c);   //
    write_data(0x00);
    write_data(0x02);
    delay(50);

    write_com(0x30);   //
    write_data(0x00);
    write_data(0x00);

    write_com(0x31);   //
    write_data(0x06);
    write_data(0x05);

    write_com(0x32);   //
    write_data(0x00);
    write_data(0x07);

    write_com(0x33);   //
    write_data(0x06);
    write_data(0x00);

    write_com(0x34);   //
    write_data(0x02);
    write_data(0x04);

    write_com(0x35);   //
    write_data(0x00);
    write_data(0x02);

    write_com(0x36);   //
    write_data(0x07);
    write_data(0x07);

    write_com(0x36);   //
    write_data(0x07);
    write_data(0x07);

    write_com(0x37);   //
    write_data(0x00);
    write_data(0x00);

    write_com(0x38);   //
    write_data(0x0f);
    write_data(0x00);

    write_com(0x11);   //
    write_data(0x00);
    write_data(0x0f);

    write_com(0x40);   //
    write_data(0x00);
    write_data(0x00);

    write_com(0x42);   //
    write_data(0x9f);
    write_data(0x00);

    write_com(0x43);   //
    write_data(0x9f);
    write_data(0x00);

    write_com(0x44);   //
    write_data(0x7f);
    write_data(0x00);

    write_com(0x45);   //
    write_data(0x9f);
    write_data(0x00);

    write_com(0x13);   //
    write_data(0x08);
    write_data(0x1b);
    delay(50);

    write_com(0x07);   //
    write_data(0x00);
    write_data(0x05);
    delay(50);

    write_com(0x07);   //
    write_data(0x00);
    write_data(0x25);
    delay(50);

    write_com(0x07);   //
    write_data(0x00);
    write_data(0x27);
    delay(50);

    write_com(0x07);   //
    write_data(0x00);
    write_data(0x37);
    delay(50);
}


/*===========================================================*/

/*************************************************************
函数名称:LCD_DefineDispWindow
功    能:定义显示窗体
参    数:xSTART:  窗体中X坐标中较小者
	     xEND:  窗体中X坐标中较大者
	     ySTART:  窗体中Y坐标中较小者
	     yEND:  窗体中Y坐标中较大者 
返 回 值:无
*************************************************************/

static void LCD_SetPos(uchar xSTART,uchar xEND,uchar ySTART,uchar yEND)
{
  write_com(WINDOW_XADDR);//窗口显示行设置寄存器
  write_data(xEND);       //窗口显示结束行设置
  write_data(xSTART);     //窗口显示开始行设置
  write_com(WINDOW_YADDR);//窗口显示列设置寄存器
  write_data(yEND);       //窗口显示结束列设置
  write_data(ySTART);     //窗口显示开始列设置
  write_com(0x21);
  write_data(ySTART);
  write_data(xSTART);
  write_com(0x22);        //LCD_WriteCMD(GRAMWR);
}

void ClearScreen(unsigned int bColor)//	清屏
{
    unsigned char i,j;
 
    LCD_SetPos(0,127,0,159);//128x160
    for (i=0;i<=159;i++)
	{	
	   for (j=0;j<=127;j++)
		write_data_U16(bColor);
	}
}


#include "8X16.h"
void LCD_PutChar8x16(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor)
{
 unsigned int i,j;
 LCD_SetPos(x,x+8-1,y,y+16-1);
 for(i=0; i<16;i++) {
		unsigned char m=Font8x16[c*16+i];
		for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				write_data_U16(fColor);
				}
			else {
				write_data_U16(bColor);
				}
			m<<=1;
			}
		}
}


void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor) 
{
		LCD_PutChar8x16( x, y, c, fColor, bColor );
}


#include "GB1616.h"	//16*16汉字字模

void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor){
	unsigned int i,j,k;

	LCD_SetPos(x,  x+16-1,y, y+16-1);

	for (k=0;k<64;k++) { //64标示自建汉字库中的个数，循环查询内码
	  if ((codeGB_16[k].Index[0]==c[0])&&(codeGB_16[k].Index[1]==c[1])){ 
    	for(i=0;i<32;i++) {
		  unsigned short m=codeGB_16[k].Msk[i];
		  for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				write_data_U16(fColor);
				}
			else {
				write_data_U16(bColor);
				}
			m<<=1;
			} 
		  }
		}  
	  }	
	}


void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor) {
	 unsigned char l=0;
	while(*s) {
		if( *s < 0x80) 
		    {
			LCD_PutChar(x+l*8,y,*s,fColor,bColor);
			s++;l++;
			}
		else
		    {
			PutGB1616(x+l*8,y,(unsigned char*)s,fColor,bColor);
			s+=2;l+=2;
			}
		}
	}
