		ORG	0000H			;程序入口地址
		MOV A ,#0FEH ;1111 1110
		MOV P1,A
		LJMP	START			;跳转到START程序
	    ORG	000BH			;中断服务程序入口
	    LJMP	TIME			;中断服务程序TIME
	    ORG	0030H			;START程序起始地址
START:	
	    MOV	TMOD,#01H		;设置T0方式1定时模式
	    MOV	TL0,#0B0H		;TL0赋初值
	    MOV TH0,#03CH		;TH0赋初值，总定时50ms
	    SETB	ET0				;允许T0中断
	    SETB	TR0			  ;启动T0计数
	    SETB	EA				;允许总中断
	    MOV	R2,#20			;计数器1
LOOP:	
	    AJMP	LOOP			;等待循环
TIME:   
	    MOV	TL0,#0B0H		;恢复定时器初值
	    MOV	TH0,#3CH		
	    DJNZ	R2,SS			;当R1不为0时，跳出中断，又开始计时，为0时，将R1的循环次数恢复，为下一次循环做准备
	    MOV	R2,#20
	    RL	A			;计时到0.5s，P0.0取反
		MOV P1,A
SS:	  	    
	    RETI	    
	    END