
#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

char contador=0;

int main(void)
{
    DDRA = 0xFF;
	DDRB &= ~(1<<PINB0);
    while (1) 
    {
		if( (PINB & (1<<0)) != 0 ){
			while( (PINB & (1<<0)) != 0 );
			
			contador++;
			
		}
		PORTA = contador;
    }
}

