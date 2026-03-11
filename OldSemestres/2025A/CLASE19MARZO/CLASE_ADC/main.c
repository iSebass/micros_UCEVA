#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "ADC/ADC_LIB.h"
#include "LCD/LCD_LIB.h"

int result;
float s1, s2, s3;

int main(void)
{
	
    ADC_Init();
	lcd_init();
	lcd_disable_cursor();
	lcd_disable_blink();
	
    while (1) 
    {
		result = ADC_Read(0);
		s1 = result*5.0/1023.0;
		
		result = ADC_Read(1);
		s2 = result*150.0/307.0;
		
		result = ADC_Read(2);
		s3 = ADC_Map(result,0,266.0,-50.0,80.0);
		
		lcd_set_cursor(1,1);
		lcd_printf("S1: %3.1f",s1);
		
		lcd_set_cursor(2,1);
		lcd_printf("S2: %3.1f",s2);
		
		lcd_set_cursor(3,1);
		lcd_printf("S3: %5.1f",s3);
		
		
		
		_delay_ms(500);
		
    }
}

