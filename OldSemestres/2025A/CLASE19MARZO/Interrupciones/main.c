#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void)
{
	DDRB |= (1<<0);
	
	DDRA = 0xFF;
	
    //CONFIGURAR LA INTERRUPCION POR FALLING
	//EICRA |= (1<<ISC01);
	//EICRA |= (1<<ISC00);
	EICRA &= ~(1<<ISC01);
	EICRA &= ~(1<<ISC00);
	
	//HABILITAMOS LA INTERRUPCION POR INT0
	EIMSK |= (1<<INT0);
	
	//HABILITAR LA INTERRUPCION GLOBAL
	sei();
	
	//APAGA LAS INTERRUPCIONES GLOBALES
	//cli();
	
    while (1) 
    {
		for(int i=0; i<=7; i++){
			PORTA  |= (1<<i);
			_delay_ms(500);
		}
		
		for(int i=0; i<=7; i++){
			PORTA  &= ~(1<<i);
			_delay_ms(500);
		}
    }
}


ISR(INT0_vect){
	PORTB ^= (1<<0);
	
}
