/* adc.c */

#include "library.h"

/* init_adc(id) */
/* 引数：ADC0D〜ADC5D(enumで定義されている。) */
/* 機能：ADCの初期化を行う */
/* 　　　ADCを使うために、library/init.c内のinit()、またはmain関数のseiの前に定義してください。 */
void init_adc(int id){
    
    switch(id){
    case ADC0D:
        pin_in_init(DDRC,PC0);
        cbi(PORTC,PC0);
        break;
    case ADC1D:
        pin_in_init(DDRC,PC1);
        cbi(PORTC,PC1);
        break;
    case ADC2D:
        pin_in_init(DDRC,PC2);
        cbi(PORTC,PC2);
        break;
    case ADC3D:
        pin_in_init(DDRC,PC3);
        cbi(PORTC,PC3);
        break;
    case ADC4D:
        pin_in_init(DDRC,PC4);
        cbi(PORTC,PC4);
        break;
    case ADC5D:
        pin_in_init(DDRC,PC5);
        cbi(PORTC,PC5);
        break;
    }

    /* 基本設定 */
    sbi(ADMUX,REFS1);
    sbi(ADMUX,REFS0);
    cbi(ADMUX,ADLAR);
    sbi(ADCSRA,ADEN);
    ADCSRA |= 0b111;

}

/* read_adc(id) */
/* 引数：ADC0D〜ADC5D */
/* 機能；ADCを読み込む。返り値は10bit(だったはず) */
uint16_t read_adc(int id){
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


        
