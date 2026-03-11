#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRA = 0xFF;
	PORTA = 0xFF;
	
	PORTA &=  ~(1<<6);   // ALT + 126 
	PORTA &=  ~( (1<<3) | (1<<0) | (1<<5));
	
    while (1) 
    {
    }
}

