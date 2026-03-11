
#ifndef SEVEN_SEG_LIB_H_
#define SEVEN_SEG_LIB_H_

#include <avr/io.h>

#define PORT_SEVENSEG  PORTC
#define DIR_SEVENSEG   DDRC

#define SEGA 0
#define SEGB 1
#define SEGC 2
#define SEGD 3
#define SEGE 4
#define SEGF 5
#define SEGG 6

void DisplaySevengSegInit(void );
void DisplaySevenSegCA(char val);
void DisplaySevenSegCC(char val);


#endif /* SEVENSEG_LIB_H_ */