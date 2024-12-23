#include<reg52.h> //包含单片机寄存器的头文件
sbit led1=P1^0;
sbit led2=P1^2;
sbit led5=P1^5;
sbit du=P2^6;//段选
sbit we=P2^7;//位选
sbit s1=P3^4;
sbit s2=P3^5;
sbit s3=P3^6;
sbit s4=P3^7;
sbit beep=P2^3;
sbit dot=P0^7;
unsigned char shi,fen,miao,unit,keyv,key,av,ashi,afen,amiao;

void delay()   //1ms
  {
      unsigned char a,b;
     
        for(b=102;b>0;b--)
          for(a=3;a>0;a--);
  }  

void delay5(void)   //误差 5ms
{
    unsigned char a,b;
    for(b=15;b>0;b--)
        for(a=152;a>0;a--);
}

void delayhalf (void)   //误差 0.5s
{
    unsigned char a,b,c;
    for(c=23;c>0;c--)
        for(b=152;b>0;b--)
            for(a=70;a>0;a--);
}


void display( unsigned char h,f,s)
 {
unsigned char code duma[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x38};
unsigned char code mawei[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
unsigned char shiwan,wan,qian,bai,shi,ge;

shiwan=h/10;
wan=h%10;
qian=f/10;
bai=f%10;
shi=s/10;
 ge=s%10;

 P0=duma[shiwan];
  du=1;
  du=0;
  P0=mawei[0];
  we=1;
  we=0;
 delay();
  
  P0=duma[wan];
  dot=1;
  du=1;
  du=0;
  dot=0;
P0=mawei[1];
  we=1;
  we=0;
 delay();  
  
  P0=duma[qian];
  du=1;
  du=0;
  P0=mawei[2];
  we=1;
  we=0;
 delay();

P0=duma[bai];
  dot=1;
  du=1;
  du=0;
  dot=0;
P0=mawei[3];
  we=1;
  we=0;
 delay();

if(key!=1&&key!=2)
 {
P0=duma[shi];
  du=1;
  du=0;
  P0=mawei[4];
  we=1;
  we=0;
 delay();

 P0=duma[ge];
  du=1;
  du=0;
  P0=mawei[5];
  we=1;
  we=0;
  delay();
 }
if(key==1||key==2)//
 {
P0=duma[10];
  du=1;
  du=0;
  P0=mawei[4];
  we=1;
  we=0;
 delay();

 P0=duma[11];
  du=1;
  du=0;
  P0=mawei[5];
  we=1;
  we=0;
 delay(); 
 }
 
  P0=0xff;
  we=1;
  we=0;
}
////////////////////////
passtime()
{
if(unit==100)
{
miao++;
unit=0;
led1=!led1;
led2=!led2;
}
if(miao==60)
{
fen++;
miao=0;
}
if(fen==60)
{
shi++;
fen=0;
}
if(shi==24)
{
shi=0;
}
}

//////////////////////////////////////
void InitTimer0(void)//10ms
{
    TMOD = 0x01;
    TH0 = 0x0DC;
    TL0 = 0x00;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
    unit=0;
}
void Timer0Interrupt(void) interrupt 1
{
    TH0 = 0x0DC;
    TL0 = 0x00;
   unit++ ;//add your code here!
passtime();
}

void adjustment(void)
{ 
if(s1==0)
  {
  delay5();
  if(s1==0)
    {
   while(!s1);
    
    amiao=0;
    key++;
    led5=0;
    if(key==5)
      {
       key=0;
       TR0=1;
       led5=1;
      }
    } 
   }//////s1 count 
 if(s2==0)
     {
      delay5();
      if(s2==0)
        {
         while(!s2);
         if(key==1)//alram
          {
           ashi++;
           if(ashi==24)
             {
              ashi=0; 
             }
           }
           if(key==2)
          {
           afen++;
           if(afen==60)
             {
              afen=0; 
             }
           }//alram

         if(key==4)/////
          {
           miao=0;
           TR0=0;
           fen++;
           if(fen==60)
             {
              fen=0; 
             }
          } 
       if(key==3)///
          {
           miao=0;
           TR0=0;
           shi++;
           if(shi==24)
             {
              shi=0; 
             }
          }      
   
        }
     }//adj +
 
///////////////////adj-
if(s3==0)
     {
      delay5();
      if(s3==0)
        {
         while(!s3);
         if(key==1)//alram
          {
           ashi--;
           if(ashi==-1)
             {
              ashi=23; 
             }
           }
           if(key==2)
          {
           afen--;
           if(afen==-1)
             {
              afen=59; 
             }
           }//alram

         if(key==4)//
          {
           miao=0;
           TR0=0;
           fen--;
           if(fen==-1)
             {
              fen=59; 
             }
          } 
       if(key==3)///
          {
           miao=0;
           TR0=0;
           shi--;
           if(shi==-1)
             {
              shi=23; 
             }
          }      
   
        }
     }//adj -
 }
/////////////////
void alarm(void)
{
if(fen!=afen)
     {
      av=0;
     }
if(av==0)
 {
  if(shi==ashi&&fen==afen)
  {
   beep=0;
   delayhalf(); 
   beep=1;
   delayhalf();
   beep=0;
   delayhalf();
   beep=1;
  delayhalf();
 
  }
 }//av==0
}

  /*******************************************************
主函数        编程: 火星人  qq:1170675125  学习板HL-1用
********************************************************/

void main(void)
{ashi=7;afen=0;
InitTimer0();
led2=0;
while(1)
{
if(keyv==0)//close display
 {
 if(s4==0)
 {
  delay5();
  if(s4==0)
   {
   
   while(!s4);
   keyv=1;
   av=1;
    }
 }
}
if(keyv==1)
{
if(s4==0)
 {
   delay5(); 
   if(s4==0)
    { 
   while(!s4);
   keyv=0;
    }
    }
 }//close display
if(keyv==0)
  {
adjustment();

   if(key!=1&&key!=2)
     {
    display(shi,fen,miao);
     } 
     if(key==1||key==2)
        {
        display(ashi,afen,amiao);
   
        } 
   }
if(key==0||key==3||key==4)
 {
alarm();
 }
}//while
}
