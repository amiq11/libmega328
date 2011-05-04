/* main.c */
#include "library.h"

int main(void){
    init();                     /* 初期化 */

    
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
        static uint8_t f_mode=0;
        static uint8_t f_pwmnum=0;
        static uint32_t duty = 0; /* 計算中にオーバーフローしないようにuint32_t */
        
        int bufc = r_getc_noblock();
        
        /* モード変更 */
        switch(bufc){
        case 'q':
            f_start=0;
            printf("pressed \"q\" key\n");
            break;

        case 's':
            f_start=1;
            printf("pressed \"s\" key\n\n");
            break;

        case 'u':
            f_mode = UARTMODE;
            printf("uart mode\n\n");
            break;

        case 'p':
            f_mode = PWMMODE;

            int i;
            for(i=0;i<6;i++)
                pwm_init(i);

            printf("pwm mode\n\n");
            break;

        case 'a':
            f_mode = ADCMODE;
            
            adc_init(ADC0D);
            adc_init(ADC1D);
            adc_init(ADC2D);
            adc_init(ADC3D);
            adc_init(ADC4D);
            adc_init(ADC5D);
            
            printf("adc mode\n");
            break;

        case 'o':
            f_mode = OUTPUTMODE;

            pin_out_init(DDRB,PB1);

            printf("output mode\n");
            break;

        case 'i':
            f_mode = INPUTMODE;

            pin_in_init(DDRB,PB1);
            
            printf("input mode\n");
            break;
        }

        if(char_to_int(bufc)>=0 && char_to_int(bufc)<6) {
            pwm_set(f_pwmnum,0);
            duty=0;
            f_pwmnum=char_to_int(bufc);
            printf("pwm mode is changed to %d\n\n",f_pwmnum);
        }

        
        if(f_start){

            /* PWMテスト */
            if(f_mode == PWMMODE){
                pwm_set(f_pwmnum,duty); /* PWMset */
                printf("\033[%dA" ,1); /* カーソル移動 */
                printf("%05ld %2ld%% \n",duty,duty*100/0x7FF); /* duty表示 */
                if(duty<=0x7F0) duty+=0x0F;
                else duty = 0;
            }

            /* ADCテスト */
            if(f_mode == ADCMODE){
                printf("%04d ",adc_read(ADC0D));
                printf("%04d ",adc_read(ADC1D));
                printf("%04d ",adc_read(ADC2D));
                printf("%04d ",adc_read(ADC3D));
                printf("%04d ",adc_read(ADC4D));
                printf("%04d\n",adc_read(ADC5D));
            }

            /* 出力テスト */
            if(f_mode == OUTPUTMODE){
                set_pin_hi(PORTB,PB1);
                delay_ms(100);
                set_pin_low(PORTB,PB1);
                delay_ms(890);
            }

            /* 入力テスト */
            if(f_mode == INPUTMODE){
            }
        }
        delay_ms(10);
    }
    
    
    return 0;
}
