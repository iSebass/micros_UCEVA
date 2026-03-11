
#include "SEVEN_SEG_LIB.h"

char decoAC[10]={0xC0, 0xF9, 0xA4, 0xB0, 0x99,
0x92, 0x82, 0xF8, 0x80, 0x90};

void DisplaySevengSegInit(void ){
	DIR_SEVENSEG = 0xFF;
}
void DisplaySevenSegCA(char val){
	
	if( (decoAC[val] & 1) == 0 )   PORT_SEVENSEG &= ~(1<<SEGA); else PORT_SEVENSEG |= (1<<SEGA);
	if( (decoAC[val] & 2) == 0 )   PORT_SEVENSEG &= ~(1<<SEGB); else PORT_SEVENSEG |= (1<<SEGB);
	if( (decoAC[val] & 4) == 0 )   PORT_SEVENSEG &= ~(1<<SEGC); else PORT_SEVENSEG |= (1<<SEGC);
	if( (decoAC[val] & 8) == 0 )   PORT_SEVENSEG &= ~(1<<SEGD); else PORT_SEVENSEG |= (1<<SEGD);
	if( (decoAC[val] & 16) == 0 )  PORT_SEVENSEG &= ~(1<<SEGE); else PORT_SEVENSEG |= (1<<SEGE);
	if( (decoAC[val] & 32) == 0 )  PORT_SEVENSEG &= ~(1<<SEGF); else PORT_SEVENSEG |= (1<<SEGF);
	if( (decoAC[val] & 64) == 0 )  PORT_SEVENSEG &= ~(1<<SEGG); else PORT_SEVENSEG |= (1<<SEGG);
	
}
void DisplaySevenSegCC(char val){
	
}
