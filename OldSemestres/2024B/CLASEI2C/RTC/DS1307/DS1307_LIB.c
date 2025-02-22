#include "DS1307_LIB.h"

void DS1307_Set_Seg_Value(char seg){
	TWI_Start();
	TWI_Write(DS1307DIR);
	TWI_Write(LOCALE_SS);
	TWI_Write(seg);
	TWI_Stop();
}
void DS1307_Set_Min_Value(char min){
	TWI_Start();
	TWI_Write(DS1307DIR);
	TWI_Write(LOCALE_MM);
	TWI_Write(min);
	TWI_Stop();
}
void DS1307_Set_Hour24_Value(char hour){
	TWI_Start();
	TWI_Write(DS1307DIR);
	TWI_Write(LOCALE_HH);
	TWI_Write(hour);
	TWI_Stop();
}
void DS1307_Set_Hour12_Value(char hour, char am){
	char ampm;
	
	if( am == 1){
		ampm  = hour | 0b01100000;
	}
	else{
		ampm = hour | 0b01000000;
	}
	
	
	TWI_Start();
	TWI_Write(DS1307DIR);
	TWI_Write(LOCALE_HH );
	TWI_Write(ampm);
	TWI_Stop();
}
void DS1307_Set_Week_Day_Value(char day){
	TWI_Start();
	TWI_Write(DS1307DIR);
	TWI_Write(LOCALE_DAY);
	TWI_Write(day);
	TWI_Stop();
}
void DS1307_Set_Date_Day_Value(char date){
	TWI_Start();
	TWI_Write(DS1307DIR);
	TWI_Write(LOCALE_DATE);
	TWI_Write(date);
	TWI_Stop();
}
void DS1307_Set_Month_Value(char month){
	TWI_Start();
	TWI_Write(DS1307DIR);
	TWI_Write(LOCALE_MONTH);
	TWI_Write(month);
	TWI_Stop();
}
void DS1307_Set_Year_Value(char year){
	TWI_Start();
	TWI_Write(DS1307DIR);
	TWI_Write(LOCALE_YEAR);
	TWI_Write(year);
	TWI_Stop();
}