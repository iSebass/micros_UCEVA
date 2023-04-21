#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART/UART_LIB.h"

char rxchar, interruptRxFlag=0;

int main(void){
	
	uart_init();
	
	
	DDRB |= ( (1<<0)|(1<<1) );
	
	UCSR0B |= (1<<RXCIE0);
	sei();
	
    
    while (1){
		
		
		
		
		if(interruptRxFlag==1){
			
			if(rxchar == 'a' ){
				PORTB |= (1<<0);
			}
			else if( rxchar == 'b'){
				PORTB &= ~(1<<0);
			}
			else if( rxchar == 'c'){
				PORTB |= (1<<1);
			}
			else if( rxchar == 'd'){
				PORTB &= ~(1<<1);
			}
			
			interruptRxFlag=0;
			
		}
		
    }
}

ISR( USART0_RX_vect ){
	rxchar = uart_read();
	interruptRxFlag = 1;
}