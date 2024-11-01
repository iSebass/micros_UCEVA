#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int contador=0;

int main(void){
    DDRB |= (1<<0);
	
	TCNT0 = 99;
	
	//PREESCALER DE 1024 101 en CS
	TCCR0B |=  (1<<CS02 | 1<<CS00);
	TCCR0B &= ~(1<<CS01);
	
	//HABILITAR LA SINTERRUPCIONES
	TIMSK0 |= (1<<TOIE0);
	sei();
	
	while(1){
    }
}

ISR( TIMER0_OVF_vect ){
	contador++;
	if(contador==50){
		PORTB ^= 1;
		contador=0;
	}
	TCNT0 = 99;
	
}

