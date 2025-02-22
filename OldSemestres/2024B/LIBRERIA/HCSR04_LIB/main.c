
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD/LCD_LIB.h"
#include "HCSR04/HCSR04_LIB.h"

int distance;



int main(void)
{
    lcd_init();
	lcd_disable_cursor();
	lcd_disable_blink();
	
	HCSR04_init();
	
    while(1){
		distance = HCSR04_readDistance();
		lcd_set_cursor(1,1);
		lcd_printf("Distance: %05d cm", distance);
    }
}

