#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Libs/LCD_LIB.h"

int conver;
float volt, temp;

int main(void)
{
    lcd_init();
	lcd_disable_cursor();
	lcd_disable_blink();
	
	//PASO 1 CONFIGURAR EL CONVERSOR ADC
	ADMUX |=  (0b01 << REFS0 ); // AVCC COMO REF
	ADMUX &= ~(1 << ADLAR);     //JUSTIFICADO A LA DERECHA
	
	ADCSRA |= (1 << ADEN);      // Habilitamos el conversor;
	ADCSRA |= (0b111 << ADPS0); // Div128;
	
	//CONFIGURAMOS LOS PINES A TRABJAR
	DIDR0 |= (1<<ADC0D) | (1<<ADC1D) ;
	
	
    while(1){
		
		ADMUX &= ~( (1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3) | (1<<MUX4)  );
		ADCSRA  |= (1<<ADSC);
		while( (ADCSRA & (1<<ADSC)) !=0 );
		conver = ADC;
		
		volt = 5.0/1023.0*conver;
		
		lcd_set_cursor(1,1);
		lcd_printf("POT: %4.1f v", volt);
		
		ADMUX  |= (1<<MUX0);
		ADCSRA |= (1<<ADSC);
		while( (ADCSRA & (1<<ADSC)) !=0 );
		conver = ADC;
		
		temp = 150.0/306.0*conver;
		
		lcd_set_cursor(2,1);
		lcd_printf("LM35: %5.1f C", temp);
		_delay_ms(100);
		
    }
}

