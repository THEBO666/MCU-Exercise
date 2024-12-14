

#ifndef __KEY_H
#define __KEY_H

#include <STC89C5xRC.H>
#include <intrins.h>

#define No_Press 	'F'
#define First_key	0xFE
#define Number0		'0'
#define Number1		'1'
#define Number2		'2'
#define Number3 	'3'
#define Number4		'4'
#define Number5		'5'
#define Number6 	'6'
#define Number7		'7'
#define Number8		'8'
#define Number9 	'9'
#define Rem				'%'
#define Point			'.'
#define Add				'+'
#define Sub				'-'
#define Mul				'*'
#define Div				'/'
#define BackSpace 'b'
#define Clear			'C'
#define SigClear	'c'
#define Sum				'='

char MatrixKey(void);

#endif
