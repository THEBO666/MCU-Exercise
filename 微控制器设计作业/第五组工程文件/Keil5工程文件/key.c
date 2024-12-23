#include <STC89C5xRC.H>


unsigned char Key_Read()
{
	unsigned char temp=0;
	if(P33==0) temp=4;
	if(P32==0) temp=3;
	if(P31==0) temp=2;
	if(P30==0) temp=1;
	return temp;
}
