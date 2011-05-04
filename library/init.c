/* init.c */

#include "library.h"
#include "uart_clk.h"

void all_port_init(void);

/* 初期化 */
void init(void){
    /* 全て一旦HiZに */
    all_port_init();
    /* だいたいUSARTはつかうっしょ */
    uart_init(br115200);

    /* ここから */
    pin_out_init(DDRB,PB1);

    /* int i; */
    /* for(i=0;i<6;i++) */
    /*     pwm_init(i); */
    /* adc_init(ADC0D); */
    /* adc_init(ADC1D); */
    /* adc_init(ADC2D); */
    /* adc_init(ADC3D); */
    /* adc_init(ADC4D); */
    /* adc_init(ADC5D); */
}


/* 全てHiZに */
void all_port_init(void){
    DDRB = 0x00;
    PORTB = 0x00;
    DDRC = 0x00;
    PORTC = 0x00;
    DDRD = 0x00;
    PORTD = 0x00;
}

