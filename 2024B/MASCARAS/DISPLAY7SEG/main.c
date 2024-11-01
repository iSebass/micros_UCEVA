#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "DISPLAY7SEG/DISPLAY7SEG_LIB.h"

char contador=0;

int main(void)
{
    DISPLAY7SEG_Init();
	
    while (1) 
    {
		for(int i=0; i<=9; i++){
			DISPLAY7SEG_CC_Set_Value(i);
			_delay_ms(500);
		}
    }
}

