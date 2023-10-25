

#ifndef LCD_LIB_H
#define	LCD_LIB_H

#include <xc.h>
#include "configuracion.h"

#define _LCD_CLEAR             1
#define _LCD_RETURN_HOME       2
#define _LCD_BLINK_CURSOR_ON   15
#define _LCD_CURSOR_OFF        12
#define _LCD_UNDERLINE_ON      14
#define _LCD_FIRST_ROW         128
#define _LCD_SECOND_ROW        192
#define _LCD_THIRD_ROW         148
#define _LCD_FOURTH_ROW        212
#define _LCD_MOVE_CURSOR_LEFT  16
#define _LCD_MOVE_CURSOR_RIGHT 20
#define _LCD_TURN_OFF          8
#define _LCD_TURN_ON           15
#define _LCD_SHIFT_LEFT        24
#define _LCD_SHIFT_RIGHT       28

#define DIR_RS    TRISDbits.TRISD0
#define DIR_EN    TRISDbits.TRISD2
#define DIR_D4    TRISDbits.TRISD4
#define DIR_D5    TRISDbits.TRISD5
#define DIR_D6    TRISDbits.TRISD6
#define DIR_D7    TRISDbits.TRISD7

#define LAT_RS    LATDbits.LATD0
#define LAT_EN    LATDbits.LATD2
#define LAT_D4    LATDbits.LATD4
#define LAT_D5    LATDbits.LATD5
#define LAT_D6    LATDbits.LATD6
#define LAT_D7    LATDbits.LATD7

#define ANSEL_RS  ANSELDbits.ANSD0
#define ANSEL_EN  ANSELDbits.ANSD2
#define ANSEL_D4  ANSELDbits.ANSD4
#define ANSEL_D5  ANSELDbits.ANSD5
#define ANSEL_D6  ANSELDbits.ANSD6
#define ANSEL_D7  ANSELDbits.ANSD7

// Cremos el prototipo de funcion
void LCD_Init(void);
void LCD_Cmd(char cmd);
void LCD_Write_Cp(char letra);
void LCD_Write_Text_Cp(char *text);
void LCD_Set_Cursor(char fila, char col);
void LCD_Write(char fila, char col, char letra);
void LCD_Write_Text(char fil, char col, char *text);

#endif	/* LCD_LIB_H */
