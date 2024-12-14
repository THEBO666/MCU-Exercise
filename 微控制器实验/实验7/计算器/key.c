#include "key.h"
#include "lcd1602.h"

char MatrixKey(void)
{
	char KeyNumber = No_Press;
	//if(P36==0){delay_ms(20);if(P36==0){while(P36==0);KeyNumber = BackSpace;}}

	P34=0,P35=1,P36=1,P37=1;

	if(P33==0){delay_ms(20);if(P33==0){while(P33==0);KeyNumber = Number0;}}
	if(P32==0){delay_ms(20);if(P32==0){while(P32==0);KeyNumber = Number7;}}
	if(P31==0){delay_ms(20);if(P31==0){while(P31==0);KeyNumber = Number4;}}
	if(P30==0){delay_ms(20);if(P30==0){while(P30==0);KeyNumber = Number1;}}

	

	P34=1,P35=0,P36=1,P37=1;
	if(P33==0){delay_ms(20);if(P33==0){while(P33==0);KeyNumber = Clear;}}
	if(P32==0){delay_ms(20);if(P32==0){while(P32==0);KeyNumber = Number8;}}
	if(P31==0){delay_ms(20);if(P31==0){while(P31==0);KeyNumber = Number5;}}
	if(P30==0){delay_ms(20);if(P30==0){while(P30==0);KeyNumber = Number2;}}
	

	P34=1,P35=1,P36=0,P37=1;
	if(P33==0){delay_ms(20);if(P33==0){while(P33==0);KeyNumber = Sum;}}
	if(P32==0){delay_ms(20);if(P32==0){while(P32==0);KeyNumber = Number9;}}
	if(P31==0){delay_ms(20);if(P31==0){while(P31==0);KeyNumber = Number6;}}
	if(P30==0){delay_ms(20);if(P30==0){while(P30==0);KeyNumber = Number3;}}
	

	P34=1,P35=1,P36=1,P37=0;
	if(P33==0){delay_ms(20);if(P33==0){while(P33==0);KeyNumber = Div;}}
	if(P32==0){delay_ms(20);if(P32==0){while(P32==0);KeyNumber = Mul;}}
	if(P31==0){delay_ms(20);if(P31==0){while(P31==0);KeyNumber = Sub;}}
	if(P30==0){delay_ms(20);if(P30==0){while(P30==0);KeyNumber = Add;}}
	
	
	
	return KeyNumber;
}