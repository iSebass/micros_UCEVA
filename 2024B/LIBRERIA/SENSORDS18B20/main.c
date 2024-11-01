/*
 * SENSORDS18B20.c
 *
 * Created: 14/09/2024 11:25:47 a. m.
 * Author : USER
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART/UART_LIB.h"
#include "DS18B20/DS18B20_LIB.h"


float temp;

int main(void)
{
    UART1_Init(9600);
	ds18b20_init();
	
    while (1) 
    {
		temp = ds18b20_get_temperature();
		UART1_Transmit_Printf("TEMP: %5.1f \r\n", temp);
		_delay_ms(500);
    }
}

