#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "TWI/TWI_LIB.h"
#include "DS13007/DS1307_LIB.h"



int main(void){
	
	TWI_Init();
	
	DS1307_set_HH(0x15);
	DS1307_set_MM(0x35);
	DS1307_set_SS(0x55);
	DS1307_set_Year(0x23);
	DS1307_set_Month(0x05);
	DS1307_set_DAY(0x03);
	
	DS1307_set_Date(0x12);
	
	while(1){
			
			
			_delay_ms(100);
	}
}


