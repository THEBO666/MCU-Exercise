#include <STC89C5xRC.H>

#include <intrins.h>
#include "lcd1602.h"
#include "key.h"
#include "stdio.h"

void clearData(char* Data)
{
	unsigned int i = 0;
	for(i=0;i<32;i++)
	{
		Data[i] = 0;
	}
}

void handleData(char *Data)
{
	int i = 0,numData = 0,numOp = 0,fix = 0,firstCount = 0;
	long tempData[8]={0};
	long sum = 0;
	char op[8]={0};
	while(Data[i] != Sum)
	{
		if((Data[i] >= '0') && (Data[i] <= '9'))
		{
			tempData[numData] = (tempData[numData] * 10) + (Data[i] - '0');
		}
		else
		{
			op[numOp] = Data[i];
			numData++;
			numOp++;
		}
		i++;
	}
	
	i = 0;
	while(op[i] != 0)
	{
		if((op[i] == Mul) && ((op[i+1] == Add) || (op[i+1] == Sub)))
		{
			tempData[i] = tempData[i] * tempData[i+1];
		}
		else if((op[i] == Div) && ((op[i+1] == Add) || (op[i+1] == Sub)))
		{
			tempData[i] = tempData[i] / tempData[i+1];
		}
		else if((op[i] == Mul)||(op[i] == Div))
		{
			if(firstCount == 0){
				fix = i;	
				firstCount = 1;
			}
			if(op[i] == Div)
			{
				tempData[fix] = tempData[fix] / tempData[i+1];
			}
			if(op[i] == Mul)
			{
				tempData[fix] = tempData[fix] * tempData[i+1];
			}
		}
		i++;
	}
	
	i = 0;
	sum = tempData[0];
	while(op[i] != 0)
	{
		if(op[i] == Add)
		{
			if(i == 0){
				sum = tempData[i] + tempData[i+1];
			}
			else
			{
				sum = sum + tempData[i+1];
			}
		}
		
		if(op[i] == Sub)
		{
			if(i == 0){
				sum = tempData[i] - tempData[i+1];
			}
			else
			{
				sum = sum - tempData[i+1];
			}
		}
		
		i++;
	}
	Lcd_ShowChar(2,1,'=');
	Lcd_ShowSignedNum(2,2,sum,5);
	//Lcd_ShowNum(2,10,tempData[0],5);
}

void main()
{
	char keyValue = 0;	
	char Data[32]={0};
	unsigned int num = 0;
	Lcd_Init();		
	//Lcd_ShowString(1,1,"6");
	while(1)
	{
		keyValue = MatrixKey();						//扫描按键
		//操作数
		if((keyValue != Sum) && (keyValue != No_Press) && (keyValue != BackSpace) && (keyValue != Clear) && (keyValue != SigClear))
		{
			Data[num] = keyValue;
			Lcd_ShowString(1,1,Data);
			num++;
		}
		//清空
		else if(keyValue == Clear)
		{
			Lcd_Clear(1);
			Lcd_Clear(2);
			clearData(Data);
			num = 0;
		}
		//单个清除
		else if(keyValue == SigClear)
		{
			Lcd_Clear(1);
			Lcd_Clear(2);
			clearData(Data);
			num = 0;
		}
		//退格
		else if(keyValue == BackSpace)
		{
			Lcd_Clear(1);
			if(num>=1){
				Data[num-1]=0;
				num = num - 1;
			}
			Lcd_ShowString(1,1,Data);
		}
		//求和
		else if(keyValue == Sum)
		{
			Data[num] = Sum;
			handleData(Data);
		}
	}
}
