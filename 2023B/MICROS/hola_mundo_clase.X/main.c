#include <xc.h>
#include "config.h"

#define te 100

signed char contador=0;

void main(void){
    
    //CONFIGURA EL PROYECTO
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSA0 = 0;
    TRISAbits.TRISA1 = 1;
    ANSELAbits.ANSA1 = 0;
    
    
    TRISD = 0x00; //CONFIGURAMOS RD0->OUT
    PORTD = 0x00;
    
    //LOOP INFINITO
    while(1){
       
        if( PORTAbits.RA0 == 1 ){
            while(PORTAbits.RA0 == 1);
            contador++;
        }
        if(PORTAbits.RA1 == 0){
            while(PORTAbits.RA1 == 0);
            contador--;
        }
        if(contador>7){
            contador=0;
        }
        
        if(contador<0){
            contador=7;
        }
        LATD = contador;
        
    }
    
    return;
}
