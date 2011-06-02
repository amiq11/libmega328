/* main.c */
#include "library.h"
#include "api.h"



int main(void){

    init();                     /* 初期化 */
    sei();                      /* 割り込み許可 */


    /* 本文 */
    printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n"
           "Semi in 2011 Summer\n"
           "Sample Program\n"
           "by Shimazu Makoto\n"
           "Date: 11-06-02\n"
           "_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
    
    
    /* メインループ */
    while(1){
        uint8_t buf[3];
        uint8_t i;
        for(i=0;i<3;i++){
            buf[i] = (read_adc(i)>>2 & 0xFF) * 2 - 0x80;
        }
        printf("%04d %04d %04d\n",
               buf[2],
               buf[1],
               buf[0]);
        set_color_led(
            buf[2],
            buf[1],
            buf[0]);
        /* static uint8_t i=0; */
        /* set_led(RED,0,i); */
        /* set_led(RED,1,i*2); */
        /* set_led(RED,2,i*3); */
        /* set_led(RED,3,i*4); */
        /* set_led(COLOR,R,i); */
        /* set_led(COLOR,G,i*2); */
        /* set_led(COLOR,B,i*4); */
        /* set_led(GREEN,0,0xFF-i); */
        /* set_led(GREEN,1,0xFF-i*2); */
        /* set_led(GREEN,2,0xFF-i*3); */
        /* set_led(GREEN,3,0xFF-i*4); */
        /* set_led(COLOR,R,i); */
        /* set_color_led(0,255,255); */
        /* if(i<250) i++; */
        /* else i=0; */
        delay_ms(100);
    }
    
    
    return 0;
}
