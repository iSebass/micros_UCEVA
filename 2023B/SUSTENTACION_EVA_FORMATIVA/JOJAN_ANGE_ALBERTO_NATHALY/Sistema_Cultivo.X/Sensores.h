

#ifndef SENSORES_H
#define	SENSORES_H

#include <xc.h>                //acceder a pines del micro

#define DIR_SENSOR1 TRISAbits.TRISA0
#define DIR_SENSOR2 TRISAbits.TRISA1
#define DIR_SENSOR3 TRISAbits.TRISA2
#define DIR_SENSOR4 TRISAbits.TRISA3

#define ANSEL_SENSOR1 ANSELAbits.ANSA0
#define ANSEL_SENSOR2 ANSELAbits.ANSA1
#define ANSEL_SENSOR3 ANSELAbits.ANSA2
#define ANSEL_SENSOR4 ANSELAbits.ANSA3

#define PORT_SENSOR1 PORTAbits.RA0
#define PORT_SENSOR2 PORTAbits.RA1
#define PORT_SENSOR3 PORTAbits.RA2
#define PORT_SENSOR4 PORTAbits.RA3

void Iniciar_Sensores();
void Lectura_Sensor1();
void Lectura_Sensor2();
void Lectura_Sensor3();
void Lectura_Sensor4();

#endif	/* SENSORES_H */

