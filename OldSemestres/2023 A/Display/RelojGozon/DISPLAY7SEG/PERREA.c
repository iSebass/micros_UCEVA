#include "PERREA.h"


void decoInit(void){
	DECO_DDR  = 0xFF;
	DECO_PORT = 0x00;
}
void decoCC(uint8_t dig){
	switch(dig){
		
		case 0: DECO_PORT = 191; break;
		case 1: DECO_PORT = 134; break;
		case 2: DECO_PORT = 219; break;
		case 3: DECO_PORT = 207; break;
		case 4: DECO_PORT = 230; break;
		case 5: DECO_PORT = 237; break;
		case 6: DECO_PORT = 253; break;
		case 7: DECO_PORT = 135; break;
		case 8: DECO_PORT = 255; break;
		case 9: DECO_PORT = 231; break;
		
	}
}
