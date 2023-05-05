#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ADC/ADC_LIB.h"
#include "UART/UART_LIB.h"

/*
	TEMP      0   a  50°C
	HUM       100 a  0
	PRESSURE  700 a 1100
*/
float temp=25, hum=36, pressure=45;
int conver;

int main(void)
{
    ADC_Init();
	UART1_Init(9600);
	
    while (1) 
    {
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

