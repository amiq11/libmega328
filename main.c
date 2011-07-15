/* main.c */
#include "library.h"
#include "api.h"
#include <avr/eeprom.h>
#include <math.h>

/* 以下の二つを使うためには、old_sw[]という配列が、スイッチのid分の大きさで必要 */
#define pushed_on(id) ((old_sw[(id)]==0 && get_sw((id))==1)?1:0) /* スイッチが押されたか確かめる。 */
#define save_sw_condition(id) (old_sw[(id)] = get_sw((id))) /* pushed_on()を使うためにこれがpushed_onの後に必要。 */



int main(void){

    init();                     /* 初期化 */
    init_adc(ADC3D);            /* ジョイスティック */
    init_adc(ADC4D);
    sei();                      /* 割り込み許可 */


    /* 本文 */
    printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n"
           "Semi in 2011 Summer\n"
           "Sample Program\n"
           "by Shimazu Makoto\n"
           "Date: 11-06-02\n"
           "_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
    load_accel_horizontal();

    /* メインループ */
    while(1){
        static uint8_t old_sw[8]={0};
        int16_t buf[4]={0};
        uint8_t id;
        
        if(pushed_on(0))
            save_accel_horizontal();
        
        save_sw_condition(0);
        

        buf[X]=get_accel(X);
        buf[Y]=get_accel(Y);
        buf[Z]=get_accel(Z);
        /* buf[X]=read_adc(ADC3D); */
        /* buf[Y]=read_adc(ADC4D); */
        /* buf[Z]=0; */
        
        
        /* buf[X]=get_accel_direct(X); */
        /* buf[Y]=get_accel_direct(Y); */
        /* buf[Z]=get_accel_direct(Z); */
        

        
        if(buf[X]<0){
            id=3-(uint8_t)(abs(buf[X])/50);
        }else{
            id=4+(uint8_t)(abs(buf[X])/50);
        }

        
        for(uint8_t i=0;i<8;i++){
            if(i==id)
                set_led(i,255);
            else
                set_led(i,0);
        }

        set_color_led((buf[X]>>1)&0xFF ,(buf[Y]>>1)&0xFF,(buf[Z]>>1)&0xFF);
        
        /* printf("%5d %5d %5d LED:%d\n",abs((buf[X]*2))%255,abs((buf[Y]*2))%255,abs((buf[Z]*2))%255,id); */
        
        
        printf("%5d %5d %5d\n",
               buf[X],buf[Y],buf[Z]);
        /* printf("\033[%dA" ,1); //カーソルを上に移動 */
        
        /* set_color_led(buf[X]+0x7F,buf[Y]+0x7F,buf[Z]+0x7F); */
        
        

        delay_ms(10);
    }
    
    
    return 0;
}
