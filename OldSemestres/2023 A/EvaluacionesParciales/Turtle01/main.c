#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define S1  ( PINB&(1<<0) )
#define S2  ( PINB&(1<<1) )

void avanzar(){
	PORTB |=  ( (1<<3)|(1<<4) );
	PORTB &= ~( (1<<2)|(1<<5) );
}
void izquierda(){
	PORTB |=  ( (1<<4) );
	PORTB &= ~( (1<<2)|(1<<5)|(1<<3) );
}
void derecha(){
	PORTB |=  ( (1<<3) );
	PORTB &= ~( (1<<2)|(1<<5)|(1<<4) );
}


int main(void)
{
    DDRB  &= ~( (1<<0)|(1<<1) );
	DDRB  |=  ( (1<<2)|(1<<3)|(1<<4)|(1<<5) );
	
	derecha();
	
    while (1) 
    {
		if(S1 != 0){
			izquierda();
		}
		if(S2 != 0){
			derecha();
		}
    }
}

