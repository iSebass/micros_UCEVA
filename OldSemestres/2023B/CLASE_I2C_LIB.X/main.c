#include <xc.h>
#include "config.h"
#include "I2C_LIB.h"
#include "I2C_LCD_LIB.h"

char DIR_PCF = 0x3F;

int hh=0x23, mm=0x54, ss=0x30;
int dia=0x11, mes =0x12, year=0x24;

void main(void){
    
    OSCCON  = 0x38;
    OSCTUNE = 0x00;
    BORCON  = 0x00;
    
    I2C_Init();
    I2C_LCD_Init();
    I2C_LCD_Write_Text(2,5,"UCEVA");
    
    ANSELD = 0x00;
    TRISD = 0x00;
    
    while(1){
        I2C_Start();
        I2C_Wr(0b11010000);
        I2C_Wr(0x06);
        I2C_Restart();
        I2C_Wr(0b11010001);
        year = I2C_Rd();
        I2C_Stop();
        
        LATD = year;
        __delay_ms(500);
        
    }
    return;
}
