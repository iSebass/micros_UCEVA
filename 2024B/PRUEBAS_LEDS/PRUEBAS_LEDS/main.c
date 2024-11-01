/*
 * PRUEBAS_LEDS.c
 *
 * Created: 30/09/2024 10:57:04 a. m.
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "ADC/ADC_LIB.h"
#include "LCD/LCD_LIB.h"
#include "HCSR04/HCSR04_LIB.h"
#include "UART/UART_LIB.h"


float s1,s2,s3,s4,s5;
uint8_t val, mask=0;
int conver;

int main(void)
{
	DDRB = 0xFF;
	UART1_Init(9600);
    ADC_init();
	while (1) 
    {	
		conver = ADC_read(A0);
		s1 = 5.0*conver/1023.0;
		
		conver = ADC_read(A1);
		s2 = 5.0*conver/1023.0;
		
		conver = ADC_read(A2);
		s3 = 5.0*conver/1023.0;
		
		conver = ADC_read(A3);
		s4 = 5.0*conver/1023.0;
		s4 = (s4-0.2 - 0.500) * 100.0;
		
		conver = ADC_read(A4);
		s5 = 5.0*conver/1023.0;
		
		UART1_Transmit_Printf("S1: %4.1f S2: %4.1f S3: %4.1f S4: %4.1f", s1,s2,s3,s4);
		UART1_Transmit_Text("\r\n");
		UART1_Transmit_Printf("TEMP: %4.1f", s5);
		UART1_Transmit_Text("\r\n");
		
		val = (int)(s1*255/5.0);
		// Resetear la máscara antes de actualizarla
		mask = 0;
		
		if (val >= 32) {
			mask |= (1 << 0); // LED 1 encendido
		}
		if (val >= 64) {
			mask |= (1 << 1); // LED 2 encendido
		}
		if (val >= 96) {
			mask |= (1 << 2); // LED 3 encendido
		}
		if (val >= 128) {
			mask |= (1 << 3); // LED 4 encendido
		}
		if (val >= 160) {
			mask |= (1 << 4); // LED 5 encendido
		}
		if (val >= 192) {
			mask |= (1 << 5); // LED 6 encendido
		}
		if (val >= 224) {
			mask |= (1 << 6); // LED 7 encendido
		}
		if (val == 255) {
			mask |= (1 << 7); // LED 8 encendido (máximo)
		}
		
		// Actualizar el puerto B con la máscara para encender los LEDs
		PORTB = mask;
		
		_delay_ms(50); // Espera de medio segundo
		
    }
}

