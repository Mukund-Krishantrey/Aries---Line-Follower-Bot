#include <reg52.h>
sbit l1 = P0^0;  //intitialize variables to take input from ir sensors using port 0
sbit c = P0^1;
sbit r1 = P0^2;
sbit led1= P1^2; // use port 1 to give output to leds
sbit led2= P1^3;
sbit led3= P1^4;
int main(void)
{
	l1=1;
	c=1;
	r1=1;
	while(1)
	{
		if(l1==1)
		{
			led1=1;
		}
		else
		{
			led1=0;
		}
		if(c==1)
		{
			led2=1;
		}
		else
		{
			led2=0;
		}
		if(r1==1)
		{
			led3=1;
		}
		else
		{
			led3=0;
		}
	}
}