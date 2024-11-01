//DEFINIMOS LA VELOCIDAD CON LA QUE SE VAN A CALCULAR LOS DELAY
#define F_CPU 16000000UL

//DEFINIMOS LIBRERIAS INTERNAS PARA USO STANDARD
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>

//DEFINIMOS LIBRERIAS PROPIAS
#include "ADC/ADC_LIB.h"
#include "UART/UART_LIB.h"
#include "HCSR04/HCSR04_LIB.h"
#include "LCD/LCD_LIB.h"
#include "MAPASBITS/MAPASBITS.h"





int main(void)
{
    DDRB = 0xFF;
	DDRD = 0x0F;
	
	
    while(1){
		PORTB = PIND&0xF0;
		_delay_ms(10);
    }
}

