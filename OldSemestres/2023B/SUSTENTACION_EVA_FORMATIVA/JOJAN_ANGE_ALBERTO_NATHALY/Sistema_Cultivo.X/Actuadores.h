

#ifndef ACTUADORES_H
#define	ACTUADORES_H

#include <xc.h>

#define DIR_BOMBA1 TRISBbits.TRISB1
#define DIR_BOMBA2 TRISBbits.TRISB2
#define DIR_BOMBA3 TRISBbits.TRISB3
#define DIR_BOMBA4 TRISBbits.TRISB4

#define ANSEL_BOMBA1 ANSELBbits.ANSB1
#define ANSEL_BOMBA2 ANSELBbits.ANSB2
#define ANSEL_BOMBA3 ANSELBbits.ANSB3
#define ANSEL_BOMBA4 ANSELBbits.ANSB4

#define LAT_BOMBA1 LATBbits.LATB1
#define LAT_BOMBA2 LATBbits.LATB2
#define LAT_BOMBA3 LATBbits.LATB3
#define LAT_BOMBA4 LATBbits.LATB4

void Iniciar_Bombas();
void Activar_Bomba1(char estado1);
void Activar_Bomba2(char estado2);
void Activar_Bomba3(char estado3);
void Activar_Bomba4(char estado4);

#endif	/* ACTUADORES_H */

