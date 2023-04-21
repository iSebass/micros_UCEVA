#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRD  = 0b11111111;
	PORTD = 0x00;
    while(1) 
    {
		PORTD = 0x01;
		_delay_ms(3000);
		PORTD = 0x00;
		_delay_ms(5000);
    }
}

