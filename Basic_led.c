#include<reg52.h>
sbit led = P1^2;
void delay_ms(unsigned int ms);
void main()
{
    while(1) //Infinity loop
    {
         while(1)
            {
                if(led == 1)
                {
                   led = 0;
                   delay_ms(500);
                }  
 
               else{
                      led = 1;
                      delay_ms(500);
               }
           }
    }
}
void delay_ms(unsigned int ms) // to blink the led, add delay between switching from 0 to 1 //
{
    unsigned int i,j;
    for(i=0;i<ms;i++)
        for(j=0;j<127;j++);
    
}