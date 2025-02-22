
#ifndef PERREA_H_
#define PERREA_H_

#define DECO_DDR  DDRD
#define DECO_PORT PORTD

#include <stdint.h>
#include <avr/io.h>

void decoInit(void);
void decoCC(uint8_t dig);



#endif /* PERREA_H_ */