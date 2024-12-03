#include <STC89C5xRC.H>

unsigned char Key_Read()
{
	unsigned char temp=0;
	P30=0,P31=1,P32=1,P33=1;
	if(P34==0) temp=0;
	if(P35==0) temp=1;
	if(P36==0) temp=2;
	if(P37==0) temp=3;
	
	P30=1,P31=0,P32=1,P33=1;
	if(P34==0) temp=4;
	if(P35==0) temp=5;
	if(P36==0) temp=6;
	if(P37==0) temp=7;
	
	P30=1,P31=1,P32=0,P33=1;
	if(P34==0) temp=8;
	if(P35==0) temp=9;
	if(P36==0) temp=10;
	if(P37==0) temp=11;
	
	P30=1,P31=1,P32=1,P33=0;
	if(P34==0) temp=12;
	if(P35==0) temp=13;
	if(P36==0) temp=14;
	if(P37==0) temp=15;
	return temp;
}