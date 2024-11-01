/*
 * UARTPRUEBA.c
 *
 * Created: 02/10/2024 08:23:03 p. m.
 * Author : USER
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART/UART_LIB.h"
#include "ADC/ADC_LIB.h"


float p1, p2, p3, p4;
int conver;

int main(void)
{
	ADC_init();
    UART1_Init(9600);
    while(1){
		conver = ADC_read(A0);
		p1 = conver*5.0/1023.0;
		
		p2 = ADC_Map( ADC_read(A1), 0, 1023, -80.0, 130.0  );
		p3 = ADC_Map( ADC_read(A2), 0, 1023,     0, 100.0  );
		p4 = ADC_Map( ADC_read(A3), 0, 1023,  20.0, 100.0  );
		
		UART1_Transmit_Printf("%3.1f / %5.1f /  %5.1f /  %5.1f  \r\n", p1,p2,p3,p4);
		
		
		_delay_ms(100);
	}
		
}

