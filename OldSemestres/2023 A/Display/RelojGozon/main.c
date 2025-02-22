#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "DISPLAY7SEG/PERREA.h"

#define DP1_ON  0b1110
#define DP2_ON  0b1101
#define DP3_ON  0b1011
#define DP4_ON  0b0111

const int tmultiplex=10;

int horas=23, minutos=52, residuo;
int dec_hora, uni_hora, dec_min, uni_min, flag_seg=0;

int main(void)
{
    decoInit();
	DDRB |= (1<<0)|(1<<1)|(1<<2)|(1<<3);
    while (1) 
    {
		if(flag_seg == 25){
			flag_seg = 0;
			minutos++;
			if(minutos >= 60){
				minutos = 0;
				horas++;
				if(horas>=24){
					horas=0;
				}
			}
			
		}
		
		dec_hora = horas/10;
		uni_hora = horas%10;
		
		dec_min = minutos/10;
		uni_min = minutos % 10;
		
		PORTB = DP1_ON;
		decoCC(dec_hora);
		_delay_ms(tmultiplex);
		
		PORTB = DP2_ON;
		decoCC(uni_hora);
		_delay_ms(tmultiplex);
		
		PORTB = DP3_ON;
		decoCC(dec_min);
		_delay_ms(tmultiplex);
		
		PORTB = DP4_ON;
		decoCC(uni_min);
		_delay_ms(tmultiplex);
		
		flag_seg++;
		
    }
}

