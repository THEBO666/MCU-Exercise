dula bit P2.0;	  
wela bit P2.1;
CS88	EQU	P2.2
SETB	CS88

KEYBUF      EQU 30H
 ORG 00H
START:      MOV KEYBUF,#2
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
            mov p1,#11111110b
            LJMP DK1
NK1:        CJNE A,#0DH,NK2
            MOV KEYBUF,#4
            mov p1,#11111100b
            LJMP DK1
NK2:        CJNE A,#0BH,NK3
            MOV KEYBUF,#8
            mov p1,#11111000b
            LJMP DK1
NK3:        CJNE A,#07H,NK4
            MOV KEYBUF,#12
            mov p1,#11110000b
            LJMP DK1
NK4:        NOP
DK1:
            call display
            
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
            mov p1,#11111110b
            LJMP DK2
NK5:        CJNE A,#0DH,NK6
            MOV KEYBUF,#5
            mov p1,#11111100b
            LJMP DK2
NK6:        CJNE A,#0BH,NK7
            MOV KEYBUF,#9
            mov p1,#11111000b
            LJMP DK2
NK7:        CJNE A,#07H,NK8
            MOV KEYBUF,#13
            mov p1,#11110000b
            LJMP DK2
NK8:        NOP
DK2:
            call display
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
            mov p1,#11111110b
            LJMP DK3
NK9:        CJNE A,#0DH,NK10
            MOV KEYBUF,#6
            mov p1,#11111100b
            LJMP DK3
NK10:       CJNE A,#0BH,NK11
            MOV KEYBUF,#10
            mov p1,#11111000b
            LJMP DK3
NK11:       CJNE A,#07H,NK12
            MOV KEYBUF,#14
            mov p1,#11110000b
            LJMP DK3
NK12:       NOP
DK3:
            call display
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
            mov p1,#11111110b
            LJMP DK4
NK13:       CJNE A,#0DH,NK14
            MOV KEYBUF,#7
             mov p1,#11111100b
            LJMP DK4
NK14:       CJNE A,#0BH,NK15
            MOV KEYBUF,#11
             mov p1,#11111000b
            LJMP DK4
NK15:       CJNE A,#07H,NK16
            mov p1,#11110000b
            MOV KEYBUF,#15
            LJMP DK4
NK16:       NOP
DK4:
            call display
DK4A:       MOV A,P3
            ANL A,#0FH
            XRL A,#0FH
            JNZ DK4A
NOKEY4:
            LJMP WAIT
DELY10MS:
            MOV R6,#10
D1:         MOV R7,#248
            DJNZ R7,$
            DJNZ R6,D1
            RET
            
            
display:    MOV A,KEYBUF        ;查表
            MOV DPTR,#TABLE
            MOVC A,@A+DPTR
            
            MOV P0,A
            setb dula
            clr dula
            mov P0,#0c0h
            setb wela
            clr wela
            clr p2.3
            acall ds1ms         ;延时，以便人眼可以观察到
            setb p2.3
           ;acall ds1ms
            ret
            
ds1ms: mov r1,#1
ds1lo: mov r2,#200
ds2lo: mov r3,#200
       djnz r3,$
       djnz r2,ds2lo
       djnz r1,ds1lo
       ret ;延时返回
TABLE:      DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H
            DB 7FH,6FH,77H,7CH,39H,5EH,79H,71H
            END
