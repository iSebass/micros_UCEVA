#include <xc.h>
#include "config.h"

#define MA1  LATDbits.LATD0
#define MA2  LATDbits.LATD1
#define MB1  LATDbits.LATD2
#define MB2  LATDbits.LATD3

#define MA1_DIR TRISDbits.TRISD0
#define MA2_DIR TRISDbits.TRISD1
#define MB1_DIR TRISDbits.TRISD2
#define MB2_DIR TRISDbits.TRISD3

#define BTN_UP PORTBbits.RB0
#define BTN_IZ PORTBbits.RB1
#define BTN_DR PORTBbits.RB2
#define BTN_AB PORTBbits.RB3

#define BTN_UP_DIR TRISBbits.TRISB0
#define BTN_IZ_DIR TRISBbits.TRISB1
#define BTN_DR_DIR TRISBbits.TRISB2
#define BTN_AB_DIR TRISBbits.TRISB3

void girar_derecha();
void girar_izquierda();
void avanzar();
void atras();

void main(void){
    ANSELB = 0x00;
    MA1_DIR  = 0;
    MA2_DIR  = 0;
    MB1_DIR  = 0;
    MB2_DIR  = 0;
    
    OPTION_REGbits.nWPUEN = 0; //Habilitamos R PULL UP INT
    WPUB = 0x0F;
    
    BTN_AB_DIR = 1;
    BTN_DR_DIR = 1;
    BTN_IZ_DIR = 1;
    BTN_UP_DIR = 1;
    
    while(1){
        
      if(BTN_UP == 0){
          avanzar();
      } 
      if(BTN_AB == 0){
          atras();
      }
      if(BTN_DR == 0){
          girar_derecha();
      }
      if(BTN_IZ == 0){
          girar_izquierda();
      }
      if( (PORTB & 0x0F) == 15){
          MA1 = 0;
          MA2 = 0;
          MB1 = 0;
          MB2 = 0;
      }
              
    }
    
    return;
}

void girar_derecha(){
    MA1 = 0;
    MA2 = 1;
    MB1 = 0;
    MB2 = 0;
}
void girar_izquierda(){
    MA1 = 0;
    MA2 = 0;
    MB1 = 1;
    MB2 = 0;
}
void avanzar(){
    MA1 = 0;
    MA2 = 1;
    MB1 = 1;
    MB2 = 0;
}
void atras(){
    MA1 = 1;
    MA2 = 0;
    MB1 = 0;
    MB2 = 1;
}
