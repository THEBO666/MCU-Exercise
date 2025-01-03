/**********************HL-1实验开发板例程************************
*  平台：HL-1 V6.2 + Keil U3 + STC89C52RD
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hlmcu.com
*  编写：慧净
*  日期：2008-8-08
*   QQ : 121350852 398115088
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://hjdz.5d6d.com
******************************************************************/
/*-----------------------------------------------
  名称：IIC协议 PCF8591ADDA转换		  显示有4个，注意只有2个可以调节电压的
  内容：此程序通过IIC协议对DAAD芯片操作，读取电位器的电压通过液晶显示，并输出模拟量，用LED亮度渐变指示
------------------------------------------------*/
 #include<reg52.h>    //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
 #include <intrins.h> //包含NOP空指令函数_nop_();
 #include<LCD1602.h>

 #define AddWr 0x90   //写数据地址 
 #define AddRd 0x91   //读数据地址

 sbit RST=P2^4;   //时钟 加上后可以关掉DS1302芯片输出
 sbit Sda=P2^0;       //定义总线连接端口
 sbit Scl=P2^1;
 sbit dula=P2^6;
 sbit wela=P2^7;

 bit ADFlag;          //定义AD采样标志位
unsigned char code Datatab[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//7段数共阴码管段码表
data unsigned char  Display[8];//定义临时存放数码管数值
/*------------------------------------------------
                    延时程序
------------------------------------------------*/
 void mDelay(unsigned char j)
 {
  unsigned int i;
  for(;j>0;j--)
     {
	  for(i=0;i<125;i++)
	     {;}
	  }
  }
/*------------------------------------------------
                    初始化定时器1
------------------------------------------------*/
void Init_Timer1(void)
{
 TMOD |= 0x10;			     
 TH1=0xff;	              	/* Init value */
 TL1=0x00;
 //PT1=1;                   /* 优先级    */
 EA=1;                      /* interupt enable */
 ET1=1;                     /* enable timer1 interrupt */
 TR1=1;  
}
/*------------------------------------------------
                    启动IIC总线
------------------------------------------------*/
  void Start(void)
  {
   Sda=1;
   _nop_();
   Scl=1;
   _nop_();
   Sda=0;
   _nop_();
   Scl=0;
  }


/*------------------------------------------------
                    停止IIC总线
------------------------------------------------*/
  void Stop(void)
  {
   Sda=0;
   _nop_();
   Scl=1;
   _nop_();
   Sda=1;
   _nop_();
   Scl=0;
   }


/*------------------------------------------------
                   应答IIC总线
------------------------------------------------*/
   void Ack(void)
   {
    Sda=0;
	_nop_();
	Scl=1;
	_nop_();
	Scl=0;
	_nop_();
	}


/*------------------------------------------------
                 非应答IIC总线
------------------------------------------------*/
	void NoAck(void)
	{
	 Sda=1;
	 _nop_();
	 Scl=1;
	 _nop_();
	 Scl=0;
	 _nop_();
	 }


/*------------------------------------------------
              发送一个字节
------------------------------------------------*/
	 void Send(unsigned char Data)
	 { 
	  unsigned char BitCounter=8;
	  unsigned char temp;

	  do
	    {
		 temp=Data;
		 Scl=0;
		 _nop_();
		 if((temp&0x80)==0x80)
		    Sda=1;
		 else
		    Sda=0;

			Scl=1;
			temp=Data<<1;
			Data=temp;
			BitCounter--;
		  }
	  while(BitCounter);
	      Scl=0;
	  }


/*------------------------------------------------
               读入一个字节并返回
------------------------------------------------*/
	  unsigned char Read(void)
	  {
	   unsigned char temp=0;
	   unsigned char temp1=0;
	   unsigned char BitCounter=8;

	   Sda=1;
	   do
	     {
		  Scl=0;
          _nop_();
		  Scl=1;
		  _nop_();
		  if(Sda)
		     temp=temp|0x01;
		  else
		     temp=temp&0xfe;

		  if(BitCounter-1)
		     {
			  temp1=temp<<1;
			  temp=temp1;
			  }
			  BitCounter--;
			 }
		while(BitCounter);
		return(temp);
	  }
 
/*------------------------------------------------
                    写入DA数模转换值
------------------------------------------------*/
	  void DAC(unsigned char Data)
	  {
		   Start();
		   Send(AddWr); //写入芯片地址
		   Ack();
		   Send(0x40);  //写入控制位，使能DAC输出
		   Ack();
		   Send(Data);  //写数据
		   Ack();
		   Stop();
		 
	   }

/*------------------------------------------------
                 读取AD模数转换的值，有返回值
------------------------------------------------*/
	  unsigned char ReadADC(unsigned char Chl)
	  {
       unsigned char Data;
		   Start();        //写入芯片地址
		   Send(AddWr);
		   Ack();
 		   Send(0x40|Chl);//写入选择的通道，本程序只用单端输入，差分部分需要自行添加
		                  //Chl的值分别为0、1、2、3，分别代表1-4通道
		   Ack();
		   Start();
		   Send(AddRd);    //读入地址
		   Ack();
		   Data=Read();    //读数据
		   Scl=0;
		   NoAck();
		   Stop();
		   return Data;   //返回值
	  }

void cmg(void)//数码管锁存函数		   关时钟DS1302
{
dula=1;
P0=0x00;
dula=0;
wela=1;
P0=0x00;
wela=0;
RST=0;		//		关时钟DS1302
}


/*------------------------------------------------
                   主程序
------------------------------------------------*/
	void main()
	{

 
	 unsigned char num;                   //DA数模输出变量
	 unsigned char ADtemp;                //定义中间变量
	 InitLcd();
     mDelay(20);
     Init_Timer1();
	 cmg();                                //数码管锁存
	 while(1)
	      { 
           DAC(num);       //DA输出，可以用LED模拟电压变化
		   num++;          //累加，到256后溢出变为0，往复循环。显示在LED上亮度逐渐变化
		   mDelay(20);     //延时用于清晰看出变化
		   if(ADFlag)      //定时采集输入模拟量
           {
   		ADFlag=0;

   		ADtemp=ReadADC(0);
		TempData[0]=(ReadADC(0))/50;//处理0通道电压显示
  		TempData[1]=((ReadADC(0))%50)/10;
  	
        ADtemp=ReadADC(1);
		TempData[2]=(ReadADC(1))/50;//处理1通道电压显示 此通道暂时屏蔽，可以自行添加
  		TempData[3]=((ReadADC(1))%50)/10;
  		
        ADtemp=ReadADC(2);
		TempData[4]=(ReadADC(2))/50;//处理1通道电压显示 此通道暂时屏蔽，可以自行添加
  		TempData[5]=((ReadADC(2))%50)/10;
  		
        ADtemp=ReadADC(3);
		TempData[6]=(ReadADC(3))/50;//处理1通道电压显示 此通道暂时屏蔽，可以自行添加
  		TempData[7]=((ReadADC(4))%50)/10;
  		
        disp();
		   }
	   }
	}

/*------------------------------------------------
                   定时器中断程序
------------------------------------------------*/
void Timer1_isr(void) interrupt 3 using 1//定时器1执行数码管动态扫描
{

 static unsigned int j;
 TH1=0xfb;		//重新赋值
 TL1=0x00;
 j++;
 if(j==200) 
    {j=0;ADFlag=1;} //定时置位AD采样标志位
	 
   // P0=Display[count];//用于动态扫描数码管
   // P2=count;
   // count++;
  // if(count==8)     //表示扫描8个数码管
   //   count=0;

 
}
