/* interrupt.c */

#include "library.h"


extern void control(void);

/* たいま割り込みべくた */
ISR(TIMER1_COMPA_vect){
    control();
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
    
    TCCR1A = 0b00000000;     /* OCnABはGPIO */
    TCCR1B = 0b00011010;     /* 1/8 prescale */
    TIMSK1 = _BV(OCIE1A);       /* OCR1A compare match interrupt enable */
    ICR1 = 625;                 /* 8(prescale) * 625 * (1/20000000) = 0.25[ms] */
    OCR1A = 625;                /* 8(prescale) * 1250* (1/20000000) = 0.50[ms] */
}


