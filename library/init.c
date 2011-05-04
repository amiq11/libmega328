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

