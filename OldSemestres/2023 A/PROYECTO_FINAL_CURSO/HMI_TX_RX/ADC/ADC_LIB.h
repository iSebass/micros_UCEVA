
#ifndef ADC_LIB_H_
#define ADC_LIB_H_

#include <avr/io.h>
#include <stdint.h>

#define ADC0  0
#define ADC1  1
#define ADC2  2
#define ADC3  3
#define ADC4  4
#define ADC5  5
#define ADC6  6
#define ADC7  7
#define _TEMP_CH  8

#define _DIV_FREQ2A  0
#define _DIV_FREQ2B  1
#define _DIV_FREQ4   2
#define _DIV_FREQ8   3
#define _DIV_FREQ16  4
#define _DIV_FREQ32  5
#define _DIV_FREQ64  6
#define _DIV_FREQ128 7

#define _RESOL_  1023.0
#define _AREF_   5.0

#define _PRE_   _DIV_FREQ128

void ADC_Init(void);
uint16_t ADC_Read(uint8_t ch);
float ADC_Map(int conv1, float conv_min, float conv_max, float sal_min, float sal_max);

#endif /* ADC_H_ */