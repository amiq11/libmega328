/* pwm.c */

#include "library.h"


void pwm_init(int id){
    switch(id){
    case PWM_PD6:
        sbi(DDRD,PD6);          /* 出力設定 */
        cbi(PORTD,PD6);
        TCCR0A = (TCCR0A&0x3C) | _BV(COM0A1) | _BV(WGM00); /* Compare Match PWM */
        TCCR0B = (TCCR0B&0xF8) | _BV(CS01);                /* 1/8 prescaling */
        break;
    case PWM_PD5:
        sbi(DDRD,PD5);
        cbi(PORTD,PD5);
        TCCR0A = (TCCR0A&0xCC) | _BV(COM0B1) | _BV(WGM00); /* Compare Match PWM */
        TCCR0B = (TCCR0B&0xF8) | _BV(CS01);                /* 1/8 prescaling */
        break;
    case PWM_PB1:
        sbi(DDRB,PB1);          /* 出力設定 */
        cbi(PORTB,PB1);
        ICR1 = 0x07FF;          /* maxは0x07FF */
        TCCR1A = (TCCR1A&0x3C) | _BV(COM1A1); /*  Phase and Frequency Correct PWM */
        TCCR1B = (TCCR1B&0xE0) | _BV(WGM13) | _BV(CS10); /* no prescaling */
        break;
    case PWM_PB2:
        sbi(DDRB,PB2);
        cbi(PORTB,PB2);
        ICR1 = 0x07FF;
        TCCR1A = (TCCR1A&0xCC) | _BV(COM1B1);
        TCCR1B = (TCCR1B&0xE0) | _BV(WGM13) | _BV(CS10);
        break;
    case PWM_PB3:
        sbi(DDRB,PB3);          /* 出力設定 */
        cbi(PORTB,PB3);
        TCCR2A = (TCCR2A&0x3C) | _BV(COM2A1) | _BV(WGM20); /* Compare Match PWM */
        TCCR2B = (TCCR2B&0xF8) | _BV(CS21);                /* 1/8 prescaling */
        break;
    case PWM_PD3:
        sbi(DDRD,PD3);          /* 出力設定 */
        cbi(PORTB,PD3);
        TCCR2A = (TCCR2A&0xCC) | _BV(COM2B1) | _BV(WGM20); /* Compare Match PWM */
        TCCR2B = (TCCR2B&0xF8) | _BV(CS21);                /* 1/8 prescaling */
        break;
    }
}


/* dutyは0〜0x07FF(つまり2048) */
/* 8bitタイマの場合は3bitシフトしてます。 */
/* てかこれってどうするのがいいんだろう。 */
void pwm_set(int id, uint16_t duty){
    switch(id){
    case PWM_PD6:
        OCR0A = duty>>3;
        break;
    case PWM_PD5:
        OCR0B = duty>>3;
        break;
    case PWM_PB1:
        OCR1A = duty;
        break;
    case PWM_PB2:
        OCR1B = duty;
        break;
    case PWM_PB3:
        OCR2A = duty>>3;
        break;
    case PWM_PD3:
        OCR2B = duty>>3;
        break;
    }
}
        




        
       
