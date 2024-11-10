	ORG 0000H
AJMP MAIN
MAIN:
     MOV R1,#0FFH
     CPL P2.3
	 CPL P1.0
     LCALL DELAY500MS
     AJMP MAIN

DELAY500MS:			;@12.000MHz
	PUSH	30H
	PUSH	31H
	PUSH	32H
	MOV		30H,#4
	MOV		31H,#205
	MOV		32H,#180
NEXT:
	DJNZ	32H,NEXT
	DJNZ	31H,NEXT
	DJNZ	30H,NEXT
	POP		32H
	POP		31H
	POP		30H
	RET


END