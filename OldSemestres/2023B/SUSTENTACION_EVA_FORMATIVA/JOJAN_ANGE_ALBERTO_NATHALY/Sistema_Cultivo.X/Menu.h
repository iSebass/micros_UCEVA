
#ifndef MENU_H
#define	MENU_H

#include <xc.h>

//boton subir y horas ++ , puerto C no tiene ansel
#define DIR_BOTON1 TRISCbits.TRISC0
#define PORT_BOTON1 PORTCbits.RC0

//boton bajar y minutos ++ , puerto C no tiene ansel
#define DIR_BOTON2 TRISCbits.TRISC1
#define PORT_BOTON2 PORTCbits.RC1

//boton  segundos ++ , puerto C no tiene ansel
#define DIR_BOTON3 TRISCbits.TRISC2
#define PORT_BOTON3 PORTCbits.RC2

//boton seleccionar, puerto C no tiene ansel
#define DIR_BOTON4 TRISCbits.TRISC3
#define PORT_BOTON4 PORTCbits.RC3

//boton hallzagos hectarea 1 Alta    //UTILIZAR INTERRUPCION EXTERNA?
#define DIR_BOTON5 TRISAbits.TRISA4
#define PORT_BOTON5 PORTAbits.RA4
#define ANSEL_BOTON5 ANSELAbits.ANSA4

//boton hallzagos hectarea 1 Baja
#define DIR_BOTON6 TRISAbits.TRISA5
#define PORT_BOTON6 PORTAbits.RA5
#define ANSEL_BOTON6 ANSELAbits.ANSA5

//boton hallzagos hectarea 2 Alta
#define DIR_BOTON7 TRISBbits.TRISB5
#define PORT_BOTON7 PORTBbits.RB5
#define ANSEL_BOTON7 ANSELBbits.ANSB5

//boton hallzagos hectarea 2 Baja
#define DIR_BOTON8 TRISBbits.TRISB6
#define PORT_BOTON8 PORTBbits.RB6
//#define ANSEL_BOTON8 ANSELBbits.

//Boton de bandera (flanco de Subida para activar interrupcion externa) 
#define DIR_BANDERA TRISBbits.TRISB7
#define LAT_BANDERA LATBbits.LATB7
//#define ANSEL_BANDERA ANSELBbits. no tiene ansel B7

void Iniciar_Botones();

void Menu_Principal();
void Menu_Horario_1();
void Menu_Eventos_2();
void Menu_Act_Sen_3();
void Menu_Registro_4();
void Menu_Sistema_5();

void Menu_Actuadores();
void Menu_ActEstados();
void Menu_ActConfig();
void Menu_Sensores();

void Menu_Hora1();
void Menu_Hora2();
void Menu_Hora3();
void Menu_Hora4();
void Menu_Hora5();

void Menu_Fijar_Hora();
void Menu_Fijar_Humedad();
void Menu_Pendiente();

void Hallazgos_externos();
void Bombas_Sensores();




#endif	/* MENU_H */

