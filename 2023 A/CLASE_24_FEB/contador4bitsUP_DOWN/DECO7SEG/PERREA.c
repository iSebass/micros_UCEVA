#include "PERREA.h"


void decoInit(void){
	DDRD  = 0xFF;
	PORTD = 0x00;
}
void decoCC(uint8_t dig){
	switch(dig){
		
		case 0: PORTD = 191; break;
		case 1: PORTD = 134; break;
		case 2: PORTD = 219; break;
		case 3: PORTD = 207; break;
		case 4: PORTD = 230; break;
		case 5: PORTD = 237; break;
		case 6: PORTD = 253; break;
		case 7: PORTD = 135; break;
		case 8: PORTD = 255; break;
		case 9: PORTD = 231; break;
		
	}
}
