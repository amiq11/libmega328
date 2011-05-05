/* interrupt.c */

#include "library.h"



uint8_t f_led[3] = {0};

/* たいま割り込みべくた */
ISR(TIMER1_COMPA_vect){
    static uint8_t f_onled=0;

    switch(f_onled){
    case 0:
        set_pin_low(PORTB,PB4);
        set_pwm(0,0);
        set_pwm(1,0);
        set_pwm(4,0);
        delay_us(150);
        set_pin_hi(PORTB,PB0);
        set_pwm(0,(f_led[0]&0x30)<<2);
        set_pwm(1,(f_led[0]&0x0C)<<4);
        set_pwm(4,(f_led[0]&0x03)<<6);
        f_onled++;
        OCR1A += 312;
        break;
    case 1:
        set_pin_low(PORTB,PB0);
        set_pwm(0,0);
        set_pwm(1,0);
        set_pwm(4,0);
        delay_us(150);
        set_pin_hi(PORTD,PD7);
        set_pwm(0,(f_led[1]&0x30)<<2);
        set_pwm(1,(f_led[1]&0x0C)<<4);
        set_pwm(4,(f_led[1]&0x03)<<6);
        f_onled++;
        OCR1A += 312;
        break;
    case 2:
        set_pin_low(PORTD,PD7);
        set_pwm(0,0);
        set_pwm(1,0);
        set_pwm(4,0);
        delay_us(150);
        set_pin_hi(PORTB,PB4);
        set_pwm(0,(f_led[2]&0x30)<<2);
        set_pwm(1,(f_led[2]&0x0C)<<4);
        set_pwm(4,(f_led[2]&0x03)<<6);
        f_onled = 0;
        OCR1A = 312;
        break;
    }
}

/* ISR(TIMER1_COMPB_vect){ */
/*     set_pin_low(PORTB,PB0); */
/*     set_pwm(0,0); */
/*     set_pwm(1,0); */
/*     set_pwm(4,0); */
/*     delay_us(200); */
/*     set_pin_hi(PORTD,PD7); */
/*     set_pwm(0,(f_led[1]&0x30)<<2); */
/*     set_pwm(1,(f_led[1]&0x0C)<<4); */
/*     set_pwm(4,(f_led[1]&0x03)<<6); */
    
/* } */

/* ISR(TIMER1_OVF_vect){ */
/*     set_pin_low(PORTD,PD7); */
/*     set_pwm(0,0); */
/*     set_pwm(1,0); */
/*     set_pwm(4,0); */
/*     delay_us(200); */
/*     set_pin_hi(PORTB,PB4); */
/*     set_pwm(0,(f_led[2]&0x30)<<2); */
/*     set_pwm(1,(f_led[2]&0x0C)<<4); */
/*     set_pwm(4,(f_led[2]&0x03)<<6); */
/* }     */


void init_interrupt(void){
    /* timer1をつかって割り込み */
    /* 制御周期は1ms */
    /* といいつつ、3msになった */
    
    /* WGM = 12 TOP:ICR1 CTCmode */
    
    TCCR1A = 0x00;     /* OCnABはGPIO */
    TCCR1B = 0x1B;     /* 1/64 prescale */
    TIMSK1 = _BV(OCIE1A);       /* OCR1A compare match interrupt enable */
    ICR1 = 936;                 /* 64(prescale) * 625 * (1/20000000) = 2[ms] */
    OCR1A = 312;
}

void set_led_condition(uint8_t id,uint8_t val){
    f_led[id] = val;
}

