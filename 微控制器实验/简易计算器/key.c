#include "key.h"
#include "lcd1602.h"

char MatrixKey(void)
{
	char KeyNumber = No_Press;
	if(P3_6==0){delay_ms(20);if(P3_6==0){while(P3_6==0);KeyNumber = Clear;}}
	if(P3_4==0){delay_ms(20);if(P3_4==0){while(P3_4==0);KeyNumber = BackSpace;}}
	P3_4=0,P3_5=1,P3_6=1,P3_7=1;
	
	if(P3_3==0){delay_ms(20);if(P3_3==0){while(P3_3==0);KeyNumber = Number0;}}
	if(P3_2==0){delay_ms(20);if(P3_2==0){while(P3_2==0);KeyNumber = Number7;}}
	if(P3_1==0){delay_ms(20);if(P3_1==0){while(P3_1==0);KeyNumber = Number4;}}
	if(P3_0==0){delay_ms(20);if(P3_0==0){while(P3_0==0);KeyNumber = Number1;}}

	
	P3_4=1,P3_5=0,P3_6=1,P3_7=1;
	if(P3_3==0){delay_ms(20);if(P3_3==0){while(P3_3==0);KeyNumber = Point;}}
	if(P3_2==0){delay_ms(20);if(P3_2==0){while(P3_2==0);KeyNumber = Number8;}}
	if(P3_1==0){delay_ms(20);if(P3_1==0){while(P3_1==0);KeyNumber = Number5;}}
	if(P3_0==0){delay_ms(20);if(P3_0==0){while(P3_0==0);KeyNumber = Number2;}}
	
	
	P3_4=1,P3_5=1,P3_6=0,P3_7=1;
	if(P3_3==0){delay_ms(20);if(P3_3==0){while(P3_3==0);KeyNumber = Sum;}}
	if(P3_2==0){delay_ms(20);if(P3_2==0){while(P3_2==0);KeyNumber = Number9;}}
	if(P3_1==0){delay_ms(20);if(P3_1==0){while(P3_1==0);KeyNumber = Number6;}}
	if(P3_0==0){delay_ms(20);if(P3_0==0){while(P3_0==0);KeyNumber = Number3;}}
	
	P3_4=1,P3_5=1,P3_6=1,P3_7=0;
	if(P3_3==0){delay_ms(20);if(P3_3==0){while(P3_3==0);KeyNumber = Div;}}
	if(P3_2==0){delay_ms(20);if(P3_2==0){while(P3_2==0);KeyNumber = Mul;}}
	if(P3_1==0){delay_ms(20);if(P3_1==0){while(P3_1==0);KeyNumber = Sub;}}
	if(P3_0==0){delay_ms(20);if(P3_0==0){while(P3_0==0);KeyNumber = Add;}}
	
	
	
	return KeyNumber;
}