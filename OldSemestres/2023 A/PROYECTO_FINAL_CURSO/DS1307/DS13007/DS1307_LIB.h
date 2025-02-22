#ifndef DS1307_LIB_H_
#define DS1307_LIB_H_

#include "../TWI/TWI_LIB.h"


#define DIR_DS1307  0b1101000<<1

void DS1307_set_HH(char data);
void DS1307_set_MM(char data);
void DS1307_set_SS(char data);
void DS1307_set_DAY(char data);
void DS1307_set_Date(char data);
void DS1307_set_Month(char data);
void DS1307_set_Year(char data);

#endif