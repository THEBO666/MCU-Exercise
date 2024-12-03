;/*------------------------------------------------------------------*/
;/* --- STC MCU Limited ---------------------------------------------*/
;/* --- STC89-90xx Series 16-bit Timer Demo -------------------------*/
;/* --- Mobile: (86)13922805190 -------------------------------------*/
;/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
;/* --- Tel: 86-0513-55012928,55012929,55012966----------------------*/
;/* --- Web: www.STCMCU.com -----------------------------------------*/
;/* --- Web: www.GXWMCU.com -----------------------------------------*/
;/* If you want to use the program or the program referenced in the  */
;/* article, please specify in which data and procedures from STC    */
;/*------------------------------------------------------------------*/

;/* define constants */
T1MS        EQU 0FA00H                  ;1ms timer calculation method in 12T mode is (65536-18432000/12/1000)

;/* define SFR */
TEST_LED    BIT  P1.0                   ;work LED, flash once per second

;/* define variables */
COUNT DATA 20H                          ;1000 times counter (2 bytes)

;-----------------------------------------------

    ORG     0000H
    LJMP    MAIN
    ORG     000BH
    LJMP    TM0_ISR

;-----------------------------------------------

;/* main program */
MAIN:
    MOV     TMOD,#01H                   ;set timer0 as mode1 (16-bit)
    MOV     TL0,#LOW T1MS               ;initial timer0 low byte
    MOV     TH0,#HIGH T1MS              ;initial timer0 high byte
    SETB    TR0                         ;timer0 start running
    SETB    ET0                         ;enable timer0 interrupt
    SETB    EA                          ;open global interrupt switch
    CLR     A
    MOV     COUNT,A
    MOV     COUNT+1,A                   ;initial counter
    SJMP    $

;-----------------------------------------------

;/* Timer0 interrupt routine */
TM0_ISR:
    PUSH    ACC
    PUSH    PSW
    MOV     TL0,#LOW T1MS               ;reload timer0 low byte
    MOV     TH0,#HIGH T1MS              ;reload timer0 high byte
    MOV     A,COUNT
    ORL     A,COUNT+1                   ;check whether count(2byte) is equal to 0
    JNZ     SKIP
    MOV     COUNT,#LOW 1000             ;1ms * 1000 -> 1s
    MOV     COUNT+1,#HIGH 1000
    CPL     TEST_LED                    ;work LED flash
SKIP:
    CLR     C
    MOV     A,COUNT                     ;count--
    SUBB    A,#1
    MOV     COUNT,A
    MOV     A,COUNT+1
    SUBB    A,#0
    MOV     COUNT+1,A
    POP     PSW
    POP     ACC
    RETI

;-----------------------------------------------

    END

