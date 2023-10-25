

#ifndef RELOJ_H
#define	RELOJ_H

#include <xc.h>


//MACRO INTERRUPCION 1 -- puero B0
#define DIR_INT1 TRISBbits.TRISB0
#define PORT_INT1 PORTBbits.RB0
#define ANSEL_INT1 ANSELBbits.ANSB0 


//PROTOTIPO DE FUNCIONES
void iniciar_reloj(); //inicializar todos los componentes
void tiempo();
void modificar_tiempo();
void aumento_seg();
void aumento_min();
void aumento_hor();

#endif	/* RELOJ_H */
