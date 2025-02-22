/*
 * TWI_LIB.h
 *
 * Created: 8/04/2023 9:33:10 p. m.
 *  Author: iProf
 */ 


#ifndef TWI_LIB_H_
#define EEPROM_24LC256_LIB_H_

#include <stdint.h>
#include <avr/io.h>

#include "../TWI/TWI_LIB.h"

#define DIRMEMORIA   0x50

void EEPROM_24LC256_Wr(char data, int pos);
char EEPROM_24LC256_Rd(int pos);


#endif /* TWI_LIB_H_ */