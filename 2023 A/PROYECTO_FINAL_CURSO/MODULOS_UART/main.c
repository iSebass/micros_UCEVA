#define F_CPU 16000000UL
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "UART/UART_LIB.h"


#define PIN_TRI     0
#define PORT_TRI    PORTB
#define DIR_TRI     DDRB
#define READ_TRI    PINB

#define PIN_ECHO     1
#define PORT_ECHO    PORTB
#define DIR_ECHO     DDRB
#define READ_ECHO    PINB



char strUart[100]=" ";


unsigned int getDistance();

int main(void){
	DDRB  |=  (1<<0);
	DDRB  &= ~(1<<1);
	uart_init();
    while(1){
		sprintf(strUart,"distancia: %03d \r\n", getDistance());
		uart_write_text(strUart);
		
		
		
		_delay_ms(500);
		
    }
}

unsigned int getDistance(){
	unsigned int contador=0;
	PORTB |= (1<<0);
	_delay_us(10);
	PORTB &= ~(1<<0);
	
	
	while( ( (1<<1) & PINB ) == 0  );
	while( ( (1<<1) & PINB ) != 0  ){
		contador++;
		_delay_us(58);
	}
		
	return contador;		
}

