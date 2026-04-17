#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "hal/gpio.h"
#include "hal/adc.h"
#include "libs/LCD_LIB.h"


int conver;
float volt, temp;


int main(void)
{
    hal_adc_config_t adc_cfg;
	
	adc_cfg.reference = HAL_ADC_REF_AVCC;
	adc_cfg.vref_mv   = 5000U;
	adc_cfg.prescaler = HAL_ADC_PRESCALER_128;
	adc_cfg.use_irq   = HAL_ADC_MODE_POLLING;
	
	HAL_ADC_Init(&adc_cfg);
	
	lcd_init();
	lcd_disable_blink();
	lcd_disable_cursor();
	
    while (1) 
    {
		HAL_ADC_ReadMillivolts(0, &conver);
		HAL_ADC_Read(1, &conver);
		
		temp = HAL_ADC_Map(conver, 0, 306, 0, 150);
		
		volt = conver/1000.0;
		
		
		lcd_set_cursor(1,1);
		lcd_printf("POT: %4.1f v", volt);
		
		lcd_set_cursor(2,1);
		lcd_printf("TEMP: %4.1f v", temp);
		
		_delay_ms(100);
    }
}

