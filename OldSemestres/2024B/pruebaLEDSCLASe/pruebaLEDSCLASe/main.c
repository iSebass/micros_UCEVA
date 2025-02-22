#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
    DDRB = 0xFF;
 
   
    while (1) 
    {
		PORTB ^= 0xFF;
		_delay_ms(2000);
    }
}

