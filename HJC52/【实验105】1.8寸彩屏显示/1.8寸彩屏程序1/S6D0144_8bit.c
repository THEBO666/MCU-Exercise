/**********************51实验开发板例程************************
*  平台：HL-1 HJ-C52 + Keil U4 + STC89C52
*  名称：TFT1.8彩屏实验2 颜色显示
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hjmcu.com
*  编写：慧净
*  日期：2008-8-08
*   QQ : 121350852 398115088
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://hjdz.5d6d.net
*  模块链接方法：接到HL-1 HJ-C52 LCD12864接口，将板子电位器W1 同LCD1602对比度一样，一定要注意15脚的方向位置，不能接错，如果接错烧掉彩屏，慧净不保修、不退货。
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
#define RED            0x001F
#define YELLOW         0x051F
#define BLUE           0xF800
#define Magenta        0xF81F//紫色
#define Green          0x03E0
#define Green1         0x07E0//浅绿
#define BLUE2          0x0FE0//浅蓝
/**************************TFT接口定义**************************/
//8位指令/数据口
//可以直接插接到北方蓝芯系列单片机实验仪的主板上的TFT接口排座上，第1PIN对齐，TFT接口排座上的16PIN空出
#define Data_port P0
sbit CS=P1^5;  //注意，本IO口为低电平，把HL-1学习板上的W1电位器调节到右边，使CS脚位低电平就可以了
sbit RST=P1^4;
sbit RS=P1^0;
sbit WR_=P1^1;
sbit RD_=P2^5;

/**************************函数声明**************************/
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


void write_data(uchar Data)//写8位数据
     {
     RS=1;
     CS=0;
     Data_port=Data;
     WR_=0;
     WR_=1;
     CS=1;
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




