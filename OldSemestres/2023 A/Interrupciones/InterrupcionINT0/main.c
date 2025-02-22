#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB |= (1<<DDRB0)|(1<<DDRB1);
	
    EICRA |= (1<<ISC01)|(1<<ISC00);
	EIMSK |= (1<<INT0);
	
	EICRA |= (1<<ISC11)|(1<<ISC10);
	EIMSK |= (1<<INT1);
	
	sei();
	
    while (1) 
    {
		
    }
}

ISR(INT0_vect){
	PORTB ^= (1<<PORTB0);
}

ISR(INT1_vect){
	PORTB ^= (1<<PORTB1);
}