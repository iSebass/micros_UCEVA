/*
 * DS1307_LIB.h
 *
 * Created: 06/11/2024 07:05:25 p. m.
 *  Author: USER
 */ 


#ifndef DS1307_LIB_H_
#define DS1307_LIB_H_


#include "../TWI/TWI_LIB.h"

#define DS1307DIR  0xD0

#define LOCALE_SS      0x00
#define LOCALE_MM      0x01
#define LOCALE_HH      0x02
#define LOCALE_DAY     0x03
#define LOCALE_DATE    0x04
#define LOCALE_MONTH   0x05
#define LOCALE_YEAR    0x06
#define LOCALE_CONTROL 0x07

#define _AM 0
#define _PM 1


void DS1307_Set_Seg_Value(char seg);
void DS1307_Set_Min_Value(char min);
void DS1307_Set_Hour24_Value(char hour);
void DS1307_Set_Hour12_Value(char hour, char am);
void DS1307_Set_Week_Day_Value(char day);
void DS1307_Set_Date_Day_Value(char date);
void DS1307_Set_Month_Value(char month);
void DS1307_Set_Year_Value(char year);



#endif /* DS1307_LIB_H_ */