#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <string.h>

#include "ADC/ADC_LIB.h"
#include "UART/UART_LIB.h"


float temp, humedad, vel;
int conver;

char letra;
char bufferIn[50];

char dataCompletada=0, idx=0;

int main(void)
{
    
	DDRC &= ~( (1<<0) | (1<<1) | (1<<2)  );
	
	UART1_Init(9600);
	ADC_init();
	
	UCSR0B |= (1<<RXCIE0);
	sei();
	
    while (1) 
    {
		conver = ADC_read(0);
		temp   = 150.0/307*conver;
		
		conver  = ADC_read(1);
		humedad = 100.0/1023.0*conver;
		
		conver = ADC_read(2);
		vel    = 50.0/1023.0*conver;
		
		UART1_Transmit_Printf("# %5.1f / %5.1f / %4.1f * \r\n", temp, humedad, vel );
		
		if(dataCompletada==1){
			if( strstr(bufferIn,"BTNA=1" ) ){
				//encenderLEDA
				UART1_Transmit_Printf("LED A ENCENDIDO \r\n");
			}
			else if( strstr(bufferIn,"BTNA=0" ) ){
				//apagar LEDA
				UART1_Transmit_Printf("LED A APAGADO \r\n");
			}
			
			memset(bufferIn,' ',49);
			idx=0;
			dataCompletada=0;
			
		}
		
		_delay_ms(500);
		
    }
}

ISR(USART0_RX_vect){
	letra = UART1_Receive();
	if(letra == '#'){
		dataCompletada = 1;
	}
	else{
		bufferIn[idx] = letra;
		idx++;
	}
}