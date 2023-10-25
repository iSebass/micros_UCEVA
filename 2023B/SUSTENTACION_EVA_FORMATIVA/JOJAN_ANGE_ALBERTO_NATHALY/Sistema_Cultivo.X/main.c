#include <xc.h>
#include "configuracion.h"
#include "lcd_lib.h"
#include "adc_lib.h"
#include "Sensores.h"
#include "Actuadores.h"
#include "Menu.h"
#include "reloj.h"
#include <stdio.h>
#include <stdbool.h>

//Slider funcionalidad
#define DIR_Slider_F TRISCbits.TRISC4
#define PORT_Slider_F PORTCbits.RC4

//LED indicacion 30 segundos
#define DIR_LEDA TRISCbits.TRISC5
#define LAT_LEDA LATCbits.LATC5

//VARIABLE APAGAR Y ENCENDER FUNCIONAMIENTO
//bool Funcionalidad = 0;

//METODOS 
void Iniciar_Sistema(); //Iniciar Sistema funcional
void Funcion_Sistema(); //funcionamiento del menu (sistema funcional)


//VARIABLES
int flag_seg = 0;
int flag_ledA = 0;

//VARIABLES PARA HORA DEL SISTEMA , estan en menu.c como extern
int segundos = 1, minutos = 0, horas = 0;
int unidadS, decenaS, unidadM, decenaM, unidadH, decenaH;

//VARIABLES PARA HALLAZGOS, estan en menu.c como extern
int Hallazgos1A = 0, Hallazgos1B = 0, Hallazgos2A = 0, Hallazgos2B = 0;
char Hallazgo1AU = 0, Hallazgo1AD = 0;
char Hallazgo1BU = 0, Hallazgo1BD = 0;
char Hallazgo2AU = 0, Hallazgo2AD = 0;
char Hallazgo2BU = 0, Hallazgo2BD = 0;

//Variables para configurar las 5 horas de riego
int segundos1 = 0, minutos1 = 0, horas1 = 0;
int unidadS1, decenaS1, unidadM1, decenaM1, unidadH1, decenaH1;

int segundos2 = 0, minutos2 = 0, horas2 = 0;
int unidadS2, decenaS2, unidadM2, decenaM2, unidadH2, decenaH2;

int segundos3 = 0, minutos3 = 0, horas3 = 0;
int unidadS3, decenaS3, unidadM3, decenaM3, unidadH3, decenaH3;

int segundos4 = 0, minutos4 = 0, horas4 = 0;
int unidadS4, decenaS4, unidadM4, decenaM4, unidadH4, decenaH4;

int segundos5 = 0, minutos5 = 0, horas5 = 0;
int unidadS5 = 0, decenaS5 = 0, unidadM5 = 0, decenaM5 = 0, unidadH5 = 0, decenaH5 = 0;

char bandera_H1A = 0, bandera_H1B = 0, bandera_H2A = 0, bandera_H2B = 0;
float Humedad_Rf;
int Humedad_R;
float Sensor_1, Sensor_2, Sensor_3, Sensor_4;
bool Bandera_Hum;

bool bandera_H1 = 0, bandera_H2 = 0, bandera_H3 = 0, bandera_H4 = 0, bandera_H5 = 0; //menu de eventos

enum {
    MP, //Menu principal
    M1, //Menu 1 Horarios
    M2, //Menu 2 eventos
    M3, //Menu 3 actuadores / sensores
    M4, //Menu 4 registro
    M5, //Menu 5 sistema
    M3sen, //Menu 6 sensores
    M3act, //Menu 7 actuadores
    M1H1, //Menu 8 ingresar hora 1 riego
    M1H2, //Menu 9 ingresar hora 2 riego
    M1H3, //Menu 10 ingresar hora 3 riego
    M1H4, //Menu 11 ingresar hora 4 riego
    M1H5, //Menu 12 ingresar hora 5 riego
    MAestado,
    MAconfig,
    MFijarHora,
    MFijarHumed,
    MPendiente
};

char Menu_actual = MP;

//INTERRUPCIONES

void __interrupt() Hora() {

    //Interrupcion externa -- pin RB0
    if (INTCONbits.INTF == 1) { //si el pin RB0 esta en alto activa la interrupcion

        if (bandera_H1A == 1) {
            Hallazgos1A++;
            bandera_H1A = 0;
            LAT_BANDERA = 0;
            INTCONbits.INTF = 0; //finalizar interrupcion

        } else if (bandera_H1B == 1) {
            Hallazgos1B++;
            bandera_H1B = 0;
            LAT_BANDERA = 0;
            INTCONbits.INTF = 0; //finalizar interrupcion

        } else if (bandera_H2A == 1) {
            Hallazgos2A++;
            bandera_H2A = 0;
            LAT_BANDERA = 0;
            INTCONbits.INTF = 0; //finalizar interrupcion

        } else if (bandera_H2B == 1) {
            Hallazgos2B++;
            bandera_H2B = 0;
            LAT_BANDERA = 0;
            INTCONbits.INTF = 0; //finalizar interrupcion

        }

    }

    //Interrupcion interna --- (timer)
    if (INTCONbits.T0IF == 1) { //cuando el timer llega al tiempo establecido (10 ms)
        flag_seg++; //aumentar la varibale cada 10 ms

        Hallazgos_externos();

        if (flag_seg == 100) { //cuando llega a 100 ha pasado un segundo
            flag_seg = 0;
            segundos++;
            flag_ledA++;
            //LAT_LEDA = 0;
        }

        //ACTIVACION CADA 30 SEGUNODS
        if (flag_ledA == 30) { //cuando llega a 100 ha pasado un segundo
            LAT_LEDA = 1;

        }
        if (flag_ledA == 31) { //cuando llega a 100 ha pasado un segundo
            LAT_LEDA = 0;
            flag_ledA = 0;

        }

        //CONDICIONES DE HORAS DE RIEGO

        if (bandera_H1 == 1 && segundos == segundos1 && minutos == minutos1 && horas == horas1) {
            LAT_BOMBA1 = 1;
            LAT_BOMBA2 = 1;
            LAT_BOMBA3 = 1;
            LAT_BOMBA4 = 1;

            bandera_H1 = 0;

            // __delay_ms(1000);     
        }
        if (bandera_H2 == 1 && segundos == segundos2 && minutos == minutos2 && horas == horas2) {
            LAT_BOMBA1 = 1;
            LAT_BOMBA2 = 1;
            LAT_BOMBA3 = 1;
            LAT_BOMBA4 = 1;

            bandera_H2 = 0;
        }
        if (bandera_H3 == 1 && segundos == segundos3 && minutos == minutos3 && horas == horas3) {
            LAT_BOMBA1 = 1;
            LAT_BOMBA2 = 1;
            LAT_BOMBA3 = 1;
            LAT_BOMBA4 = 1;

            bandera_H3 = 0;
        }
        if (bandera_H4 == 1 && segundos == segundos4 && minutos == minutos4 && horas == horas4) {
            LAT_BOMBA1 = 1;
            LAT_BOMBA2 = 1;
            LAT_BOMBA3 = 1;
            LAT_BOMBA4 = 1;

            bandera_H4 = 0;
        }

        if (bandera_H5 == 1 && segundos == segundos5 && minutos == minutos5 && horas == horas5) {
            LAT_BOMBA1 = 1;
            LAT_BOMBA2 = 1;
            LAT_BOMBA3 = 1;
            LAT_BOMBA4 = 1;

            bandera_H5 = 0;
        }

        Humedad_Rf = Humedad_R + 0.0;
        if (Bandera_Hum == 1) {

            if (Sensor_1 < Humedad_Rf) {
                Activar_Bomba1(1);
            }

            if (Sensor_2 < Humedad_Rf) {
                Activar_Bomba2(1);
            }

            if (Sensor_3 < Humedad_Rf) {
                Activar_Bomba3(1);
            }

            if (Sensor_4 < Humedad_Rf) {
                Activar_Bomba4(1);
            }
        }






        TMR0 = 61;
        INTCONbits.T0IF = 0;

    }
}

void main(void) {

    //VOID SETUP 

    //INICIAR SLIDER DE FUNCIONAMIENTO
    DIR_Slider_F = 0;
    Iniciar_Sistema();

    while (1) {

        Funcion_Sistema();

    }
    return;
}

void Iniciar_Sistema() {

    //CONFIGURAMOS LA SEÑALES DE RELOJ
    OSCCON = 0x38; // OSC EXT HS //OSCCON  = 0x72; // OSC INT
    OSCTUNE = 0x00;
    BORCON = 0x00;

    DIR_LEDA = 0;
    LAT_LEDA = 0;

    iniciar_reloj();
    Iniciar_Botones();
    Iniciar_Sensores();
    Iniciar_Bombas();
    ADC_Init();
    LCD_Init();
    LCD_Cmd(_LCD_CURSOR_OFF);
}

void Funcion_Sistema() {

    switch (Menu_actual) {
        case MP: Menu_Principal();
            break;
        case M1: Menu_Horario_1();
            break;
        case M2: Menu_Eventos_2();
            break;
        case M3: Menu_Act_Sen_3();
            break;
        case M4: Menu_Registro_4();
            break;
        case M5: Menu_Sistema_5();
            break;
        case M3sen:Menu_Sensores();
            break;
        case M3act:Menu_Actuadores();
            break;
        case M1H1:Menu_Hora1();
            break;
        case M1H2:Menu_Hora2();
            break;
        case M1H3:Menu_Hora3();
            break;
        case M1H4:Menu_Hora4();
            break;
        case M1H5:Menu_Hora5();
            break;
        case MAestado: Menu_ActEstados();
            break;
        case MAconfig: Menu_ActConfig();
            break;
        case MFijarHora:Menu_Fijar_Hora();
            break;
        case MFijarHumed:Menu_Fijar_Humedad();
            break;
        case MPendiente:Menu_Pendiente();
            break;

    }



    __delay_ms(50);

}

