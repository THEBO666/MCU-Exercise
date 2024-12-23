#include <STC89C5xRC.H>
#include "led.h"

void Beep(unsigned char ena)
{
	if(ena)
		BEEP=1;
	else
		BEEP=0;
}

void Relay(unsigned char ena)
{
	if(ena)
		RELAY=1;
	else
		RELAY=0;
}