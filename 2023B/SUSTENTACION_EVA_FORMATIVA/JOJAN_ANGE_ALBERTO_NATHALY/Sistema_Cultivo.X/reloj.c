#include "reloj.h"
#include "Sensores.h"          //libreria con sensores de humeda
#include "Menu.h"
#include "configuracion.h"
#include "lcd_lib.h"
#include "adc_lib.h"          //libreria para conversion Analogo-digital
#include "Actuadores.h"
#include <stdio.h>             //usar sprintf,

//VARIABLES
extern int flag_seg;

//variables hora
//variables para la hora 
extern int segundos = 1, minutos = 0, horas = 0;
extern int unidadS, decenaS, unidadM, decenaM, unidadH, decenaH;


//CONFIGURAR FUNCIONES

void iniciar_reloj() {

    //INTERRUPCION PUERTO B0 (externa)
    INTCONbits.INTE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.T0IE = 1;

    //INTERRUPCIONES TIMER
    OPTION_REGbits.T0CS = 0; // Internal Signal
    OPTION_REGbits.PSA = 0; // Habilitamos el Preescaler
    OPTION_REGbits.T0SE = 1;
    OPTION_REGbits.PS = 0b111; // PREESCALER 256
    TMR0 = 61; //tiempo deseado

    //CONFIGURAR PIN RB0
    DIR_INT1 = 1; //interrupcion pin 0 como entrada (1)
    ANSEL_INT1 = 0; //interrupcion como entrada digital pin 0

}

void tiempo() {

    unidadS = segundos % 10;
    decenaS = segundos / 10;

    unidadM = minutos % 10;
    decenaM = minutos / 10;

    unidadH = horas % 10;
    decenaH = horas / 10;

    LCD_Write(4, 13, decenaH + 48);
    LCD_Write(4, 14, unidadH + 48);
    LCD_Write(4, 15, ':');
    LCD_Write(4, 16, decenaM + 48);
    LCD_Write(4, 17, unidadM + 48);
    LCD_Write(4, 18, ':');
    LCD_Write(4, 19, decenaS + 48);
    LCD_Write(4, 20, unidadS + 48);

    if (segundos > 59) {
        segundos = 0;
        minutos++;
        if (minutos > 59) {
            minutos = 0;
            horas++;
            if (horas > 23) {
                horas = 0;
            }
        }
    }


}

void aumento_seg() {

    if (PORT_BOTON4 == 1) {
        segundos++;

    }

}

void aumento_min() {
    if (PORT_BOTON2 == 1) {
        minutos++;

        if (minutos > 59) {
            minutos = 0;


        }
    }

}

void aumento_hor() {
    if (PORT_BOTON1 == 1) {
        horas++;
        if (horas > 23) {
            horas = 0;
        }
    }

}

void modificar_tiempo() {
    
    tiempo();
    aumento_hor();
    aumento_min();


    

}








