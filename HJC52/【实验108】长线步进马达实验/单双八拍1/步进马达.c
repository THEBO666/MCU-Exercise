/*************************************************************************************
*  标题:  步进电机试验一															 *
* 																					 *
*    通过本例程了解步进马达使用及驱动程序编写										 *
*;   单双八拍工作方式：                                                           	 *
*;   A-AB-B-BC-C-CD-D-DA (即一个脉冲,转 3.75 度)      								 *
*                     	                                                        	 *
*  请学员一定要消化掉本例程                       	                            	 *
                    	                          									 *
**************************************************************************************/  
 #include "reg52.h"
 //Motor
sbit F1 = P1^0;
sbit F2 = P1^1;
sbit F3 = P1^2;
sbit F4 = P1^3;

 ///////////////////////////////////////
//步进电机驱动
unsigned char MotorStep=0;
unsigned int  MotorTimer = 0;
unsigned int  MotorDelay,Speed=1,TIM,CT;

/*****************************************************
*	    初始化马达							         *
******************************************************/
void InitMotor()
{
  F1 = 1;
  F2 = 1;
  F3 = 1;
  F4 = 1;
}


 
void SetMotor()
{
  //  if(Speed == 0) return;

    MotorDelay=Speed;
    switch(MotorStep)
    {
       case 0:
          if(TIM)   // A
          {				    
            F1 = 0;		    //0xf1  
            F2 = 1;
			F3 = 1;
            F4 = 1;
            MotorStep = 1;
			TIM=0;
          }
       break;

       case 1:		 // AB
         if(TIM)
          {	
            F1 = 0;		   //0xf3 
            F2 = 0;
           	F3 = 1;
            F4 = 1;
            MotorStep = 2;
			TIM=0;
          }
       break;

       case 2:	   //B
         if(TIM)
          {
           
          	F1 = 1;
            F2 = 0;		  //0xf2 
            F3 = 1;
            F4 = 1;
           
            MotorStep = 3;
			TIM=0;
          }
       break;


       case 3:		//BC
         if(TIM)
          {	
            F1 = 1;
            F2 = 0;		    //0xf6
            F3 = 0;
            F4 = 1;
            MotorStep = 4;
			TIM=0;
          }
       break;
     case 4:		 //C
         if(TIM)
          {	
            F1 = 1;
            F2 = 1;		    //0xf4
            F3 = 0;
            F4 = 1;
            MotorStep = 5;
			TIM=0;
           }
       break;
	case 5:			  //CD
         if(TIM)
          {	
            F1 = 1;
            F2 = 1;		    //0xfc
            F3 = 0;
            F4 = 0;
            MotorStep = 6;
			TIM=0;
          }
       break;
	case 6:			  //D
         if(TIM)
          {	
            F1 = 1;
            F2 = 1;		    //0xf8
            F3 = 1;
            F4 = 0;
            MotorStep = 7;
			TIM=0;
          }
       break;
	case 7:			//DA
         if(TIM)
          {	
            F1 = 0;
            F2 = 1;		    //0xf9
            F3 = 1;
            F4 = 0;
            MotorStep = 0;
			TIM=0;
          }
       break;
	
	}

}


void system_Ini()
{
    TMOD|= 0x11;
    TH0=0xDC; //11.0592M
    TL0=0x00;	
	IE = 0x8A;	
    TR0  = 1;


}

main() 
 { system_Ini();
   InitMotor();
    while(1)
	{
	 SetMotor();

	 }



  }

/************************************************
*												*
*	      定时中断延时						    *
************************************************/
  void Tzd(void) interrupt 1
{
   TH0 = 0xfe;    //11.0592
	 TL0 = 0x33;

	if( CT++==10) 
	  {TIM=1;
	   CT=0;
	  }
 }
