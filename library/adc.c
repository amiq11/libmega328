/* adc.c */

#include "library.h"

void adc_init(int id){
    
    switch(id){
    case ADC0D:
        pin_in_init(DDRC,PC0);
        break;
    case ADC1D:
        pin_in_init(DDRC,PC1);
        break;
    case ADC2D:
        pin_in_init(DDRC,PC2);
        break;
    case ADC3D:
        pin_in_init(DDRC,PC3);
        break;
    case ADC4D:
        pin_in_init(DDRC,PC4);
        break;
    case ADC5D:
        pin_in_init(DDRC,PC5);
        break;
    }

    /* 基本設定 */
    sbi(ADMUX,REFS1);
    sbi(ADMUX,REFS0);
    cbi(ADMUX,ADLAR);
    sbi(ADCSRA,ADEN);
    ADCSRA |= 0b111;

}

uint16_t adc_read(int id){
    uint16_t buf=0;
    sbi(DIDR0,id);
    ADMUX = ((ADMUX&0xF0) | id);
    sbi(ADCSRA,ADIF);
    sbi(ADCSRA,ADSC);
    loop_until_bit_is_set(ADCSRA,ADIF);
    buf = ADCW;
    cbi(DIDR0,id);
    return buf;
}


        
