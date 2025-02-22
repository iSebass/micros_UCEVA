#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define get_Btn()    ( PIND & (1<<PORTD4) )

int contador=7, flagBeahvioral=1;
char statusBtn;


int main(void)
{
    DDRD |=   (  (1<<DDRD0)|(1<<DDRD1)|(1<<DDRD2)|(1<<DDRD3)  ); 
	DDRD &= ~ (1<<DDRD4);
	
    while (1) {
		
		if(get_Btn() == 0){
			PORTD = contador;
			contador++;
			if(contador>15) contador=0;
		}
		if(get_Btn() != 0){
			PORTD = contador;
			contador--;
			if(contador<0) contador=15;
		}
		
		
		_delay_ms(500);
		
    }
}

