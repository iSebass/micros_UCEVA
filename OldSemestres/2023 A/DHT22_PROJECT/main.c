#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART/UART_LIB.h"
#include "DHT22/DHT22_LIB.h"

float temp, hum;

int main(void)
{
    UART1_Init(9600);
	
	UART1_Transmit_Text("Prueba DHT");
    while(1){
		
		switch( DHT22_ReadData(&temp, &hum ) ){
			case SUCESS: UART1_Transmit_Printf("Temp: %0.1f  Hum: %0.1f \r\n\r\n",temp,hum); break;
			case ERROR_SINCRO1: UART1_Transmit_Printf("Error PRIMER BIT DE SINCRO\r\n"); break;
			case ERROR_SINCRO2: UART1_Transmit_Printf("Error SEGUNDO BIT DE SINCRO\r\n"); break;
			case ERROR_CHECKSUM: UART1_Transmit_Printf("ERROR DE CHECKSUM\r\n"); break;
		}
		
		
		
		_delay_ms(1000);
		_delay_ms(1000);
    }
}

