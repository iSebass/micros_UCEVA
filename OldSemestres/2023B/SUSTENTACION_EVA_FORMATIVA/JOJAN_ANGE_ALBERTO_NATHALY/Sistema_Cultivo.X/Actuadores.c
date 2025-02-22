#include "Actuadores.h"        //libreria con motores de bombeo 
#include "Menu.h"
#include "configuracion.h"
#include "lcd_lib.h"
#include "adc_lib.h"
#include "Sensores.h"
#include "reloj.h"
#include <stdio.h>             //usar sprintf, 

void Iniciar_Bombas() {

    //Motor 1
    DIR_BOMBA1 = 0;
    ANSEL_BOMBA1 = 0;
    LAT_BOMBA1 = 0;

    //Motor 2
    DIR_BOMBA2 = 0;
    ANSEL_BOMBA2 = 0;
    LAT_BOMBA2 = 0;

    //Motor 3
    DIR_BOMBA3 = 0;
    ANSEL_BOMBA3 = 0;
    LAT_BOMBA3 = 0;

    //Motor 4
    DIR_BOMBA4 = 0;
    ANSEL_BOMBA4 = 0;
    LAT_BOMBA4 = 0;

}

void Activar_Bomba1(char estado1) {
    if (estado1 == 1) {
        LAT_BOMBA1 = 1;
    } else {
        LAT_BOMBA1 = 0;
    }
}

void Activar_Bomba2(char estado2) {
    if (estado2 == 1) {
        LAT_BOMBA2 = 1;
    } else {
        LAT_BOMBA2 = 0;
    }
}

void Activar_Bomba3(char estado3) {
    if (estado3 == 1) {
        LAT_BOMBA3 = 1;
    } else {
        LAT_BOMBA3 = 0;
    }
}

void Activar_Bomba4(char estado4) {
    if (estado4 == 1) {
        LAT_BOMBA4 = 1;
    } else {
        LAT_BOMBA4 = 0;
    }
}


