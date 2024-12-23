  /**********************HL-1实验开发板例程************************
*  平台：HL-1 V8.0 + Keil U3 + STC89C52
*  名称：TFT彩屏测试程序
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hjmcu.com
*  编写：慧净
*  日期：2008-8-08
*   QQ : 121350852 398115088
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://hjdz.5d6d.net
******************************************************************/
#include <reg51.h>
#include <intrins.h>
#include <sys\sys.h>
#include <lcd\lcd.h>
#include <font\font.h>
/* www.hjmcu.com 慧净电子
代码测试环境:HL-1 HJ-3G HJ-C52开发板板+STC89C52芯片
1T指令周期的STC单片机（51内核STC12LE5A60S2)+33M晶振
程序默认IO连接方式：
控制线：RS-P3^5;    WR-P3^6;   RD-P3^7;   CS-P1^0;   REST-P1^2;
数据线: DB0-DB7依次连接P0^0-P0^7;  DB8-DB15依次连接P2^0-P2^7;（8位模式下DB0-DB7可以不连接）
触摸功能连接方式：(不使用触摸可不连接)
D_CLK-P1^7;  D_CS-P1^4;  D_DIN-P3^0;  D_OUT-P3^1;  D_PENIRQ-P3^4;
*/
u16 BACK_COLOR, POINT_COLOR;   //背景色，画笔色

#ifdef  Bus_16    //条件编译-16位数据模式   
void LCD_Writ_Bus(char VH,char VL)   //并行数据写入函数
{
    LCD_DataPortH=VH;	
	LCD_DataPortL=VL;		
	LCD_WR=0;
	LCD_WR=1; 
}
#else			//条件编译-8位数据模式 
void LCD_Writ_Bus(char VH,char VL)   //并行数据写入函数
{	
    LCD_DataPortH=VH;	
   	LCD_WR=0;
	LCD_WR=1;
	LCD_DataPortH=VL;		
	LCD_WR=0;
	LCD_WR=1;
}
#endif
void LCD_WR_DATA8(char VH,char VL) //发送数据-8位参数
{
    LCD_RS=1;
	LCD_Writ_Bus(VH,VL);
}  
 void LCD_WR_DATA(int da)
{
    LCD_RS=1;
	LCD_Writ_Bus(da>>8,da);
}	  
void LCD_WR_REG(int da)	 
{	
    LCD_RS=0;
	LCD_Writ_Bus(da>>8,da);
}
 void LCD_WR_REG_DATA(int reg,int da)
{
    LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{ 
	LCD_WR_REG(0x0046);LCD_WR_DATA8(x2,x1);	  
    LCD_WR_REG(0x0047);LCD_WR_DATA(y2);  
    LCD_WR_REG(0x0048);LCD_WR_DATA(y1);
  	LCD_WR_REG(0x0020);LCD_WR_DATA(x1);	  
    LCD_WR_REG(0x0021);LCD_WR_DATA(y1); 
    LCD_WR_REG(0x0022);					 						 
}
void Lcd_Init(void)
{

//调用一次这些函数，免得编译的时候提示警告
   	LCD_CS =1;
	if(LCD_CS==0)
	{
	   LCD_WR_REG_DATA(0,0);
	   LCD_ShowString(0,0," ");
	   LCD_ShowNum(0,0,0,0);
	   LCD_Show2Num(0,0,0,0);
	   LCD_DrawPoint_big(0,0);
	   LCD_DrawRectangle(0,0,0,0);
	   Draw_Circle(0,0,0);
 	 }

    LCD_REST=1;
    delayms(5);	
	LCD_REST=0;
	delayms(5);
	LCD_REST=1;
	LCD_CS=1;
	LCD_RD=1;
	LCD_WR=1;
	delayms(5);
	LCD_CS =0;  //打开片选使能

	LCD_WR_REG_DATA(0x11,0x2004);		
    LCD_WR_REG_DATA(0x13,0xCC00);		
    LCD_WR_REG_DATA(0x15,0x2600);	
	LCD_WR_REG_DATA(0x14,0x252A);	
//	LCD_WR_REG_DATA(0x14,0x002A);		
	LCD_WR_REG_DATA(0x12,0x0033);		
	LCD_WR_REG_DATA(0x13,0xCC04);		
	delayms(1); 
	LCD_WR_REG_DATA(0x13,0xCC06);		
	delayms(1); 
	LCD_WR_REG_DATA(0x13,0xCC4F);		
	delayms(1); 
	LCD_WR_REG_DATA(0x13,0x674F);
	LCD_WR_REG_DATA(0x11,0x2003);
	delayms(1); 	
	LCD_WR_REG_DATA(0x30,0x2609);		
	LCD_WR_REG_DATA(0x31,0x242C);		
	LCD_WR_REG_DATA(0x32,0x1F23);		
	LCD_WR_REG_DATA(0x33,0x2425);		
	LCD_WR_REG_DATA(0x34,0x2226);		
	LCD_WR_REG_DATA(0x35,0x2523);		
	LCD_WR_REG_DATA(0x36,0x1C1A);		
	LCD_WR_REG_DATA(0x37,0x131D);		
	LCD_WR_REG_DATA(0x38,0x0B11);		
	LCD_WR_REG_DATA(0x39,0x1210);		
	LCD_WR_REG_DATA(0x3A,0x1315);		
	LCD_WR_REG_DATA(0x3B,0x3619);		
	LCD_WR_REG_DATA(0x3C,0x0D00);		
	LCD_WR_REG_DATA(0x3D,0x000D);		
	LCD_WR_REG_DATA(0x16,0x0007);		
	LCD_WR_REG_DATA(0x02,0x0013);		
	LCD_WR_REG_DATA(0x03,0x0003);		
	LCD_WR_REG_DATA(0x01,0x0127);		
	delayms(1); 
	LCD_WR_REG_DATA(0x08,0x0303);		
	LCD_WR_REG_DATA(0x0A,0x000B);		
	LCD_WR_REG_DATA(0x0B,0x0003);   
	LCD_WR_REG_DATA(0x0C,0x0000);   
	LCD_WR_REG_DATA(0x41,0x0000);    
	LCD_WR_REG_DATA(0x50,0x0000);   
	LCD_WR_REG_DATA(0x60,0x0005);    
    LCD_WR_REG_DATA(0x70,0x000B);    
	LCD_WR_REG_DATA(0x71,0x0000);    
	LCD_WR_REG_DATA(0x78,0x0000);    
	LCD_WR_REG_DATA(0x7A,0x0000);   
	LCD_WR_REG_DATA(0x79,0x0007);		
	LCD_WR_REG_DATA(0x07,0x0051);   
	delayms(1); 	
	LCD_WR_REG_DATA(0x07,0x0053);		
	LCD_WR_REG_DATA(0x79,0x0000);
	
	LCD_WR_REG(0x0022);

}
//清屏函数
//Color:要清屏的填充色
void LCD_Clear(u16 Color)
{
	u8 VH,VL;
	u16 i,j;
	VH=Color>>8;
	VL=Color;	
	Address_set(0,0,LCD_W-1,LCD_H-1);
    for(i=0;i<LCD_W;i++)
	 {
	  for (j=0;j<LCD_H;j++)
	   	{
        	 LCD_WR_DATA8(VH,VL);
	    }

	  }
}
//画点
//POINT_COLOR:此点的颜色
void LCD_DrawPoint(u16 x,u16 y)
{
	Address_set(x,y,x,y);//设置光标位置 
	LCD_WR_DATA(POINT_COLOR); 	    
} 	 
//画一个大点
//POINT_COLOR:此点的颜色
void LCD_DrawPoint_big(u16 x,u16 y)
{
	LCD_Fill(x-1,y-1,x+1,y+1,POINT_COLOR);
} 
//在指定区域内填充指定颜色
//区域大小:
//  (xend-xsta)*(yend-ysta)
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	Address_set(xsta,ysta,xend,yend);      //设置光标位置 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)LCD_WR_DATA(color);//设置光标位置 	    
	} 					  	    
}  
//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//画矩形
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a);             //3           
		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0-a,y0+b);             //1       
		LCD_DrawPoint(x0-b,y0-a);             //7           
		LCD_DrawPoint(x0-a,y0-b);             //2             
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0-b);             //5
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-b,y0+a);             
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		LCD_DrawPoint(x0+a,y0+b);
	}
} 
//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"
//mode:叠加方式(1)还是非叠加方式(0)
//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"

//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode)
{
    u8 temp;
    u8 pos,t;
	u16 x0=x;
	u16 colortemp=POINT_COLOR;      
    if(x>LCD_W-16||y>LCD_H-16)return;	    
	//设置窗口		   
	num=num-' ';//得到偏移后的值
	Address_set(x,y,x+8-1,y+16-1);      //设置光标位置 
	if(!mode) //非叠加方式
	{
		for(pos=0;pos<16;pos++)
		{ 
			temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_WR_DATA(POINT_COLOR);	
				temp>>=1; 
				x++;
		    }
			x=x0;
			y++;
		}	
	}else//叠加方式
	{
		for(pos=0;pos<16;pos++)
		{
		    temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//画一个点     
		        temp>>=1; 
		    }
		}
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   
//m^n函数
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//color:颜色
//num:数值(0~4294967295);	
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len)
{         	
	u8 t,temp;
	u8 enshow=0;
	num=(u16)num;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+8*t,y,' ',0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+8*t,y,temp+48,0); 
	}
} 
//显示2个数字
//x,y:起点坐标
//num:数值(0~99);	 
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len)
{         	
	u8 t,temp;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
	 	LCD_ShowChar(x+8*t,y,temp+'0',0); 
	}
} 
//显示字符串
//x,y:起点坐标  
//*p:字符串起始地址
//用16字体
void LCD_ShowString(u16 x,u16 y,const u8 *p)
{         
    while(*p!='\0')
    {       
        if(x>LCD_W-16){x=0;y+=16;}
        if(y>LCD_H-16){y=x=0;LCD_Clear(RED);}
        LCD_ShowChar(x,y,*p,0);
        x+=8;
        p++;
    }  
}












