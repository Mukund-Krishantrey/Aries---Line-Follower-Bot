#include <reg52.h>
sbit l2 = P0^0;/*initialize vairables for taking input from port 0*/
sbit  l1= P0^1;
sbit r1 = P0^2;
sbit r2 = P0^3;
sbit PWM_Pinl = P2^2;/* Two pins for pwm value of left and right wheel, and two pins each for two wheels motion direction*/
sbit PWM_Pinr = P2^5;
sbit ml1=P2^0;
sbit ml2=P2^1;
sbit mr1=P2^3;
sbit mr2=P2^4;
void InitPWM_timer();//various functions used //
void pleft();
void pright();
void left();
void right();
void forw();
void stop();

unsigned char PWM = 0; // can take values from 0 to 255 for controlling speed of motor//
unsigned int temp = 0; // used inside Timer0_ISR//
unsigned int check =0; // takes value accroding to the motion the motor undertakes//
char a=1; //takes 0 or 1 for stopping motor//
int main(void)
{
	l2=1;//to initialize a pin as input pin, we have to give it logic 1//
	l1=1;
	r1=1;
	r2=1;
	InitPWM_timer(); // Timer 0 initialize//
	/* we have used 4 ir sensors. According to the output of these 4 ir sensors we assign value to motor pins, from P2^0 to P2^5.*/
	while(1)
	{
		if((l2==1) && (l1==1) && (r1==1) && (r2==1))// All pins 1 1 1 1 means stop//
		stop();
		else if((l2==1)||(r2==1))
		{
			if(l2==1) // If outermost left is 1 and all else 0, then we call pleft//
			pleft();
			else if(r2==1)
			pright();
		}
		else if((l1==1)||(r1==1))
		{
			if((l1==1)&&(r1==1))// If both inner pins are on white line, then move forward//
			forw();
			else if(l1==1)//If only one of them is on the white line, then tuern in that direction, but speed of turn slower than when outermost on white line//
			left();
			else if(r1==1)
			right();
		}
		else // If none of the ir sensors are on white line then assign value to 'check' so as to move in the required way//
		{
			if(check==1)
			pleft();
			else if(check==2)
			left();
			else if(check==3)
			right();
			else if(check==4)
			pright();
		}
	}
}

/*in motor driver, for moving a wheel in anti-clockwise, logic '1 0' is required, and in clockwise logic '0 1' is required. 
'0 0' or '1 1' stops the wheel.*/	

void stop() 
{
	ml1=1;
	ml2=1;
	mr1=1;
	mr2=1;
	PWM = 0;
	a=1; // to make motor stop, if 'a'=0 then only motor moves//
}

/* In usage of Pulse width modulation to control speed of motor, we consider PWM=255 as 100 percent, so whatever percentage speed is required,
corresponding PWM value is used*/

void pleft() //Power left or left with more speed//
{
	ml1=0;
	ml2=0;
	mr1=1;
	mr2=0;
	a=0;
	PWM=200; // Calculated PWM values according to speed of wheel required is assign to the 'PWM' variable //
	check=1; // Assigning corresponding value to 'check' for when ir sensors go into all black zone //
}
void pright() //Power right//
{
	ml1=1;
	ml2=0;
	mr1=0;
	mr2=0;
	a=0;
	PWM=200;
	check=4;
}

void forw() // Forward//
{
	ml1=1;
	ml2=0;
	mr1=1;
	mr2=0;
	a=0;
	PWM=170;
}

void left() 
{
	ml1=0;
	ml2=0;
	mr1=1;
	mr2=0;
	a=0;
	PWM=180;
	check=2;
}

void right()
{
	ml1=1;
	ml2=0;
	mr1=0;
	mr2=0;
	a=0;
	PWM=180;
	check=3;
}

void InitPWM_timer () // Initialize Timer 0//
{
	TMOD &= 0xF0;    // Clear 4-bits field for Timer 0 which we are going to use here//
	TMOD |= 0x01;    // Set Timer 0 to operate in mode 1//
	
	TH0 = 0x00;		// First time value //     
	TL0 = 0x00;   // Can be any arbitrary value//	
	
	ET0 = 1;   // Enable timer 0 interrupts//
	EA  = 1;   // Enable global interrupts//      
	
	TR0 = 1;   // Start timer 0//      
}


void Timer0_ISR (void) interrupt 1   //When the timer 0 generates an interupt then control is transferred here//
{
	TR0 = 0;   // Stop timer 0 here//

	if(PWM_Pinl==1 && a==0) // the PWM_Pinl & PWM_Pinr remain 0 for (255-PWM) * 1 {maximum possible frequency} //
	{
		PWM_Pinl = 0;
		PWM_Pinr = 0;
		temp = (255-PWM); 
		TH0  = 0xFF;
		TL0  = 0xFF - temp&0xFF; // initialize TL0 for next run of timer0 //	
	}
	else if(PWM_Pinl==0 && a==0) // the PWM_Pinl & PWM_Pinr remain 0 for (255-PWM) * 1 {maximum possible frequency} //    
	{
		PWM_Pinl = 1;
		PWM_Pinr = 1;
		temp = PWM;
		TH0  = 0xFF;
		TL0  = 0xFF - temp&0xFF;
	}

	TF0 = 0;  // clear interupt flag //
	TR0 = 1;  //   start timer0 //
}
				
