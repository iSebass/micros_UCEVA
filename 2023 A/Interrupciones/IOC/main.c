#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

char flagPCINT2=0;

int main(void){
    
	DDRB    = 0xFF;
	PCICR  |=(1<<PCIE2);
	PCMSK2 |= (1<<PCINT16);
	PCMSK2 |= (1<<PCINT17);
	
	sei();
	
	while(1){
		if(flagPCINT2 == 1){
			if( (PIND&(1<<PCINT16))!=0 ){
				PORTB |=(1<<PORTB0);
			}
			else{
				PORTB &=~(1<<PORTB0);
			}
			if((PIND&(1<<PCINT17))!=0){
				PORTB ^=(1<<PORTB1);
			}
			flagPCINT2=0;
		}
		
    }
}

ISR(PCINT2_vect){
	flagPCINT2=1;
	
}

ISR(PCINT1_vect){
	
}
