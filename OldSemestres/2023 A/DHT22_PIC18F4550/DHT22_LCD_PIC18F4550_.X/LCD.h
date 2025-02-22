
//////////////////////////////////////////////////////////////////////////
////  Mombre :      LCD.h                                             ////
////  Creación :    04/11/2018                                        ////
////  Descripción:  Configurable con cualquier PIN                    ////
////                Para familia mejorada LAT                         ////
////  LCD_init()    Inicializa PORTB con pull up.                     ////
////  LCD_dato(c)   Envia dato por el LCD                             ////
////                                                                  ////
//////////////////////////////////////////////////////////////////////////

//#ifndef LCD_H
//#define LCD_H
#define _XTAL_FREQ 20000000

#include <xc.h>
#include <stdlib.h>	//Para poder mostrar enteros
#include <stdint.h>	//Para poder usar tipo uint


//******** Pines para los datos del LCD *********

#define D4          LATDbits.LATD4          // pin       
#define D5          LATDbits.LATD5          // pin      
#define D6          LATDbits.LATD6          // pin             
#define D7          LATDbits.LATD7          // pin

#define TRIS_D4     TRISDbits.TRISD4
#define TRIS_D5     TRISDbits.TRISD5
#define TRIS_D6     TRISDbits.TRISD6
#define TRIS_D7     TRISDbits.TRISD7

//******** Pines para el control del LCD **********

#define RS          LATDbits.LATD3           //Pin
#define EN          LATDbits.LATD2           //Pin

#define TRIS_RS     TRISDbits.TRISD3  	
#define TRIS_EN     TRISDbits.TRISD2  

#define ON  1
#define OFF 0

/******** Comandos para LCD *******/

#define LCD_CLEAR       0X01    //Limpia pantalla
#define LCD_CURSOR_ON   0X0F    //Cursor ON
#define LCD_CURSOR_OFF  0X0C    //Cursor off
#define LCD_LINEA1      0X02    //Primera línea
#define LCD_LINEA2      0XC0    //Segunda línea
#define LCD_LINEA3      0x94    //Tercera línea
#define LCD_LINEA4      0XD4    //Cuarta línea
#define LCD_LEFT        0X10    //Mueve cursor izquierda
#define LCD_RIGHT       0X14    //Mueve cursor derecha

#define ROT_LEFT        0X18    //Rotar izquierda
#define ROT_RIGHT       0X1C    //Rotar derecha

/************ Prototipos de funciones *************/

void LCD_init(void);                    	//Inicializa LCD
void LCD_cmd(unsigned char);                //Envia comando
void LCD_dato(unsigned char);               //Envia dato
void LCD_write(unsigned char dato);         //Rutina para enviar dato
void LCD_printf(unsigned char*);            //Imprime cadena de caracteres
void LCD_integer(int);                      //Imprime un entero
void LCD_goto(uint8_t, uint8_t);            //Mueve cursor a un XY
void LCD_cursor(unsigned char);             //Activa o desactiva cursor
void LCD_segunda_linea(void);
void LCD_clear(void);
void LCD_home(void);
void LCD_custom_char(unsigned char loc,unsigned char *msg);

//unsigned char TestBusyLCD (void);



