/**********************51ʵ�鿪��������************************
*  ƽ̨��HL-1 HJ-C52 + Keil U4 + STC89C52
*  ���ƣ�TFT1.8����ʵ��1��ʾ�۾���ַ+����+����
*  ��˾���۾����ӿƼ����޹�˾
*  �Ա���http://shop37031453.taobao.com       
*  ��վ��www.hjmcu.com
*  ��д���۾�
*  ���ڣ�2008-8-08
*   QQ : 121350852 398115088
*  ����:11.0592MHZ
*  ˵������ѿ�Դ�����ṩԴ���������������ֱ�ӵ��۾���̳����
*  ��̳��http://hjdz.5d6d.net
*  ģ�����ӷ������ӵ�HL-1 HJ-C52 LCD12864�ӿڣ������ӵ�λ��W1 ͬLCD1602�Աȶ�һ����һ��Ҫע��16�ŵķ���λ�ã����ܽӴ�����Ӵ��յ��������۾�������
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
//��ɫ��18Ϊ���ݹ��ɣ�ÿһ��ɫ��6bit��� BBBBBBGGGGGGRRRRRR�����ɴ�64*64*64��62K��ɫ
//��8λ���ݺ�16Ϊ���ݿ�ģʽ��DB0��DB9��ʹ�ã�����ɫ����ΪBBBBBBGGXGGGRRRRRX��X��ʾ��Чλ
//ͨ����ɫ��B��G��R������ΪRRRRRRGGGGGGBBBBBB����ͨ����ʼ�������������޸�����
//write_com(0x03);   //ENTRY MODE
//write_data(0x00);  //BGR=1,��ɫ��˳��ΪBBBBBBGGGGGGRRRRRR;BGR=0,��ɫ��˳��ΪRRRRRRGGGGGGBBBBBB
//write_data(0x30);
#define White          0xFFFF
#define Black          0x0000
#define Red            0x001F
#define Yellow         0x051F
#define Blue           0xF800
#define Magenta        0xF81F//��ɫ
#define Green          0x03E0
#define Green1         0x07E0//ǳ��
#define Blue2          0x0FE0//ǳ��

/**************************TFT�ӿڶ���**************************/
//8λָ��/���ݿ�
//����ֱ�Ӳ�ӵ�������оϵ�е�Ƭ��ʵ���ǵ������ϵ�TFT�ӿ������ϣ���1PIN���룬TFT�ӿ������ϵ�16PIN�ճ�
#define Data_port P0
#define  nop _nop_()

sbit CS=P1^5;  //ע�⣬��IO��Ϊ�͵�ƽ����HL-1ѧϰ���ϵ�W1��λ�����ڵ��ұߣ�ʹCS��λ�͵�ƽ�Ϳ�����
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
void ClearScreen(unsigned int bColor);//	����
void LCD_PutChar8x16(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor);



void main(void)
{
    initial();
	ClearScreen(Blue);
	LCD_PutString(8,0,"www.hjmcu.com",White,Blue);
    LCD_PutString(15,16,"�۾����ӿƼ�",Magenta,Blue);
	LCD_PutString(15,32,"�������޹�˾",Magenta,Blue);
	LCD_PutString(22,50,"I LOVE NBC ",Black,Blue);
	LCD_PutString(10,68,"�۾��Ƽ�",Green1,Blue);
	LCD_PutString(50,84,"����ͬ��",Red,Blue);
	LCD_PutString(20,100,"1234567890",Green,Blue);
	LCD_PutString(10,114,"abcdefghijklm",Magenta,Blue);
	LCD_PutString(10,128,"nopqrstuvwxyz",Magenta,Blue);
	LCD_PutString(0,142,"`,./<>';:[]{}\|?)",Yellow,Blue);
	//LCD_PutString(0,142,"`,./<>';:[]{}\|?)(-=+*&^%$",Yellow,Blue);
	while(1);
}
/*************************************************************
��������:delay
��    ��:
��    ��:��
�� �� ֵ:��
*************************************************************/
void delay(uint time)
{
	uint i;
	while(time--)
	for(i=0;i<10;i++);
}

/*************************************************************
��������:д����/������غ���
��    ��:
��    ��:��
�� �� ֵ:��
*************************************************************/
void write_data(uchar Data)//д8λ����
{
     RS=1;
     CS=0;
     Data_port=Data;
     WR_=0;
     WR_=1;
     CS=1;
}

void  write_data_U16(uint y)//д16λ����
{
	uchar m,n;
	m=y>>8;
	n=y;
	write_data(m);
    write_data(n);
}

void write_com(uchar Com)//д����
{
	RS=0;
	CS=0;
	Data_port=Com;
	WR_=0;
	WR_=1;
	CS=1;
}

/*************************************************************
��������:TFT initial
��    ��:tft���ƼĴ�����ʼ��
��    ��:��
�� �� ֵ:��
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
    write_data(0x10);  //BGR=1,��ɫ��˳��ΪBBBBBBGGGGGGRRRRRR;BGR=0,��ɫ��˳��ΪRRRRRRGGGGGGBBBBBB
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
��������:LCD_DefineDispWindow
��    ��:������ʾ����
��    ��:xSTART:  ������X�����н�С��
	     xEND:  ������X�����нϴ���
	     ySTART:  ������Y�����н�С��
	     yEND:  ������Y�����нϴ��� 
�� �� ֵ:��
*************************************************************/

static void LCD_SetPos(uchar xSTART,uchar xEND,uchar ySTART,uchar yEND)
{
  write_com(WINDOW_XADDR);//������ʾ�����üĴ���
  write_data(xEND);       //������ʾ����������
  write_data(xSTART);     //������ʾ��ʼ������
  write_com(WINDOW_YADDR);//������ʾ�����üĴ���
  write_data(yEND);       //������ʾ����������
  write_data(ySTART);     //������ʾ��ʼ������
  write_com(0x21);
  write_data(ySTART);
  write_data(xSTART);
  write_com(0x22);        //LCD_WriteCMD(GRAMWR);
}

void ClearScreen(unsigned int bColor)//	����
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


#include "GB1616.h"	//16*16������ģ

void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor){
	unsigned int i,j,k;

	LCD_SetPos(x,  x+16-1,y, y+16-1);

	for (k=0;k<64;k++) { //64��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
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
