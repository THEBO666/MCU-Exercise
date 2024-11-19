	ORG 0000H
	LJMP MAIN
	ORG 0003H
	LJMP LINT0
	ORG 000BH
	LJMP TIME0
	ORG 0030H
MAIN:
	MOV P1,#07FH
	SETB IT0
	SETB EX0
	SETB EA
	
LOOP:
	AJMP LOOP
LINT0:
	MOV P1,#0FFH
	MOV R0, #10;设置循环次数
	MOV R1, #8;偏移量
	MOV DPTR, #LEDTABLE
	MOV	TMOD,#01H		;设置T0方式1定时模式
	MOV	TL0,#0B0H		;TL0赋初值
	MOV TH0,#03CH		;TH0赋初值，总定时50ms
	SETB	ET0				;允许T0中断
	SETB	TR0			  ;启动T0计数
	SETB 	EA
	MOV	R2,#20			;计数器1
	;MOV   A, R1;将偏移量赋值给A
	;MOVC A, @A + DPTR
	MOV P1, #90H;把A赋值给P1
	RETI
TIME0:   
	MOV	TL0,#0B0H		;恢复定时器初值
	MOV	TH0,#3CH		
	DJNZ R2,SS			;当R1不为0时，跳出中断，又开始计时，为0时，将R1的循环次数恢复，为下一次循环做准备
	MOV	R2,#20
	MOV   A, R1;将偏移量赋值给A
	MOVC A, @A + DPTR
	MOV P1,A
	DEC R1
	DJNZ R0,SS
	CLR ET0
	CLR TR0
	MOV P1,#07FH
SS:	  	    
	    RETI	    
	
LEDTABLE:
	DB 0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H
	
END	