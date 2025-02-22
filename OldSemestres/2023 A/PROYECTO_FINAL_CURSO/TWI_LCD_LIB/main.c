#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "TWI/TWI_LIB.h"
#include "TWI_LCD/TWI_LCD.h"

int main(void){
    
	TWI_Init();
	
	TWI_LCD_Init();
	TWI_LCD_Puts("UCEVA");
	TWI_LCD_Set_Cursor(2,1);
	TWI_LCD_Puts("Ingenierias");
	
	TWI_LCD_Backlight_Off();
	
    while(1){
		
		
    }
}

