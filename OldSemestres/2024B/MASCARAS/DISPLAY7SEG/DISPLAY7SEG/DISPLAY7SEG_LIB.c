#include "DISPLAY7SEG_LIB.h"

void DISPLAY7SEG_Init(){
	DISPLAY_DDR = 0xFF;
}
void DISPLAY7SEG_CA_Set_Value(char num){
	 
}
void DISPLAY7SEG_CC_Set_Value(char num){
	char decoVal[10]={191,134,219,207,230,237,253,135,255,231};
	
	if( (decoVal[num]&1)   != 0 ) DISPLAY_PORT |= (1<<SEGA); else DISPLAY_PORT &= ~(1<<SEGA);
	if( (decoVal[num]&2)   != 0 ) DISPLAY_PORT |= (1<<SEGB); else DISPLAY_PORT &= ~(1<<SEGB);
	if( (decoVal[num]&4)   != 0 ) DISPLAY_PORT |= (1<<SEGC); else DISPLAY_PORT &= ~(1<<SEGC);
	if( (decoVal[num]&8)   != 0 ) DISPLAY_PORT |= (1<<SEGD); else DISPLAY_PORT &= ~(1<<SEGD);
	if( (decoVal[num]&16)  != 0 ) DISPLAY_PORT |= (1<<SEGE); else DISPLAY_PORT &= ~(1<<SEGE);
	if( (decoVal[num]&32)  != 0 ) DISPLAY_PORT |= (1<<SEGF); else DISPLAY_PORT &= ~(1<<SEGF);
	if( (decoVal[num]&64)  != 0 ) DISPLAY_PORT |= (1<<SEGG); else DISPLAY_PORT &= ~(1<<SEGG);
	
	
}