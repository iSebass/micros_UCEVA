#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


void girarmotorA_R(void);
void girarmotorB_R(void);

void girarmotorA_L(void);
void girarmotorB_L(void);

void frenarmotorA(void);
void frenarmotorB(void);


void girarmotorA_R(void){
	 PORTB |=  (1<<0);
	 PORTB &= ~(1<<1);
}
void girarmotorB_R(void){
	 PORTB |=  (1<<2);
	 PORTB &= ~(1<<3);
}

void girarmotorA_L(void){
	 PORTB |=  (1<<1);
	 PORTB &= ~(1<<0);
}
void girarmotorB_L(void){
	PORTB |=  (1<<3);
	PORTB &= ~(1<<2);
}

void frenarmotorA(void){
	PORTB |=  (1<<0);
	PORTB |=  (1<<1);
}
void frenarmotorB(void){
	PORTB &=  ~(1<<2);
	PORTB &=  ~(1<<3);
}


int main(void)
{
	
    DDRB = 0x0F;
	
    while (1) 
    {
		girarmotorA_R();
		girarmotorB_L();
		_delay_ms(2000);
		
		girarmotorA_L();
		girarmotorB_R();
		_delay_ms(2000);
		
		frenarmotorB();
		frenarmotorA();
		_delay_ms(2000);
		
    }
}

