#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


#define SET_DP1  0b1110
#define SET_DP2  0b1101
#define SET_DP3  0b1011
#define SET_DP4  0b0111


const int te =10;

char seven_seg[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

int main(void)
{
    DDRD = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	PORTD = seven_seg[5];
    while (1) 
    {
		PORTB = SET_DP1;
		PORTD = seven_seg[3];
		_delay_ms(te);
		
		PORTB = SET_DP2;
		PORTD = seven_seg[5];
		_delay_ms(te);
		
		PORTB = SET_DP3;
		PORTD = seven_seg[2];
		_delay_ms(te);
		
		PORTB = SET_DP4;
		PORTD = seven_seg[1];
		_delay_ms(te);
		
		
    }
}

