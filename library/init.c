/* init.c */

#include "library.h"
#include "uart_clk.h"

void init_all_port(void);

/* 初期化 */
void init(void){
    /* 全て一旦HiZに */
    init_all_port();
    /* だいたいUSARTはつかうっしょ */
    uart_init(br115200);

    /* ここから */
}


/* 全てHiZに */
void init_all_port(void){
    DDRB = 0x00;
    PORTB = 0x00;
    DDRC = 0x00;
    PORTC = 0x00;
    DDRD = 0x00;
    PORTD = 0x00;
}

