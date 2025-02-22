#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


#define getB0()  (PINB & (1<<0))
#define getB1()  (PINB & (1<<1))

int main(void)
{
    DDRD = 0xFF;
	DDRB &= ~( (1<<0) | (1<<1) );

    while (1) 
    {
		for(char i =0; i<=7; i++){
			PORTD = (1<<i);
			_delay_ms(100);
		}
		for(char i =0; i<=7; i++){
			PORTD = (128>>i);
			_delay_ms(100);
		}
    }
}

