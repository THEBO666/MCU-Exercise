	RS	EQU	P1.0  //数据命令选择
	RW	EQU	P1.1   //数据读写
	E	EQU	P2.5  //使能
	LCDDATA EQU	P0  //数据
	KEYBUF EQU 30H
	ORG	0000H
	AJMP	START 
	ORG	0033H
START:	
	MOV	SP,#60H
	MOV KEYBUF,#00H
WAIT:
            MOV P3,#0FFH
            CLR P3.4
            MOV A,P3
            ANL A,#0FH
            XRL A,#0FH
            JZ NOKEY1
            LCALL DELY10MS
            MOV A,P3
            ANL A,#0FH
            XRL A,#0FH
            JZ NOKEY1
            MOV A,P3
            ANL A,#0FH
            CJNE A,#0EH,NK1
            MOV KEYBUF,#0
            //mov p1,#11111110b
            LJMP DK1
NK1:        CJNE A,#0DH,NK2
            MOV KEYBUF,#4
            //mov p1,#11111100b
            LJMP DK1
NK2:        CJNE A,#0BH,NK3
            MOV KEYBUF,#8
            //mov p1,#11111000b
            LJMP DK1
NK3:        CJNE A,#07H,NK4
            MOV KEYBUF,#12
            //mov p1,#11110000b
            LJMP DK1
NK4:        NOP
DK1:
            LCALL display
            
DK1A:       MOV A,P3      ;等待释放
            ANL A,#0FH
            XRL A,#0FH
            JNZ DK1A
NOKEY1:
            MOV P3,#0FFH
            CLR P3.5
            MOV A,P3
            ANL A,#0FH
            XRL A,#0FH
            JZ NOKEY2
            LCALL DELY10MS
            MOV A,P3
            ANL A,#0FH
            XRL A,#0FH
            JZ NOKEY2
            MOV A,P3
            ANL A,#0FH
            CJNE A,#0EH,NK5
            MOV KEYBUF,#1
            //mov p1,#11111110b
            LJMP DK2
NK5:        CJNE A,#0DH,NK6
            MOV KEYBUF,#5
            mov p1,#11111100b
            LJMP DK2
NK6:        CJNE A,#0BH,NK7
            MOV KEYBUF,#9
            //mov p1,#11111000b
            LJMP DK2
NK7:        CJNE A,#07H,NK8
            MOV KEYBUF,#13
            //mov p1,#11110000b
            LJMP DK2
NK8:        NOP
DK2:
            LCALL display
DK2A:       MOV A,P3           ;释放
            ANL A,#0FH
            XRL A,#0FH
            JNZ DK2A
NOKEY2:
            MOV P3,#0FFH
            CLR P3.6
            MOV A,P3
            ANL A,#0FH
            XRL A,#0FH
            JZ NOKEY3
            LCALL DELY10MS
            MOV A,P3
            ANL A,#0FH
            XRL A,#0FH
            JZ NOKEY3
            MOV A,P3
            ANL A,#0FH
            CJNE A,#0EH,NK9
            MOV KEYBUF,#2
            //mov p1,#11111110b
            LJMP DK3
NK9:        CJNE A,#0DH,NK10
            MOV KEYBUF,#6
           //mov p1,#11111100b
            LJMP DK3
NK10:       CJNE A,#0BH,NK11
            MOV KEYBUF,#10
            //mov p1,#11111000b
            LJMP DK3
NK11:       CJNE A,#07H,NK12
            MOV KEYBUF,#14
            //mov p1,#11110000b
            LJMP DK3
NK12:       NOP
DK3:
            LCALL display
DK3A:       MOV A,P3
            ANL A,#0FH
            XRL A,#0FH
            JNZ DK3A
NOKEY3:
            MOV P3,#0FFH
            CLR P3.7
            MOV A,P3
            ANL A,#0FH
            XRL A,#0FH
            JZ NOKEY4
            LCALL DELY10MS
            MOV A,P3
            ANL A,#0FH
            XRL A,#0FH
            JZ NOKEY4
            MOV A,P3
            ANL A,#0FH
            CJNE A,#0EH,NK13
            MOV KEYBUF,#3
            //mov p1,#11111110b
            LJMP DK4
NK13:       CJNE A,#0DH,NK14
            MOV KEYBUF,#7
             //mov p1,#11111100b
            LJMP DK4
NK14:       CJNE A,#0BH,NK15
            MOV KEYBUF,#11
             //mov p1,#11111000b
            LJMP DK4
NK15:       CJNE A,#07H,NK16
            //mov p1,#11110000b
            MOV KEYBUF,#15
            LJMP DK4
NK16:       NOP
DK4:
            LCALL display
DK4A:       MOV A,P3
            ANL A,#0FH
            XRL A,#0FH
            JNZ DK4A
NOKEY4:
            LJMP WAIT	
display:
	LCALL DELAY
	MOV LCDDATA,#01H
	LCALL ENABLE
	MOV	LCDDATA,#38H		;写指令38H,设定LCD为16*2显示，5*7 点阵，8位数据接口
	LCALL	ENABLE
	MOV	LCDDATA,#0FH		;写指令0FH,显示ON,光标ON,闪烁ON
	LCALL	ENABLE
	MOV	LCDDATA,#06H		;写指令06H,光标输入方式增量移位
	LCALL	ENABLE
	MOV	R1,#1
	MOV	LCDDATA,#80H		;第一行起始字符地址
	LCALL	ENABLE
	MOV DPTR,#TABLE
	LCALL DISP
	RET
ENABLE:
	CLR RS
	CLR RW
	CLR E
	LCALL DELAY
	SETB E
	RET
DISP:	MOV	A,KEYBUF		;将ACC清零
	MOVC	A,@A+DPTR	;查表取得要显示的数据
	LCALL	DISP1		;写入一个数据
	INC	DPTR		;数据表指针加1,准备取下一个数据
	DJNZ	R1,DISP		;一行没有显示完就继续
	RET
;----------------- 
DISP1:	
	MOV	LCDDATA,A		;写1字节数据到显示端口 
	SETB	RS	;写数据时序(请参照1602LCD使用说明 书)
	CLR	RW 
	CLR	E
	LCALL	DELAY
	SETB	E
	RET
DELAY:			;@12.000MHz
	PUSH	30H
	PUSH	31H
	MOV		30H,#30
	MOV		31H,#38
NEXT:
	DJNZ	31H,NEXT
	DJNZ	30H,NEXT
	POP		31H
	POP		30H
	RET
DELY10MS:
            MOV R6,#10
D1:         MOV R7,#248
            DJNZ R7,$
            DJNZ R6,D1
            RET

TABLE:
	DB "0","1","2","3","4","5"
	DB "6","7","8","9","A","B"
	DB "C","D","E","F"
	END