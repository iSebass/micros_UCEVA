#include <xc.h>
#include <stdio.h>
#include "config.h"
#include "LCD_LIB.h"
#include "ADC.h"

char strLCD[20]=" ";

int conver;
float lm35, mcp, ldr;

void main(void){
    //CONFIGURAMOS LA SEÑALES DE RELOJ
    OSCCON  = 0x38; // OSC EXT HS
    //OSCCON  = 0x72; // OSC INT
    OSCTUNE = 0x00;
    BORCON  = 0x00;
    
    ANSELAbits.ANSA0 = 1;
    ANSELAbits.ANSA1 = 1;
    ANSELAbits.ANSA2 = 1;
    
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    
    ADC_Init();
    LCD_Init();
    LCD_Cmd(_LCD_CURSOR_OFF);
    
    while(1){
        conver = ADC_Get_Value(2);
        ldr = (100.0/1023.0)*conver;
        sprintf(strLCD,"LDR: %5.1f", ldr);
        LCD_Write_Text(3,1,strLCD);
        LCD_Write_Cp('%');
        
        conver = ADC_Get_Value(1);
        lm35   = (150.0/307.0)*conver;
        
        sprintf(strLCD,"LM35: %0.1f", lm35);
        LCD_Write_Text(1,1,strLCD);
        
        conver = ADC_Get_Value(0);
        mcp    = (165.0/337.59)*conver-50.0;
        
        sprintf(strLCD,"MCP: %0.1f", mcp);
        LCD_Write_Text(2,1,strLCD);
        
        __delay_ms(200);
        
    }
    return;
}
