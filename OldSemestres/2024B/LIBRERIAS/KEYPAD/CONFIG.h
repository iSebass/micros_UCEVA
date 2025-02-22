/*
 * CONFIG.h
 *
 * Created: 10/10/2024 10:18:09 a. m.
 *  Author: USER
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

//MAPEAMOS  LOS REGISTROS A UTILIZAR
typedef uint8_t byte;

typedef union {
	struct {
		byte B0        :1;
		byte B1        :1;
		byte B2        :1;
		byte B3        :1;
		byte B4        :1;
		byte B5        :1;
		byte B6        :1;
		byte B7        :1;
	};
	struct {
		byte NIBBLE_L   :4;
		byte NIBBLE_H   :4;
	};
}STRUCTBbits_t;


typedef union {
	struct {
		byte D0        :1;
		byte D1        :1;
		byte D2        :1;
		byte D3        :1;
		byte D4        :1;
		byte D5        :1;
		byte D6        :1;
		byte D7        :1;
	};				   
	struct {		   
		byte           :2;
		byte INT_0     :1;
		byte INT_1     :1;
		byte T0        :1;
		byte T1        :1;
		byte           :2;
	};
	struct {
		byte NIBBLE_L   :4;
		byte NIBBLE_H   :4;
	};
}STRUCTDbits_t;

typedef union {
	struct {
		byte C0         :1;
		byte C1         :1;
		byte C2         :1;
		byte C3         :1;
		byte C4         :1;
		byte C5         :1;
		byte C6         :1;
		byte C7         :1;
	};
	
	struct {
		byte NIBBLE_L    :4;
		byte NIBBLE_H    :4;	
	};	
} STRUCTCbits_t;

typedef union {
	struct {
		byte E0         :1;
		byte E1         :1;
		byte E2         :1;
		byte E3         :1;
		byte            :4;
	};
	struct {
		byte NIBBLE_L   :4;
		byte            :4;
	};
} STRUCTEbits_t;


//MAPEAMOS LOS ESTRUCTURAS A LOS REGISTROS
#define MACRO_MAP(STRUCT, SFR)  ( *(volatile  STRUCT *)_SFR_MEM_ADDR(SFR) )

#define PORTDbits  MACRO_MAP(STRUCTDbits_t, PORTD)
#define PORTCbits  MACRO_MAP(STRUCTCbits_t, PORTC)
#define PORTBbits  MACRO_MAP(STRUCTBbits_t, PORTB)
#define PORTEbits  MACRO_MAP(STRUCTEbits_t, PORTE)

#define DDRDbits   MACRO_MAP(STRUCTDbits_t, DDRD)
#define DDRCbits   MACRO_MAP(STRUCTCbits_t, DDRC)
#define DDRBbits   MACRO_MAP(STRUCTBbits_t, DDRB)
#define DDREbits   MACRO_MAP(STRUCTEbits_t, DDRE)

#define PINDbits   MACRO_MAP(STRUCTDbits_t, PIND)
#define PINCbits   MACRO_MAP(STRUCTCbits_t, PINC)
#define PINBbits   MACRO_MAP(STRUCTBbits_t, PINB)
#define PINEbits   MACRO_MAP(STRUCTEbits_t, PINE)


#endif /* CONFIG_H_ */