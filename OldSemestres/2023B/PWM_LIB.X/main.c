#include <xc.h>
#include "config.h"

#define dutyVal 400

void main(void){
    OSCCON  = 0x38;
    OSCTUNE = 0x00;
    BORCON  = 0x00;
    

    //CONFIGURAMOS EL PIN PARA CCP4
    ANSELDbits.ANSD1 = 0;
    TRISDbits.TRISD1 = 0;
    
    //SELECCIONAMOS EL TIMER A TRABAJAR
    CCPTMRS0bits.C4TSEL = 0b00; //SELECCIONAMOS TIMER2
    
    //LIMPIAMOS EL TIMER 2
    TMR2 = 0;
    PR2  = 155;
    T2CONbits.T2CKPS = 0b10; // PRE 16
    
    //CONFIGURAMOS MODO PWM
    CCP4CONbits.CCP4M3 = 1; 
    CCP4CONbits.CCP4M2 = 1; 
    CCP4CONbits.CCP4M1 = 0;
    CCP4CONbits.CCP4M0 = 0;
    
    CCPR4H   = 0;
    CCPR4L   = (dutyVal&0x3FC)>>2;
    CCP4CON |= (dutyVal&0x003)<<5;
    
    T2CONbits.TMR2ON = 1;
    
    while(1){
        __delay_ms(30);
    }
    
    return;
}
