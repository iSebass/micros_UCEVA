#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>


#define tme  100

int main(void)
{
	//CONFIGRUAMOS TODO EL PUERTO A COMO SALIDA
    DDRA = 0xFF;
	//APAGAMOS TODOS LOS BITS DEL PUERTO A
	PORTA = 0x00; // 0000X0X0
	
    while (1) 
    {
		PORTA |= (1<<0);
		_delay_ms(tme);
		PORTA |= (1<<1);
		_delay_ms(tme);
		PORTA |= (1<<2);
		_delay_ms(tme);
		PORTA |= (1<<3);
		_delay_ms(tme);
		PORTA |= (1<<4);
		_delay_ms(tme);
		PORTA |= (1<<5);
		_delay_ms(tme);
		PORTA |= (1<<6);
		_delay_ms(tme);
		PORTA |= (1<<7);
		_delay_ms(tme);
		
		PORTA ^= (1<<0); _delay_ms(tme);
		PORTA ^= (1<<1); _delay_ms(tme);
		PORTA ^= (1<<2); _delay_ms(tme);
		PORTA ^= (1<<3); _delay_ms(tme);
		PORTA ^= (1<<4); _delay_ms(tme);
		PORTA ^= (1<<5); _delay_ms(tme);
		PORTA ^= (1<<6); _delay_ms(tme);
		PORTA ^= (1<<7); _delay_ms(tme);
		
    }
}

