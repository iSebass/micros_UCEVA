#include "Sensores.h"          //libreria con sensores de humeda
#include "Menu.h"
#include "configuracion.h"
#include "lcd_lib.h"
#include "adc_lib.h"          //libreria para conversion Analogo-digital
#include "reloj.h"
#include "Actuadores.h"
#include <stdio.h>             //usar sprintf,

char strLCD[20] = " ";
int conver;
extern float Sensor_1, Sensor_2, Sensor_3, Sensor_4;

void Iniciar_Sensores() {

    //Sensor 1
    DIR_SENSOR1 = 1; //sensor 1 como entrada
    ANSEL_SENSOR1 = 1; //sensor 1 puerto A0 como analogico

    //Sensor 2
    DIR_SENSOR2 = 1; //sensor 2 como entrada
    ANSEL_SENSOR2 = 1; //sensor 2 puerto A0 como analogico

    //Sensor 3
    DIR_SENSOR3 = 1; //sensor 3 como entrada
    ANSEL_SENSOR3 = 1; //sensor 3 puerto A0 como analogico

    //Sensor 4
    DIR_SENSOR4 = 1; //sensor 4 como entrada
    ANSEL_SENSOR4 = 1; //sensor 4 puerto A0 como analogico

}

void Lectura_Sensor1() {
    conver = ADC_Get_Value(0);
    Sensor_1 = (1.0 - (conver * 1.0) / 1023.0)*100.0;
    //sprintf(strLCD, "%0.1f", Sensor_1);
    LCD_Write_Text(2, 6, strLCD);
    LCD_Write_Cp('%');

    //__delay_ms(200);
}

void Lectura_Sensor2() {
    conver = ADC_Get_Value(1);
    Sensor_2 = (1.0 - (conver * 1.0) / 1023.0)*100.0;
    //sprintf(strLCD, "%0.1f", Sensor_2);
    LCD_Write_Text(3, 6, strLCD);
    LCD_Write_Cp('%');

    //__delay_ms(200);
}

void Lectura_Sensor3() {
    conver = ADC_Get_Value(2);
    Sensor_3 = (1.0 - (conver * 1.0) / 1023.0)*100.0;
    //sprintf(strLCD, "%0.1f", Sensor_3);
    LCD_Write_Text(4, 6, strLCD);
    LCD_Write_Cp('%');

    //__delay_ms(200);
}

void Lectura_Sensor4() {
    conver = ADC_Get_Value(3);
    Sensor_4 = (1.0 - (conver * 1.0) / 1023.0)*100.0;
    sprintf(strLCD, "%0.1f", Sensor_4);
    LCD_Write_Text(2, 16, strLCD);
    LCD_Write_Cp('%');

    //__delay_ms(200);
}
