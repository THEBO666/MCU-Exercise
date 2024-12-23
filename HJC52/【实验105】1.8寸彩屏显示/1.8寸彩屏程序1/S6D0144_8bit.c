/**********************51ʵ�鿪��������************************
*  ƽ̨��HL-1 HJ-C52 + Keil U4 + STC89C52
*  ���ƣ�TFT1.8����ʵ��2 ��ɫ��ʾ
*  ��˾���۾����ӿƼ����޹�˾
*  �Ա���http://shop37031453.taobao.com       
*  ��վ��www.hjmcu.com
*  ��д���۾�
*  ���ڣ�2008-8-08
*   QQ : 121350852 398115088
*  ����:11.0592MHZ
*  ˵������ѿ�Դ�����ṩԴ���������������ֱ�ӵ��۾���̳����
*  ��̳��http://hjdz.5d6d.net
*  ģ�����ӷ������ӵ�HL-1 HJ-C52 LCD12864�ӿڣ������ӵ�λ��W1 ͬLCD1602�Աȶ�һ����һ��Ҫע��15�ŵķ���λ�ã����ܽӴ�����Ӵ��յ��������۾������ޡ����˻���
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
#define RED            0x001F
#define YELLOW         0x051F
#define BLUE           0xF800
#define Magenta        0xF81F//��ɫ
#define Green          0x03E0
#define Green1         0x07E0//ǳ��
#define BLUE2          0x0FE0//ǳ��
/**************************TFT�ӿڶ���**************************/
//8λָ��/���ݿ�
//����ֱ�Ӳ�ӵ�������оϵ�е�Ƭ��ʵ���ǵ������ϵ�TFT�ӿ������ϣ���1PIN���룬TFT�ӿ������ϵ�16PIN�ճ�
#define Data_port P0
sbit CS=P1^5;  //ע�⣬��IO��Ϊ�͵�ƽ����HL-1ѧϰ���ϵ�W1��λ�����ڵ��ұߣ�ʹCS��λ�͵�ƽ�Ϳ�����
sbit RST=P1^4;
sbit RS=P1^0;
sbit WR_=P1^1;
sbit RD_=P2^5;

/**************************��������**************************/
void write_data(uchar in_data);
void write_com(uchar in_com);
void delay(uint time);
void initial();
void test_patten(uchar cl,uchar ch);
void display_colorbar(void);

void main(void)
     {
     initial();     
     test_patten(0xf8,0x00);
     delay(1000);
     test_patten(0x07,0xe0);
	 delay(1000);
     test_patten(0x00,0x1f);
	 delay(1000);
     test_patten(0xff,0xff);
	 delay(1000);
     test_patten(0x00,0x00);
	 delay(1000);
	 display_colorbar();
	 while(1);
    }

void delay(uint time)
     {
    uint i;
    while(time--)
         for(i=0;i<1000;i++);
    }


void write_data(uchar Data)//д8λ����
     {
     RS=1;
     CS=0;
     Data_port=Data;
     WR_=0;
     WR_=1;
     CS=1;
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


void test_patten(uchar cl,uchar ch)
{
    uint i,j;

     write_com(0x21);
     write_data(0x00);
     write_data(0x00);
     write_com(0x22);
    for(i=0;i<X_add;i++)
       for(j=0;j<Y_add;j++)
         {
          write_data(cl);
          write_data(ch);
         }
}


void display_colorbar(void)
{
     int i;
     write_com(0x21);
     write_data(0x00);
     write_data(0x00);
     write_com(0x22);
	  for(i=0;i<128*160/4;i++)
	     {
		  write_data(0xF8);
		  write_data(0x00);
    	  		  }
	 for(i=0;i<128*160/4;i++)
	     {
		   write_data(0x07);
	           write_data(0xe0);
    	  		  }
	 for(i=0;i<128*160/4;i++)
	     {
		   write_data(0x00);
		   write_data(0x1F);
    	  		  }
	 for(i=0;i<128*160/4;i++)
	     {
		   write_data(0xFF);
		   write_data(0xFF);
    	  		  }
}




