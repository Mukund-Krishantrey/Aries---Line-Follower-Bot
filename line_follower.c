#include <reg52.h>
sbit l1 = P0^0;/*initialize vairables for taking input from port 0*/
sbit c = P0^1;
sbit r1 = P0^2;
sbit PWM_Pinl = P2^2;/* Two pins for pwm value of left and right wheel, and two pins each for two wheels motion direction*/
sbit PWM_Pinr = P2^5;
sbit ml1=P2^0;
sbit ml2=P2^1;
sbit mr1=P2^3;
sbit mr2=P2^4;
void InitPWM_timer(void);

unsigned char PWM = 0;	  // can take values from 0 to 255 for controlling speed of motor//
unsigned int temp = 0;    // used inside Timer0_ISR//
char a=1; //takes 0 or 1 for stopping motor//
int main(void)
{
	l1=1;
	c=1;
	r1=1;
	PWM_Pinl=0;
	PWM_Pinr=0;
	while(1)
	{
			ml1=1;   //to initialize a pin as input pin, we have to give it logic 1//
			ml2=0;
			mr1=1;
			mr2=0;
		if((l1==0)&&(c==1)&&(r1==0)) //move in straight line if only the centre ir sensor is on white line//
		{
			PWM = 180; // PWM value to adjust motor speed //
			a=0;
		}
		else
		{
			PWM = 0;
			a=1;
		}
	}
}

void InitPWM_timer (void) // Initialize Timer 0//
{
	TMOD &= 0xF0;    // Clear 4-bits field for Timer 0 which we are going to use here//
	TMOD |= 0x01;    // Set Timer 0 to operate in mode 1//
	
	TH0 = 0x00;   // First time value //  
	TL0 = 0x00;   // Can be any arbitrary value//	   
	
	ET0 = 1;    // Enable timer 0 interrupts//    
	EA  = 1;    // Enable global interrupts//     
	
	TR0 = 1;    // Start timer 0//     
}


void Timer0_ISR (void) interrupt 1   //When the timer 0 generates an interupt then control is transferred here//
{
	TR0 = 0;   // Stop timer 0 here//

	if(PWM_Pinl==1 && a==0)    // the PWM_Pinl & PWM_Pinr remain 0 for (255-PWM) * 1 {maximum possible frequency} //
	{
		PWM_Pinl = 0;
		PWM_Pinr = 0;
		temp = (255-PWM); 
		TH0  = 0xFF;
		TL0  = 0xFF - temp&0xFF;	
	}
	else if(PWM_Pinl==0 && a==0)   // the PWM_Pinl & PWM_Pinr remain 0 for (255-PWM) * 1 {maximum possible frequency} //   
	{
		PWM_Pinl = 1;
		PWM_Pinr = 1;
		temp = PWM;
		TH0  = 0xFF;
		TL0  = 0xFF - temp&0xFF;
	}

	TF0 = 0;    // clear interupt flag // 
	TR0 = 1;    //   start timer0 //
}