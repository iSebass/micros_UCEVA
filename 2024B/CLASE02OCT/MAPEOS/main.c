/*
 * MAPEOS.c
 *
 * Created: 02/10/2024 06:28:08 p. m.
 * Author : USER
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "MAPEOS/MAPEOS.h"
#include "UART/UART_LIB.h"



char  statusBTNA, statusBTNB, statusBTNC;
int main(void)
{
	UART1_Init(9600);
    while (1) 
    {
		UART1_Transmit_Text("ING. ELECTRONICA - UCEVA :D  \r\n");
		_delay_ms(1000);
    }
}

