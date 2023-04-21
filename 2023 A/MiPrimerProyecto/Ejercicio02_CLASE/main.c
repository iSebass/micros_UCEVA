#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void secuencia_A(void);
void secuencia_B(void);
void secuencia_C(void);

const int te=100;

int main(void)
{
    DDRB  = 0xFF;
	PORTB = 0x00;
	int i=0;
    while (1) 
    {
		secuencia_A();
		for(i=0; i<=3; i++){
			secuencia_B();
		}
		for(i=0; i<=3; i++){
			secuencia_C();
		}
		
    }
}

void secuencia_A(void){
	PORTB = 0b10000001;
	_delay_ms(te);
	PORTB = 0b11000011;
	_delay_ms(te);
	PORTB = 0b11100111;
	_delay_ms(te);
	PORTB = 0b11111111;
	_delay_ms(te);
	PORTB = 0b01111110;
	_delay_ms(te);
	PORTB = 0b00111100;
	_delay_ms(te);
	PORTB = 0b00011000;
	_delay_ms(te);
	PORTB = 0b00000000;
	_delay_ms(te);
}

void secuencia_B(void){
	PORTB = 0x0F;
	_delay_ms(te);
	PORTB = 0xF0;
	_delay_ms(te);
	
}
void secuencia_C(void){
	PORTB = 0b10101010;
	_delay_ms(te);
	PORTB = 0b01010101;
	_delay_ms(te);
}