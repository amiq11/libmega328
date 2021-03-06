/* hal.c */
/* デバイスごとに変わるピン等を、ここで定義する。 */
/* 結構適当です。すみません。 */
/* デバイスの名前で貼り直してるだけという説も */
/* led関連はダイナミック点灯しているので、直接触らず、できるだけapiを使ってください。 */

#include "library.h"

/* select_led(id) */
/* id:{RED,GREEN,COLOR} */
/* 指定した色に対応するトランジスタをonにする */
void select_led(LED_t id){
        switch(id){
        case RED:
            set_pin_hi(RED_sel_PORT,RED_sel_PIN);
            break;
        case COLOR:
            set_pin_hi(COLOR_sel_PORT,COLOR_sel_PIN);
            break;
        case GREEN:
            set_pin_hi(GREEN_sel_PORT,GREEN_sel_PIN);
            break;
        default:
            break;
        }
}

/* set_led_pwm(id,duty) */
/* id:0-3 duty:0-255 */
/* 0が左 */
/* カラーLEDのidは 0:R 1:G 2:B */
/* 機能：select_ledによってonになっているトランジスタに対応するLEDにこのdutyがかかる */
void set_led_pwm(uint8_t id, uint8_t duty){
    switch(id){
    case 0:
        set_pwm(LED0_PWM, duty);
        break;
    case 1:
        set_pwm(LED1_PWM, duty);
        break;
    case 2:
        set_pwm(LED2_PWM, duty);
        break;
    case 3:
        set_pwm(LED3_PWM, duty);
        break;
    default:
        break;
    }
}

/* 全部のLEDを消す */
void clear_all_led(void){
    set_led_pwm(0,0);
    set_led_pwm(1,0);
    set_led_pwm(2,0);
    set_led_pwm(3,0);
    set_pin_low(RED_sel_PORT,RED_sel_PIN);
    set_pin_low(GREEN_sel_PORT,GREEN_sel_PIN);
    set_pin_low(COLOR_sel_PORT,COLOR_sel_PIN);
}

/* init_led */
/* ledを使うための各種設定を行う */
void init_led(void){
    init_pwm(LED0_PWM);
    init_pwm(LED1_PWM);
    init_pwm(LED2_PWM);
    init_pwm(LED3_PWM);
    pin_out_init(RED_sel_PORT,RED_sel_PIN);
    pin_out_init(GREEN_sel_PORT,GREEN_sel_PIN);
    pin_out_init(COLOR_sel_PORT,COLOR_sel_PIN);
}

/* 加速度センサを使うための各種設定を行う */
void init_accel(void){
    init_adc(ADC0D);
    init_adc(ADC1D);
    init_adc(ADC2D);
}
