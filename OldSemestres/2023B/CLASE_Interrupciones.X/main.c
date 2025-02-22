#include <xc.h>
#include "config.h"
#include "LCD_LIB.h"

int counter=0, unidades, decenas;
int counter2=99, flag_seg=0;

void __interrupt() nombre(){
    if(INTCONbits.INTF == 1){
        counter++;
        INTCONbits.INTF = 0;
    }
    if(INTCONbits.T0IF==1){
        flag_seg++;
        if(flag_seg==100){
            flag_seg=0;
            LATBbits.LATB7 ^=1;
        }
        TMR0 = 61;
        INTCONbits.T0IF=0;
    }
    
    
}

void main(void){
    OSCCON  = 0x38;
    OSCTUNE = 0x00;
    BORCON  = 0x00;
    
    
    LCD_Init();
    LCD_Cmd(12);
    
    
    INTCONbits.INTE = 1;
    INTCONbits.GIE  = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.T0IE = 1;
    
    ANSELB = 0x00;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB7 = 0;
    LATBbits.LATB7   = 0;
    
    OPTION_REGbits.T0CS = 0; // Internal Signal
    OPTION_REGbits.PSA  = 0; // Habilitamos el Preescaler
    OPTION_REGbits.T0SE  = 1;
    OPTION_REGbits.PS   = 0b111; // PREESCALER 256
    TMR0 = 61;

    while(1){
        
        decenas = counter / 10;
        unidades = counter  % 10;
        
        LCD_Write(1,1,decenas+48);
        LCD_Write(1,2,unidades+48);
        
        decenas = counter2 / 10;
        unidades = counter2  % 10;
        
        LCD_Write(3,1,decenas+48);
        LCD_Write(3,2,unidades+48);
        
        counter2--;
        if(counter2<0)
            counter2=99;
        
        __delay_ms(1000);
    }
    
    return;
}
