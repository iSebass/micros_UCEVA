
#ifndef DISPLAY7SEG_LIB_H_
#define DISPLAY7SEG_LIB_H_

#include <avr/io.h>

#define DISPLAY_PORT   PORTD
#define DISPLAY_DDR    DDRD

#define SEGA   6
#define SEGB   1
#define SEGC   2
#define SEGD   3
#define SEGE   4
#define SEGF   5
#define SEGG   0

void DISPLAY7SEG_Init();
void DISPLAY7SEG_CA_Set_Value(char num);
void DISPLAY7SEG_CC_Set_Value(char num);




#endif /* DISPLAY7SEG_LIB_H_ */