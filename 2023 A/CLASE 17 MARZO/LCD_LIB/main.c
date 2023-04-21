#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD/LCD_LIB.h"

int contador=0;
float temp=26.5;

char fig_0[8]={14,14,4,14,14,4,14,14};
	
char texto[34]="Hola todos, todas y todes        ";
char aux[34]=" ";

int main(void)
{
    lcd_init();
	lcd_disable_cursor();
	lcd_disable_blink();
	

	
	
    while (1) 
    {
		//lcd_clear();
		lcd_set_cursor(1,1);
			for(int i=0; i<=19; i++){
				lcd_write(texto[i]);
				
			}
		for(int i=0; i<=33; i++){
			aux[i]=texto[i];
		}
		
		for(int i=0; i<=33; i++){
			if(i==33){
				texto[i] = aux[0];
			}
			else{
				
				texto[i] = aux[i+1];
			}
		}
		
	
		_delay_ms(200);
    }
}

