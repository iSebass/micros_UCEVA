
#ifndef SEVENSEG_LIB_H_
#define SEVENSEG_LIB_H_

#include <avr/io.h>

#define PORT_SEVENSEG  PORTC
#define DIR_SEVENSEG   DDRC

#define SEGA 2
#define SEGB 3
#define SEGC 1
#define SEGD 0
#define SEGE 4
#define SEGF 5
#define SEGG 6

void DisplaySevengSegInit(void );
void DisplaySevenSegCA(char val);
void DisplaySevenSegCC(char val);


#endif /* SEVENSEG_LIB_H_ */