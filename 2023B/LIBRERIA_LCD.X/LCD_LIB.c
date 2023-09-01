#include "LCD_LIB.h"

static void Load_Data(char data);
static void Load_Cmd(char cmd);

static void Load_Cmd(char cmd){
    LAT_RS = 0;
    
    if( (cmd & 1) == 0 ) LAT_D4 = 0; else LAT_D4 = 1;
    if( (cmd & 2) == 0 ) LAT_D5 = 0; else LAT_D5 = 1;
    if( (cmd & 4) == 0 ) LAT_D6 = 0; else LAT_D6 = 1;
    if( (cmd & 8) == 0 ) LAT_D7 = 0; else LAT_D7 = 1;
    
    LAT_EN = 0;
    LAT_EN = 1;
    LAT_EN = 0;
    __delay_us(300);
    
}
static void Load_Data(char data){
    LAT_RS = 1;
    
    if( (data & 1) == 0 ) LAT_D4 = 0; else LAT_D4 = 1;
    if( (data & 2) == 0 ) LAT_D5 = 0; else LAT_D5 = 1;
    if( (data & 4) == 0 ) LAT_D6 = 0; else LAT_D6 = 1;
    if( (data & 8) == 0 ) LAT_D7 = 0; else LAT_D7 = 1;
    
    LAT_EN = 0;
    LAT_EN = 1;
    LAT_EN = 0;
    
    __delay_us(300);
    
}

// Cremos el prototipo de funcion
void LCD_Init(void){
    //CONFIGURAMOS TODOS LOS PINES DE SALIDA
    DIR_RS = 0; DIR_EN = 0; DIR_D4 = 0;
    DIR_D5 = 0; DIR_D6 = 0; DIR_D7 = 0;
    //INICIAMOS PUERTO EN CERO
    LAT_EN = 0; LAT_D4 = 0; LAT_D5 = 0;
    LAT_D6 = 0; LAT_D7 = 0;
    
    __delay_ms(15);
    Load_Cmd(0x03);
    __delay_ms(5);
    Load_Cmd(0x03);
    __delay_us(100);
    Load_Cmd(0x03);
    Load_Cmd(0x02);
    
    Load_Cmd(0x02);
    Load_Cmd(0x08);
    
    Load_Cmd(0x00);
    Load_Cmd(0x0F);
    
    Load_Cmd(0x00);
    Load_Cmd(0x01);
    __delay_ms(2);
    
}
void LCD_Cmd(char cmd){
    char NibbleH, NibbleL;
    NibbleH = cmd>>4;
    NibbleL = cmd & 0x0F;
    Load_Cmd(NibbleH);
    Load_Cmd(NibbleL);
    __delay_ms(2);
}
void LCD_Write_Cp(char letra){
    char NibbleH, NibbleL;
    NibbleH = letra>>4;
    NibbleL = letra & 0x0F;
    Load_Data(NibbleH);
    Load_Data(NibbleL);
    
}

void LCD_Write_Text_Cp(char *text){
    
    while(*text){
        LCD_Write_Cp(*text);
        text++;
    }
    
}

void LCD_Set_Cursor(char fila, char col){
    char pos;
    switch(fila){
        case 1: pos = 0x80+(col-1); break;
        case 2: pos = 0xC0+(col-1); break;
        case 3: pos = 0x94+(col-1); break;
        case 4: pos = 0xD4+(col-1); break;
    }
    LCD_Cmd(pos);
}
void LCD_Write(char fila, char col, char letra){
    LCD_Set_Cursor(fila, col);
    LCD_Write_Cp(letra);
}
void LCD_Write_Text(char fila, char col, char *text){
    LCD_Set_Cursor(fila, col);
    while(*text){
        LCD_Write_Cp(*text);
        text++;
    }
}