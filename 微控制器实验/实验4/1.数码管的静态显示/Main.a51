	ORG 0000H
	DU 	EQU	P2.0
	WE	EQU	P2.1
MAIN:
	MOV P0,#00H
	SETB WE
	CLR WE
	MOV P0,#071H
	SETB P2.0
	CLR P2.0
	SJMP $
END