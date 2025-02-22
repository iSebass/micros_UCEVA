#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADC/ADC_LIB.h"
#include "UART/UART_LIB.h"

/*
	TEMP      0   a  50°C
	HUM       100 a  0
	PRESSURE  700 a 1100
*/
float temp=25, hum=36, pressure=45;
int conver;

char bufferRx[50]=" ";
int idx = 0;
char interpreteRx = 0;

int main(void)
{
    ADC_Init();
	UART1_Init(9600);
	
	DDRB |= ( (1<<3)|(1<<1)|(1<<2) );
	
	
	UCSR0B |= (1<<RXCIE0);
	sei();
	
    while (1) 
    {
			if(interpreteRx == 1){
				
				if( strstr(bufferRx, "yellowON") ){
					PORTB |= (1<<3);
				}
				if( strstr(bufferRx, "yellowOFF") ){
					PORTB &= ~(1<<3);
				}
				if( strstr(bufferRx, "purpleON") ){
					PORTB |= (1<<1);
				}
				if( strstr(bufferRx, "purpleOFF") ){
					PORTB &= ~(1<<1);
				}
				if( strstr(bufferRx, "orangeON") ){
					PORTB |= (1<<2);
				}
				if( strstr(bufferRx, "orangeOFF") ){
					PORTB &= ~(1<<2);
				}
				
				idx = 0;
				for(int i=0; i<=49; i++){
					bufferRx[i]=' ';
				}
				interpreteRx = 0;
				
			}
			
			conver = ADC_Read(0);
			temp   = ADC_Map(conver, 0, 1023, 0, 50);
			
			conver = ADC_Read(1);
			hum    = ADC_Map(conver, 0, 1023, 100, 0);
			
			conver   = ADC_Read(2);
			pressure = ADC_Map(conver, 0, 1023, 700, 1100);
			
			UART1_Transmit_Printf("*%5.1f/%5.1f/%6.1f#\r\n",temp,hum,pressure);
			
			_delay_ms(50);
    }
}

ISR( USART0_RX_vect ){
	bufferRx[idx] = UART1_Receive();
	if(bufferRx[idx]=='#'){
		interpreteRx=1;
	}
	idx++;
}

