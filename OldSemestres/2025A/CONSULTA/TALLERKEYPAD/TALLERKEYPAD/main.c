#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD/LCD_LIB.h"
#include "KEYPAD/KEYPAD_LIB.h"

char tecla;
char buffer[16];


int main(void)
{
    KeyPad_Init();
	lcd_init();
	
	lcd_disable_blink();
	lcd_disable_cursor();
	
	lcd_puts("Presiona una tecla: ");
	
	while (1) 
    {

		
		tecla = KeyPad_KeyClick();
		if(tecla != 0 ){
			lcd_clear();
		}
		
		lcd_set_cursor(1,1);
		lcd_printf("tecla: %c", tecla);
    }
}

