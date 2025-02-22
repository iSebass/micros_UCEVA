#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "TWI/TWI_LIB.h"

#define PCF1  0b0100000<<1
#define PCF2  0b0100101<<1
#define PCF3  0b0111000<<1

char contador1=0;
char contador2=255;
char data;

int main(void){
	
	TWI_Init();
	
	
    while(1){
		
		TWI_Start();
		TWI_Write(PCF3 | 1);
		data = TWI_ReadNack();
		TWI_Stop();
		
		TWI_Start();
		TWI_Write(PCF1 | 0 );
		TWI_Write(data);
		TWI_Stop();
		
		TWI_Start();
		TWI_Write(PCF2 | 0 );
		TWI_Write(contador1);
		TWI_Stop();
		
		_delay_ms(200);
		contador2--;
		contador1++;
		
    }
}

