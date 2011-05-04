#include <util/delay.h>

/* 1us待つよ！ */
void delay_us(uint16_t t){
    while(t--){
        _delay_us(1);
    }
}

/* 1ms待つよ！ */
void delay_ms(uint16_t t){
    while(t--){
        _delay_ms(1);
    }
}

/* 1s待つよ！ */
void delay_s(uint16_t t){
    while(t--){
        delay_ms(1000);
    }
}
