#include <STC89C5xRC.H>
#include <INTRINS.H>

sbit sda = P2^1;
sbit scl = P2^0;
unsigned char AD_Read(unsigned char addr);