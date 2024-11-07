#include "EEPROM_24LC256.h"


void EEPROM_24LC256_Wr(char data, int pos){
	
	char NibbleH, NibbleL;
	NibbleH = (0xFF00 & pos)>>8;
	NibbleL = (0x00FF & pos)>>0;
	
	TWI_Start();
	TWI_Write( (DIRMEMORIA<<1) | 0);
	TWI_Write( NibbleH );  //NIBBLE H
	TWI_Write( NibbleL );  //NIBBLE L
	TWI_Write(data);       //DATA
	TWI_Stop();
	
	
}

char EEPROM_24LC256_Rd(int pos){
	char data;
	char NibbleH, NibbleL;
	NibbleH = (0xFF00 & pos)>>8;
	NibbleL = (0x00FF & pos)>>0;
	TWI_Start();
	TWI_Write((DIRMEMORIA<<1) | 0);
	TWI_Write(NibbleH);
	TWI_Write(NibbleL);
	TWI_Repeat_Start();
	TWI_Write( (DIRMEMORIA<<1) | 1);
	data = TWI_ReadNack();
	TWI_Stop();
	return data;
}