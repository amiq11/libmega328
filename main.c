/* main.c */
#include "library.h"

extern uint8_t f_led[2];


int main(void){

    init();                     /* 初期化 */


    init_interrupt();
    
    pin_out_init(DDRB,PB4);
    set_pin_hi(PORTB,PB4);
    printf("set hi\n");
    delay_ms(500);
    set_pin_low(PORTB,PB4);
    printf("set low\n");


    pin_out_init(DDRB,PB0);
    pin_out_init(DDRD,PD7);

    init_pwm(PWM_PD6);
    init_pwm(PWM_PD5);
    init_pwm(PWM_PB3);

    sei();                      /* 割り込み許可 */


    /* 本文 */
    printf("\n\n_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n"
           "test program for atmega328p library\n"
           "by Shimazu Makoto\n"
           "_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
    printf("\n");
    printf("press \"s\" key, then program will start!\n"
           "and after that, when you press \"q\" key, main loop will stop.\n\n");
    
    
    
    /* メインループ */
    
    /* モード定義 */
    #define UARTMODE 0
    #define PWMMODE 1
    #define ADCMODE 2
    #define OUTPUTMODE 3
    #define INPUTMODE 4
    
    while(1){
        static uint8_t f_start=0;
        static uint8_t f_pwmnum=0;
        
        int bufc = r_getc_noblock();
        
        /* モード変更 */
        switch(bufc){
        case 'q':
            f_start=0;
            printf("pressed \"q\" key\n");
            break;

        case 's':
            f_start=1;
            printf("pressed \"s\" key\n");
            break;
        }

        if(char_to_int(bufc)>=0 && char_to_int(bufc)<=9) {
            f_pwmnum=char_to_int(bufc);
            printf("pwm mode is changed to %d\n",f_pwmnum);
        }
        
        
        if(f_start){
            /* const  uint16_t time = 1; */
            static uint8_t f_color=0;
            set_led_condition(0,f_color);
            set_led_condition(1,f_color);
            set_led_condition(2,f_color);
            int i;
            for(i=5;i>=0;i--)
                printf("%d",(f_color>>i)&0x01);
            printf("\n");
            /* if(f_color == 0) { */
            /*     set_led_condition(0,~(0b00110000)); */
            /*     set_led_condition(1,~(0b00001100)); */
            /*     set_led_condition(2,~(0b00000011)); */
            /* } */
            /* if(f_color == 1){ */
            /*     set_led_condition(0,~(0b00001100)); */
            /*     set_led_condition(1,~(0b00000011)); */
            /*     set_led_condition(2,~(0b00110000)); */
            /* } */
            /* if(f_color == 2){ */
            /*     set_led_condition(0,~(0b00000011)); */
            /*     set_led_condition(1,~(0b00110000)); */
            /*     set_led_condition(2,~(0b00001100)); */
            /* }             */
            delay_ms(f_pwmnum*50);

            if(f_color<0b00111111) f_color++;
            else f_color = 0;
        }
    }
    
    
    return 0;
}
