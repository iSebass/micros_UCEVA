#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>

//AGREGAMOS LIBRERIAS PROPIAS
#include "LCD/LCD_LIB.h"

#define getBTNUP       ( PINA & (1<<0) )
#define getBTNDOWN     ( PINA & (1<<1) )
 

char contador=0, contador2=255, buffer[20];

int main(void)
{
    lcd_init();
	
	lcd_disable_blink();
	lcd_disable_cursor();
	
	lcd_custom_char(0, );
	
    while (1) 
    {
		
		if( getBTNUP ){
			while(getBTNUP);
			contador++;
			contador2 = contador2 - contador;
		}
		
		if( getBTNDOWN ){
			while(getBTNDOWN);
			contador--;
			contador2 = contador2 - contador;
		}
		
		sprintf(buffer, "contador: %3d",contador);
		lcd_set_cursor(1,1);
		lcd_puts(buffer);
		

		lcd_set_cursor(2,1);
		lcd_printf("contador: %03d",contador2);

		
		
		_delay_ms(100);
    }
}

