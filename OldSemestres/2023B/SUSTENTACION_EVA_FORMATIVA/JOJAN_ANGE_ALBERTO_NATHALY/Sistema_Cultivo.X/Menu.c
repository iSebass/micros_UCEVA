#include "Menu.h"
#include "configuracion.h"
#include "lcd_lib.h"
#include "adc_lib.h"
#include "Sensores.h"
#include "reloj.h"
#include "Actuadores.h"
#include <stdio.h>
#include <stdbool.h>

//ENUMERADOR

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

//VARIABLES

//Variables para configurar las 5 horas de riego -- menu horario
extern int segundos1 = 0, minutos1 = 0, horas1 = 0;
extern int unidadS1, decenaS1, unidadM1, decenaM1, unidadH1, decenaH1;

extern int segundos2 = 0, minutos2 = 0, horas2 = 0;
extern int unidadS2, decenaS2, unidadM2, decenaM2, unidadH2, decenaH2;

extern int segundos3 = 0, minutos3 = 0, horas3 = 0;
extern int unidadS3, decenaS3, unidadM3, decenaM3, unidadH3, decenaH3;

extern int segundos4 = 0, minutos4 = 0, horas4 = 0;
extern int unidadS4, decenaS4, unidadM4, decenaM4, unidadH4, decenaH4;

extern int segundos5 = 0, minutos5 = 0, horas5 = 0;
extern int unidadS5 = 0, decenaS5 = 0, unidadM5 = 0, decenaM5 = 0, unidadH5 = 0, decenaH5 = 0;

//variable para fijar / establecer hora de riego -- menu eventos
extern bool bandera_H1 = 0, bandera_H2 = 0, bandera_H3 = 0, bandera_H4 = 0, bandera_H5 = 0; //menu de eventos

//VARIABLES PARA HALLAZGOS -- menu -- registro
extern int Hallazgos1A = 0, Hallazgos1B = 0, Hallazgos2A = 0, Hallazgos2B = 0;
extern char Hallazgo1AU = 0, Hallazgo1AD = 0;
extern char Hallazgo1BU = 0, Hallazgo1BD = 0;
extern char Hallazgo2AU = 0, Hallazgo2AD = 0;
extern char Hallazgo2BU = 0, Hallazgo2BD = 0;

extern char bandera_H1A = 0, bandera_H1B = 0, bandera_H2A = 0, bandera_H2B = 0;


extern char Menu_actual;
char op = 1;

// Variables char estado de actuadores
char Est1, Est2, Est3, Est4;

// Variables char estado de Horario de riego 
char EstaH1, EstaH2, EstaH3, EstaH4, EstaH5;

//Variables establcer rango de humedad
extern int Humedad_R = 0;
char Humedad_RD, Humedad_RU;
extern float Sensor_1, Sensor_2, Sensor_3, Sensor_4;

extern bool Bandera_Hum = 0;
char estado_hum;


//INICIALIZAR

void Iniciar_Botones() {
    DIR_BOTON1 = 1;
    DIR_BOTON2 = 1;
    DIR_BOTON3 = 1;
    DIR_BOTON4 = 1;

    DIR_BOTON5 = 1;
    DIR_BOTON6 = 1;
    DIR_BOTON7 = 1;
    DIR_BOTON8 = 1;

    ANSEL_BOTON5 = 0;
    ANSEL_BOTON6 = 0;
    ANSEL_BOTON7 = 0;
    //ANSEL_BOTON8 = 0; -- NO TIENE ANSEL

    DIR_BANDERA = 0;
    LAT_BANDERA = 0;

    TRISCbits.TRISC0 = TRISCbits.TRISC1 = TRISCbits.TRISC2 = 1;
}

//MENU PRINCIPAL

void Menu_Principal() {
    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "   MENU PRINCIPAL   ");
    LCD_Write_Text(2, 1, "1Horario  4Registro ");
    LCD_Write_Text(3, 1, "2Eventos  5Sistema  ");
    LCD_Write_Text(4, 1, "3Act/Sen  6Op:      ");
    LCD_Write(4, 15, op + 48);

    switch (op) {
        case 1:
            LCD_Write(2, 9, '<');
            LCD_Write(2, 20, ' ');
            LCD_Write(3, 9, ' ');
            LCD_Write(3, 19, ' ');
            LCD_Write(4, 9, ' ');
            break;
        case 2:
            LCD_Write(2, 9, ' ');
            LCD_Write(2, 20, ' ');
            LCD_Write(3, 9, '<');
            LCD_Write(3, 19, ' ');
            LCD_Write(4, 9, ' ');
            break;
        case 3:
            LCD_Write(2, 9, ' ');
            LCD_Write(2, 20, ' ');
            LCD_Write(3, 9, ' ');
            LCD_Write(3, 19, ' ');
            LCD_Write(4, 9, '<');
            break;
        case 4:
            LCD_Write(2, 9, ' ');
            LCD_Write(2, 20, '<');
            LCD_Write(3, 9, ' ');
            LCD_Write(3, 19, ' ');
            LCD_Write(4, 9, ' ');
            break;
        case 5:
            LCD_Write(2, 9, ' ');
            LCD_Write(2, 20, ' ');
            LCD_Write(3, 9, ' ');
            LCD_Write(3, 19, '<');
            LCD_Write(4, 9, ' ');
            break;
    }

    if (PORT_BOTON1 == 1) {
        while (PORT_BOTON1 == 1);
        op++;
        if (op > 5) {
            op = 1;
        }
    }
    if (PORT_BOTON2 == 1) {
        while (PORT_BOTON2 == 1);
        op--;
        if (op < 1) {
            op = 5;
        }
    }
    if (PORT_BOTON3 == 1) {
        while (PORT_BOTON3 == 1);
        switch (op) {
            case 1: Menu_actual = M1;
                break;
            case 2: Menu_actual = M2;
                break;
            case 3: Menu_actual = M3;
                break;
            case 4: Menu_actual = M4;
                break;
            case 5: Menu_actual = M5;
                break;
        }
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

    //Hallazgos_externos();
    //Bombas_Sensores();

}


//1. MENU HORARIO
void Menu_Horario_1() {
    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "   MENU 1 HORARIO   ");
    LCD_Write_Text(2, 1, "1Hora  4Hora  6Volv ");
    LCD_Write_Text(3, 1, "2Hora  5Hora  7Op:  ");
    LCD_Write_Text(4, 1, "3Hora               ");
    LCD_Write(3, 19, op + 48);
    tiempo();

    switch (op) {
        case 1:
            LCD_Write(2, 6, '<');
            LCD_Write(2, 13, ' ');
            LCD_Write(2, 20, ' ');
            LCD_Write(3, 6, ' ');
            LCD_Write(3, 13, ' ');
            LCD_Write(4, 6, ' ');
            break;
        case 2:
            LCD_Write(2, 6, ' ');
            LCD_Write(2, 13, ' ');
            LCD_Write(2, 20, ' ');
            LCD_Write(3, 6, '<');
            LCD_Write(3, 13, ' ');
            LCD_Write(4, 6, ' ');
            break;
        case 3:
            LCD_Write(2, 6, ' ');
            LCD_Write(2, 13, ' ');
            LCD_Write(2, 20, ' ');
            LCD_Write(3, 6, ' ');
            LCD_Write(3, 13, ' ');
            LCD_Write(4, 6, '<');
            break;
        case 4:
            LCD_Write(2, 6, ' ');
            LCD_Write(2, 13, '<');
            LCD_Write(2, 20, ' ');
            LCD_Write(3, 6, ' ');
            LCD_Write(3, 13, ' ');
            LCD_Write(4, 6, ' ');
            break;
        case 5:
            LCD_Write(2, 6, ' ');
            LCD_Write(2, 13, ' ');
            LCD_Write(2, 20, ' ');
            LCD_Write(3, 6, ' ');
            LCD_Write(3, 13, '<');
            LCD_Write(4, 6, ' ');
            break;
        case 6:
            LCD_Write(2, 6, ' ');
            LCD_Write(2, 13, ' ');
            LCD_Write(2, 20, '<');
            LCD_Write(3, 6, ' ');
            LCD_Write(3, 13, ' ');
            LCD_Write(4, 6, ' ');
            break;
    }

    if (PORT_BOTON1 == 1) {
        while (PORT_BOTON1 == 1);
        op++;
        if (op > 6) {
            op = 1;
        }
    }
    if (PORT_BOTON2 == 1) {
        while (PORT_BOTON2 == 1);
        op--;
        if (op < 1) {
            op = 6;
        }
    }
    if (PORT_BOTON3 == 1) {
        while (PORT_BOTON3 == 1);
        switch (op) {
            case 1: Menu_actual = M1H1;
                break;
            case 2: Menu_actual = M1H2;
                break;
            case 3: Menu_actual = M1H3;
                break;
            case 4: Menu_actual = M1H4;
                break;
            case 5: Menu_actual = M1H5;
                break;
            case 6: Menu_actual = MP;
                break;
        }
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

    //Hallazgos_externos();

}

//1.1 menu hora 1

void Menu_Hora1() {
    unidadS1 = segundos1 % 10;
    decenaS1 = segundos1 / 10;

    unidadM1 = minutos1 % 10;
    decenaM1 = minutos1 / 10;

    unidadH1 = horas1 % 10;
    decenaH1 = horas1 / 10;

    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "     MENU HORA 1    ");
    LCD_Write_Text(2, 1, "1.Establecer hora:  ");
    LCD_Write_Text(3, 1, "                    ");
    LCD_Write_Text(4, 1, "2.Volver            ");
    LCD_Write(4, 9, '<');

    LCD_Write(3, 6, decenaH1 + 48);
    LCD_Write(3, 7, unidadH1 + 48);
    LCD_Write(3, 8, ':');
    LCD_Write(3, 9, decenaM1 + 48);
    LCD_Write(3, 10, unidadM1 + 48);
    LCD_Write(3, 11, ':');
    LCD_Write(3, 12, decenaS1 + 48);
    LCD_Write(3, 13, unidadS1 + 48);

    if (PORTCbits.RC0) {
        while (PORTCbits.RC0 == 1); //cambiarlo por delay
        horas1++;
        if (horas1 > 23) {
            horas1 = 0;
        }
    }
    if (PORTCbits.RC1) {
        while (PORTCbits.RC0); //cambiarlo por delay
        minutos1++;
        if (minutos1 > 59) {
            minutos1 = 0;
        }
    }

    if (PORTCbits.RC2) {
        while (PORTCbits.RC2);
        Menu_actual = M1;
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

   // Hallazgos_externos();

}

//1.2 menu hora 2

void Menu_Hora2() {

    unidadS2 = segundos2 % 10;
    decenaS2 = segundos2 / 10;

    unidadM2 = minutos2 % 10;
    decenaM2 = minutos2 / 10;

    unidadH2 = horas2 % 10;
    decenaH2 = horas2 / 10;

    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "     MENU HORA 2    ");
    LCD_Write_Text(2, 1, "1.Establecer hora:  ");
    LCD_Write_Text(3, 1, "                    ");
    LCD_Write_Text(4, 1, "2.Volver            ");
    LCD_Write(4, 9, '<');

    LCD_Write(3, 6, decenaH2 + 48);
    LCD_Write(3, 7, unidadH2 + 48);
    LCD_Write(3, 8, ':');
    LCD_Write(3, 9, decenaM2 + 48);
    LCD_Write(3, 10, unidadM2 + 48);
    LCD_Write(3, 11, ':');
    LCD_Write(3, 12, decenaS2 + 48);
    LCD_Write(3, 13, unidadS2 + 48);

    if (PORT_BOTON1 == 1) {
        while (PORT_BOTON1 == 1); //cambiarlo por delay
        horas2++;
        if (horas2 > 23) {
            horas2 = 0;
        }
    }
    if (PORT_BOTON2 == 1) {
        while (PORT_BOTON2 == 1); //cambiarlo por delay
        minutos2++;
        if (minutos2 > 59) {
            minutos2 = 0;
        }
    }


    if (PORT_BOTON3 == 1) {
        while (PORT_BOTON3 == 1);
        Menu_actual = M1;
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

    //Hallazgos_externos();

}

//1.3 menu hora 3

void Menu_Hora3() {

    unidadS3 = segundos3 % 10;
    decenaS3 = segundos3 / 10;

    unidadM3 = minutos3 % 10;
    decenaM3 = minutos3 / 10;

    unidadH3 = horas3 % 10;
    decenaH3 = horas3 / 10;

    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "     MENU HORA 3    ");
    LCD_Write_Text(2, 1, "1.Establecer hora:  ");
    LCD_Write_Text(3, 1, "                    ");
    LCD_Write_Text(4, 1, "2.Volver            ");
    LCD_Write(4, 9, '<');

    LCD_Write(3, 6, decenaH3 + 48);
    LCD_Write(3, 7, unidadH3 + 48);
    LCD_Write(3, 8, ':');
    LCD_Write(3, 9, decenaM3 + 48);
    LCD_Write(3, 10, unidadM3 + 48);
    LCD_Write(3, 11, ':');
    LCD_Write(3, 12, decenaS3 + 48);
    LCD_Write(3, 13, unidadS3 + 48);

    if (PORT_BOTON1 == 1) {
        while (PORT_BOTON1 == 1); //cambiarlo por delay
        horas3++;
        if (horas3 > 23) {
            horas3 = 0;
        }
    }
    if (PORT_BOTON2 == 1) {
        while (PORT_BOTON2 == 1); //cambiarlo por delay
        minutos3++;
        if (minutos3 > 59) {
            minutos3 = 0;
        }
    }


    if (PORT_BOTON3 == 1) {
        while (PORT_BOTON3 == 1);
        Menu_actual = M1;
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

    //Hallazgos_externos();

}

//1.4 menu hora 4

void Menu_Hora4() {

    unidadS4 = segundos4 % 10;
    decenaS4 = segundos4 / 10;

    unidadM4 = minutos4 % 10;
    decenaM4 = minutos4 / 10;

    unidadH4 = horas4 % 10;
    decenaH4 = horas4 / 10;

    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "     MENU HORA 4    ");
    LCD_Write_Text(2, 1, "1.Establecer hora:  ");
    LCD_Write_Text(3, 1, "                    ");
    LCD_Write_Text(4, 1, "2.Volver            ");
    LCD_Write(4, 9, '<');

    LCD_Write(3, 6, decenaH4 + 48);
    LCD_Write(3, 7, unidadH4 + 48);
    LCD_Write(3, 8, ':');
    LCD_Write(3, 9, decenaM4 + 48);
    LCD_Write(3, 10, unidadM4 + 48);
    LCD_Write(3, 11, ':');
    LCD_Write(3, 12, decenaS4 + 48);
    LCD_Write(3, 13, unidadS4 + 48);

    if (PORT_BOTON1 == 1) {
        while (PORT_BOTON1 == 1); //cambiarlo por delay
        horas4++;
        if (horas4 > 23) {
            horas4 = 0;
        }
    }
    if (PORT_BOTON2 == 1) {
        while (PORT_BOTON2 == 1); //cambiarlo por delay
        minutos4++;
        if (minutos4 > 59) {
            minutos4 = 0;
        }
    }

    if (PORT_BOTON3 == 1) {
        while (PORT_BOTON3 == 1);
        Menu_actual = M1;
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

   // Hallazgos_externos();

}

//1.5 menu hora 5

void Menu_Hora5() {

    unidadS5 = segundos5 % 10;
    decenaS5 = segundos5 / 10;

    unidadM5 = minutos5 % 10;
    decenaM5 = minutos5 / 10;

    unidadH5 = horas5 % 10;
    decenaH5 = horas5 / 10;

    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "     MENU HORA 5    ");
    LCD_Write_Text(2, 1, "1.Establecer hora:  ");
    LCD_Write_Text(3, 1, "                    ");
    LCD_Write_Text(4, 1, "2.Volver            ");
    LCD_Write(4, 9, '<');

    LCD_Write(3, 6, decenaH5 + 48);
    LCD_Write(3, 7, unidadH5 + 48);
    LCD_Write(3, 8, ':');
    LCD_Write(3, 9, decenaM5 + 48);
    LCD_Write(3, 10, unidadM5 + 48);
    LCD_Write(3, 11, ':');
    LCD_Write(3, 12, decenaS5 + 48);
    LCD_Write(3, 13, unidadS5 + 48);

    if (PORT_BOTON1 == 1) {
        while (PORT_BOTON1 == 1); //cambiarlo por delay
        horas5++;
        if (horas5 > 23) {
            horas5 = 0;
        }
    }
    if (PORT_BOTON2 == 1) {
        while (PORT_BOTON2 == 1); //cambiarlo por delay
        minutos5++;
        if (minutos5 > 59) {
            minutos5 = 0;
        }
    }


    if (PORT_BOTON3 == 1) {
        while (PORT_BOTON3 == 1);
        Menu_actual = M1;
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

    //Hallazgos_externos();

}



//2. MENU EVENTOS

void Menu_Eventos_2() {

    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "   MENU 2 EVENTOS   ");
    LCD_Write_Text(2, 1, "Fijar Hora          ");
    LCD_Write_Text(3, 1, "Fijar Humedad       ");
    LCD_Write_Text(4, 1, "Pendiente   Volver  ");

    switch (op) {
        case 1:
            LCD_Write(2, 12, '<');
            LCD_Write(3, 14, ' ');
            LCD_Write(4, 10, ' ');
            LCD_Write(4, 19, ' ');
            break;
        case 2:
            LCD_Write(2, 12, ' ');
            LCD_Write(3, 14, '<');
            LCD_Write(4, 10, ' ');
            LCD_Write(4, 19, ' ');
            break;
        case 3:
            LCD_Write(2, 12, ' ');
            LCD_Write(3, 14, ' ');
            LCD_Write(4, 10, '<');
            LCD_Write(4, 19, ' ');
            break;
        case 4:
            LCD_Write(2, 12, ' ');
            LCD_Write(3, 14, ' ');
            LCD_Write(4, 10, ' ');
            LCD_Write(4, 19, '<');
            break;
    }

    if (PORTCbits.RC0) {
        while (PORTCbits.RC0);
        op++;
        if (op > 4) {
            op = 1;
        }
    }
    if (PORTCbits.RC1) {
        while (PORTCbits.RC1);
        op--;
        if (op < 1) {
            op = 4;
        }
    }

    if (PORTCbits.RC2) {
        while (PORTCbits.RC2);
        switch (op) {
            case 1: Menu_actual = MFijarHora;
                break;
            case 2: Menu_actual = MFijarHumed;
                break;
            case 3: Menu_actual = MPendiente;
                break;
            case 4: Menu_actual = MP;
                break;
        }
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

    //Hallazgos_externos();

}

//2.1 Menu fijar hora

void Menu_Fijar_Hora() {

    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "   MENU FIJAR HORA  ");
    LCD_Write_Text(2, 1, "1Hora      4Hora    ");
    LCD_Write_Text(3, 1, "2Hora      5Hora    ");
    LCD_Write_Text(4, 1, "3Hora      6Volver  ");

    switch (op) {
        case 1:
            LCD_Write(2, 7, '<');
            LCD_Write(2, 18, ' ');
            LCD_Write(3, 7, ' ');
            LCD_Write(3, 18, ' ');
            LCD_Write(4, 7, ' ');
            LCD_Write(4, 19, ' ');
            break;
        case 2:
            LCD_Write(2, 7, ' ');
            LCD_Write(2, 18, ' ');
            LCD_Write(3, 7, '<');
            LCD_Write(3, 18, ' ');
            LCD_Write(4, 7, ' ');
            LCD_Write(4, 19, ' ');
            break;
        case 3:
            LCD_Write(2, 7, ' ');
            LCD_Write(2, 18, ' ');
            LCD_Write(3, 7, ' ');
            LCD_Write(3, 18, ' ');
            LCD_Write(4, 7, '<');
            LCD_Write(4, 19, ' ');
            break;
        case 4:
            LCD_Write(2, 7, ' ');
            LCD_Write(2, 18, '<');
            LCD_Write(3, 7, ' ');
            LCD_Write(3, 18, ' ');
            LCD_Write(4, 7, ' ');
            LCD_Write(4, 19, ' ');
            break;
        case 5:
            LCD_Write(2, 7, ' ');
            LCD_Write(2, 18, ' ');
            LCD_Write(3, 7, ' ');
            LCD_Write(3, 18, '<');
            LCD_Write(4, 7, ' ');
            LCD_Write(4, 19, ' ');
            break;
        case 6:
            LCD_Write(2, 7, ' ');
            LCD_Write(2, 18, ' ');
            LCD_Write(3, 7, ' ');
            LCD_Write(3, 18, ' ');
            LCD_Write(4, 7, ' ');
            LCD_Write(4, 19, '<');
            break;
    }


    if (bandera_H1) {
        EstaH1 = '1';
    } else
        EstaH1 = '0';
    LCD_Write(2, 6, EstaH1);


    if (bandera_H2) {
        EstaH2 = '1';
    } else
        EstaH2 = '0';
    LCD_Write(3, 6, EstaH2);


    if (bandera_H3) {
        EstaH3 = '1';
    } else
        EstaH3 = '0';
    LCD_Write(4, 6, EstaH3);


    if (bandera_H4) {
        EstaH4 = '1';
    } else
        EstaH4 = '0';
    LCD_Write(2, 17, EstaH4);


    if (bandera_H5) {
        EstaH5 = '1';
    } else
        EstaH5 = '0';
    LCD_Write(3, 17, EstaH5);



    if (PORT_BOTON1 == 1) {
        while (PORT_BOTON1 == 1);
        op++;
        if (op > 6) {
            op = 1;
        }
    }
    if (PORT_BOTON2 == 1) {
        while (PORT_BOTON2 == 1);
        op--;
        if (op < 1) {
            op = 6;
        }
    }


    if (PORT_BOTON3 == 1) {
        while (PORT_BOTON3 == 1);
        switch (op) {
            case 1: bandera_H1 = !(bandera_H1);
                break;
            case 2: bandera_H2 = !(bandera_H2);
                break;
            case 3: bandera_H3 = !(bandera_H3);
                break;
            case 4: bandera_H4 = !(bandera_H4);
                break;
            case 5: bandera_H5 = !(bandera_H5);
                break;
            case 6: Menu_actual = M2;
                break;
        }
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

    //Hallazgos_externos();

}

//2.2 menu fijar humeda

void Menu_Fijar_Humedad() {
    
    Humedad_RU = Humedad_R %10;
    Humedad_RD = Humedad_R /10;
     
     //                   12345678901234567890  
    LCD_Write_Text(1, 1, " MENU FIJAR HUMEDAD ");
    LCD_Write_Text(2, 1, "Ingrese humedad 0-99");
    LCD_Write_Text(3, 1, "Rango %:            ");
    LCD_Write_Text(4, 1, "1Estado:    2Volver ");
    LCD_Write(3, 13, Humedad_RD + 48);
    LCD_Write(3, 14, Humedad_RU + 48);
    
    switch (op) {
        case 1:
            LCD_Write(4, 11, '<');
            LCD_Write(4, 20, ' ');
            break;
        case 2:
            LCD_Write(4, 11, ' ');
            LCD_Write(4, 20, '<');
            break;
    }
    
     if (Bandera_Hum) {
        estado_hum = '1';
    } else
        estado_hum = '0';
    LCD_Write(4, 9, estado_hum);
    
    
      if (PORTCbits.RC0) {
        while (PORTCbits.RC0);
        op++;
        if (op > 2) {
            op = 1;
        }
    }
    
      if (PORTCbits.RC2) {
        while (PORTCbits.RC2);
        
        switch(op){
            case 1 : Bandera_Hum = !Bandera_Hum; break;  //con esta bandera se puede establecer modo automatico 
            case 2 : Menu_actual = M2; break;
        }
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }


    
    
    if (PORTCbits.RC1) {
        while (PORTCbits.RC1);
        __delay_ms(50);
        Humedad_R++;
        if (Humedad_R > 99) {
            Humedad_R = 0;

        } 
    }
    
    

    //Hallazgos_externos();


}

//2.3 menu pendiente

void Menu_Pendiente() {
        
     //                    12345678901234567890  
    LCD_Write_Text(1, 1, "  EVENTOS PENDIENTES ");
    LCD_Write_Text(2, 1, "                     ");
    LCD_Write_Text(3, 1, "                     ");
    LCD_Write_Text(4, 1, "             Volver< ");
    
  
    if (bandera_H1 == 1){
    LCD_Write(2,1,'1');
    LCD_Write(2, 2, decenaH1 + 48);
    LCD_Write(2, 3, unidadH1 + 48);
    LCD_Write(2, 4, ':');
    LCD_Write(2, 5, decenaM1 + 48);
    LCD_Write(2, 6, unidadM1 + 48);
    LCD_Write(2, 7, ':');
    LCD_Write(2, 8, decenaS1 + 48);
    LCD_Write(2, 9, unidadS1 + 48);
    }else{
        LCD_Write(2,1,'1');
        LCD_Write_Text(2,2,"hora1 ok");
    }
    
        if (bandera_H2 == 1){
    LCD_Write(2,11,'2');
    LCD_Write(2, 12, decenaH2 + 48);
    LCD_Write(2, 13, unidadH2 + 48);
    LCD_Write(2, 14, ':');
    LCD_Write(2, 15, decenaM2 + 48);
    LCD_Write(2, 16, unidadM2 + 48);
    LCD_Write(2, 17, ':');
    LCD_Write(2, 18, decenaS2 + 48);
    LCD_Write(2, 19, unidadS2 + 48);
    }else{
        LCD_Write(2,11,'2');
        LCD_Write_Text(2,12,"hora2 ok");
    }
    
     if (bandera_H3 == 1){
    LCD_Write(3,1,'3');
    LCD_Write(3, 2, decenaH3 + 48);
    LCD_Write(3, 3, unidadH3 + 48);
    LCD_Write(3, 4, ':');
    LCD_Write(3, 5, decenaM3 + 48);
    LCD_Write(3, 6, unidadM3 + 48);
    LCD_Write(3, 7, ':');
    LCD_Write(3, 8, decenaS3 + 48);
    LCD_Write(3, 9, unidadS3 + 48);
    }else{
        LCD_Write(3,1,'3');
        LCD_Write_Text(3,2,"hora3 ok");
    }
    
     if (bandera_H4 == 1){
    LCD_Write(3,11,'4');
    LCD_Write(3, 12, decenaH4 + 48);
    LCD_Write(3, 13, unidadH4 + 48);
    LCD_Write(3, 14, ':');
    LCD_Write(3, 15, decenaM4 + 48);
    LCD_Write(3, 16, unidadM4 + 48);
    LCD_Write(3, 17, ':');
    LCD_Write(3, 18, decenaS4 + 48);
    LCD_Write(3, 19, unidadS4 + 48);
    }else{
        LCD_Write(3,11,'4');
        LCD_Write_Text(3,12,"hora4 ok");
    }
    
     if (bandera_H5 == 1){
    LCD_Write(4,1,'5');
    LCD_Write(4, 2, decenaH5 + 48);
    LCD_Write(4, 3, unidadH5 + 48);
    LCD_Write(4, 4, ':');
    LCD_Write(4, 5, decenaM5 + 48);
    LCD_Write(4, 6, unidadM5 + 48);
    LCD_Write(4, 7, ':');
    LCD_Write(4, 8, decenaS5 + 48);
    LCD_Write(4, 9, unidadS5 + 48);
    }else{
        LCD_Write(4,1,'5');
        LCD_Write_Text(4,2,"hora5 ok");
    }


    if (PORT_BOTON1 == 1) {
        while (PORT_BOTON1 == 1);
        
    }
    
      if (PORT_BOTON3 == 1) {
        while (PORT_BOTON3 == 1);
        Menu_actual= M2;
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

    //Hallazgos_externos();

}


//3. MENU ACTUADORES Y SENSORES

void Menu_Act_Sen_3() {
    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "   MENU 3 ACT/SEN   ");
    LCD_Write_Text(2, 1, "1Sensores     4Op:  ");
    LCD_Write_Text(3, 1, "2Actuadores         ");
    LCD_Write_Text(4, 1, "3Volver             ");
    LCD_Write(2, 19, op + 48);

    switch (op) {
        case 1:
            LCD_Write(2, 10, '<');
            LCD_Write(2, 19, ' ');
            LCD_Write(3, 12, ' ');
            LCD_Write(4, 8, ' ');
            break;
        case 2:
            LCD_Write(2, 10, ' ');
            LCD_Write(2, 19, ' ');
            LCD_Write(3, 12, '<');
            LCD_Write(4, 8, ' ');
            break;
        case 3:
            LCD_Write(2, 10, ' ');
            LCD_Write(2, 19, ' ');
            LCD_Write(3, 12, ' ');
            LCD_Write(4, 8, '<');
            break;

    }

    if (PORT_BOTON1 == 1) {
        while (PORT_BOTON1 == 1);
        op++;
        if (op > 3) {
            op = 1;
        }
    }
    if (PORT_BOTON2 == 1) {
        while (PORT_BOTON2 == 1);
        op--;
        if (op < 1) {
            op = 3;
        }
    }
    if (PORT_BOTON3 == 1) {
        while (PORT_BOTON3 == 1);
        switch (op) {
            case 1: Menu_actual = M3sen;
                break;
            case 2: Menu_actual = M3act;
                break;
            case 3: Menu_actual = MP;
        }
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

   // Hallazgos_externos();


}

//3.1 menu sensores

void Menu_Sensores() {

    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "    MENU SENSORES   ");
    LCD_Write_Text(2, 1, "1Sen:     4Sen:     ");
    LCD_Write_Text(3, 1, "2Sen:     5:Volver  ");
    LCD_Write_Text(4, 1, "3Sen:               ");
    LCD_Write(3, 19, '<');

    Lectura_Sensor1();
    Lectura_Sensor2();
    Lectura_Sensor3();
    Lectura_Sensor4();
    __delay_ms(500);

    if (PORT_BOTON3 == 1) {
        while (PORT_BOTON3 == 1);
        Menu_actual = M3;
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

    //Hallazgos_externos();
}

//3.2 menu actuadores

void Menu_Actuadores() {

    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "   MENU ACTUADORES  ");
    LCD_Write_Text(2, 1, "1Estado       4Op:  ");
    LCD_Write_Text(3, 1, "2Config             ");
    LCD_Write_Text(4, 1, "3Volver             ");
    LCD_Write(2, 19, op + 48);

    switch (op) {
        case 1:
            LCD_Write(2, 8, '<');
            LCD_Write(3, 8, ' ');
            LCD_Write(4, 8, ' ');
            break;
        case 2:
            LCD_Write(2, 8, ' ');
            LCD_Write(3, 8, '<');
            LCD_Write(4, 8, ' ');
            break;
        case 3:
            LCD_Write(2, 8, ' ');
            LCD_Write(3, 8, ' ');
            LCD_Write(4, 8, '<');
            break;


    }

    if (PORTCbits.RC0) {
        while (PORTCbits.RC0);
        op++;
        if (op > 3) {
            op = 1;
        }
    }
    if (PORTCbits.RC1) {
        while (PORTCbits.RC1);
        op--;
        if (op < 1) {
            op = 3;
        }
    }


    if (PORTCbits.RC2) {
        while (PORTCbits.RC2);
        switch (op) {
            case 1: Menu_actual = MAestado;
                break;
            case 2: Menu_actual = MAconfig;
                break;
            case 3: Menu_actual = M3;
        }
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }
    //Hallazgos_externos();

}
//3.3 menu estado de actuadores

void Menu_ActEstados() {

    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "   MENU ESTADO ACT  ");
    LCD_Write_Text(2, 1, "1ENG:     4ENG:     ");
    LCD_Write_Text(3, 1, "2ENG:     5:Volver  ");
    LCD_Write_Text(4, 1, "3ENG:               ");
    LCD_Write(3, 19, '<');

    //Lectura Motor 1

    if (PORTBbits.RB1) {
        Est1 = '1';
    } else
        Est1 = '0';
    LCD_Write(2, 6, Est1);

    //Lectura Motor 2
    if (PORTBbits.RB2) {
        Est2 = '1';
    } else
        Est2 = '0';
    LCD_Write(3, 6, Est2);

    //Lectura Motor 3

    if (PORTBbits.RB3) {
        Est3 = '1';
    } else
        Est3 = '0';
    LCD_Write(4, 6, Est3);

    //Lectura Motor 4
    if (PORTBbits.RB4) {
        Est4 = '1';
    } else
        Est4 = '0';
    LCD_Write(2, 16, Est4);

    //__delay_ms(100);*
    if (PORTCbits.RC2) {
        while (PORTCbits.RC2);
        Menu_actual = M3act;
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }
    //Hallazgos_externos();
}
//3,4 menu configurar actuadores

void Menu_ActConfig() {
    //                    12345678901234567890
    LCD_Write_Text(1, 1, "    MENU MOTORES    ");
    LCD_Write_Text(2, 1, "1ENG:     4ENG:     ");
    LCD_Write_Text(3, 1, "2ENG:     5:Volver  ");
    LCD_Write_Text(4, 1, "3ENG:               ");

    switch (op) {
        case 1:
            LCD_Write(2, 7, '<');
            LCD_Write(2, 16, ' ');
            LCD_Write(3, 7, ' ');
            LCD_Write(3, 19, ' ');
            LCD_Write(4, 9, ' ');
            break;
        case 2:
            LCD_Write(2, 7, ' ');
            LCD_Write(2, 16, ' ');
            LCD_Write(3, 7, '<');
            LCD_Write(3, 19, ' ');
            LCD_Write(4, 9, ' ');
            break;
        case 3:
            LCD_Write(2, 7, ' ');
            LCD_Write(2, 16, ' ');
            LCD_Write(3, 7, ' ');
            LCD_Write(3, 19, ' ');
            LCD_Write(4, 7, '<');
            break;
        case 4:
            LCD_Write(2, 7, ' ');
            LCD_Write(2, 16, '<');
            LCD_Write(3, 7, ' ');
            LCD_Write(3, 19, ' ');
            LCD_Write(4, 9, ' ');
            break;
        case 5:
            LCD_Write(2, 7, ' ');
            LCD_Write(2, 16, ' ');
            LCD_Write(3, 7, ' ');
            LCD_Write(3, 19, '<');
            LCD_Write(4, 9, ' ');
            break;
    }

    if (PORTCbits.RC0) {
        while (PORTCbits.RC0);
        op++;
        if (op > 5) {
            op = 1;
        }
    }
    if (PORTCbits.RC1) {
        while (PORTCbits.RC1);
        op--;
        if (op < 1) {
            op = 5;
        }
    }


    if (PORTCbits.RC2) {
        while (PORTCbits.RC2);
        switch (op) {
            case 1: LATBbits.LATB1 = !(PORTBbits.RB1);
                break;
            case 2: LATBbits.LATB2 = !(PORTBbits.RB2);
                break;
            case 3: LATBbits.LATB3 = !(PORTBbits.RB3);
                break;
            case 4: LATBbits.LATB4 = !(PORTBbits.RB4);
                break;
            case 5: Menu_actual = M3act;
                break;
        }
        op = 1;
        LCD_Cmd(_LCD_CLEAR);

    }

    //Hallazgos_externos();

}


//4. MENU REGISTRO

void Menu_Registro_4() {

    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "   MENU 4 REGISTRO  ");
    LCD_Write_Text(2, 1, "1Hec1A:   3Hec2A:   ");
    LCD_Write_Text(3, 1, "2Hec1B:   4Hec2B:   ");
    LCD_Write_Text(4, 1, "5Volver             ");
    LCD_Write(4, 8, '<');

    LCD_Write(2, 8, Hallazgo1AD + 48);
    LCD_Write(2, 9, Hallazgo1AU + 48);

    LCD_Write(3, 8, Hallazgo1BD + 48);
    LCD_Write(3, 9, Hallazgo1BU + 48);

    LCD_Write(2, 18, Hallazgo2AD + 48);
    LCD_Write(2, 19, Hallazgo2AU + 48);

    LCD_Write(3, 18, Hallazgo2BD + 48);
    LCD_Write(3, 19, Hallazgo2BU + 48);


    if (PORT_BOTON3 == 1) {
        while (PORT_BOTON3 == 1);
        Menu_actual = MP;
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

    //Hallazgos_externos();

}




//5. MENU SISTEMA

void Menu_Sistema_5() {
    

    //                    12345678901234567890  
    LCD_Write_Text(1, 1, "   MENU 5 SISTEMA   ");
    LCD_Write_Text(2, 1, "                    ");
    LCD_Write_Text(3, 1, "                    ");
    LCD_Write_Text(4, 1, "Volver              ");
 
    
    
    modificar_tiempo();

    if (PORT_BOTON3 == 1) {
        while (PORT_BOTON3 == 1);
        Menu_actual = MP;
        op = 1;
        LCD_Cmd(_LCD_CLEAR);
    }

    //Hallazgos_externos();

}




void Hallazgos_externos() {
    if (PORTAbits.RA4) {
        while (PORTAbits.RA4);

        Hallazgo1AU = Hallazgos1A % 10;
        Hallazgo1AD = Hallazgos1A / 10;

        if (Hallazgo1AU > 9) {
            Hallazgo1AU = 9;
            Hallazgo1AD++;

            if (Hallazgo1AD > 9) {
                Hallazgo1AD = 9;

            }
        }
        bandera_H1A = 1;
        LAT_BANDERA = 1;
    }

    if (PORTAbits.RA5) {
        while (PORTAbits.RA5);

        Hallazgo1BU = Hallazgos1B % 10;
        Hallazgo1BD = Hallazgos1B / 10;



        if (Hallazgo1BU > 9) {
            Hallazgo1BU = 9;
            Hallazgo1BD++;

            if (Hallazgo1BD > 9) {
                Hallazgo1BD = 9;

            }
        }

        bandera_H1B = 1;
        LAT_BANDERA = 1;
    }

    if (PORTBbits.RB5) {
        while (PORTBbits.RB5);

        Hallazgo2AU = Hallazgos2A % 10;
        Hallazgo2AD = Hallazgos2A / 10;



        if (Hallazgo2AU > 9) {
            Hallazgo2AU = 9;
            Hallazgo2AD++;

            if (Hallazgo2AD > 9) {
                Hallazgo2AD = 9;

            }
        }
        bandera_H2A = 1;
        LAT_BANDERA = 1;
    }

    if (PORTBbits.RB6) {
        while (PORTBbits.RB6);

        Hallazgo2BU = Hallazgos2B % 10;
        Hallazgo2BD = Hallazgos2B / 10;



        if (Hallazgo2BU > 9) {
            Hallazgo2BU = 9;
            Hallazgo2BD++;

            if (Hallazgo2BD > 9) {
                Hallazgo2BD = 9;

            }
        }
        bandera_H2B = 1;
        LAT_BANDERA = 1;
    }
}

void Bombas_Sensores(){
    if (Bandera_Hum == 1){
        
        if (Sensor_1 > Humedad_R){
            Activar_Bomba1(1);
        }
        
         if (Sensor_2 > Humedad_R){
            Activar_Bomba2(1);
        }
        
         if (Sensor_3 > Humedad_R){
            Activar_Bomba3(1);
        }
        
         if (Sensor_4 > Humedad_R){
            Activar_Bomba4(1);
        }
        
    }
}



