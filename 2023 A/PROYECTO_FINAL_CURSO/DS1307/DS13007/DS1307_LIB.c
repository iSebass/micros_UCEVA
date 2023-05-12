#include "DS1307_LIB.h"

enum{
	SS,
	MM,
	HH,
	DAY,
	DATE,
	MONTH,
	YEAR	
};

void DS1307_set_HH(char data){
	TWI_Start();
	TWI_Write(DIR_DS1307);
	TWI_Write(HH);
	TWI_Write(data);
	TWI_Stop();
	
}

void DS1307_set_MM(char data){
	TWI_Start();
	TWI_Write(DIR_DS1307);
	TWI_Write(MM);
	TWI_Write(data);
	TWI_Stop();
}
void DS1307_set_SS(char data){
	TWI_Start();
	TWI_Write(DIR_DS1307);
	TWI_Write(SS);
	TWI_Write(data);
	TWI_Stop();
}

void DS1307_set_DAY(char data){
	TWI_Start();
	TWI_Write(DIR_DS1307);
	TWI_Write(DAY);
	TWI_Write(data);
	TWI_Stop();
}

void DS1307_set_Date(char data){
	TWI_Start();
	TWI_Write(DIR_DS1307);
	TWI_Write(DATE);
	TWI_Write(data);
	TWI_Stop();
}

void DS1307_set_Month(char data){
	TWI_Start();
	TWI_Write(DIR_DS1307);
	TWI_Write(MONTH);
	TWI_Write(data);
	TWI_Stop();
}

void DS1307_set_Year(char data){
	TWI_Start();
	TWI_Write(DIR_DS1307);
	TWI_Write(YEAR);
	TWI_Write(data);
	TWI_Stop();
}
