/* dynamic_led.c */

#include "library.h"
#include "api.h"

/* dutyを入れるハコ */
static uint8_t led_status[3][4];
/* 次に表示する行 */
static uint8_t nextline;


uint8_t get_led_status(LED_t id, uint8_t num){
    return led_status[id][num];
}


void set_led(uint8_t id,uint8_t duty){
    if(id<4) led_status[RED][id]     = duty;
    else     led_status[GREEN][id-4] = duty;
}
    
/* void set_led(LED_t id, uint8_t num, uint8_t duty){ */
/*     led_status[id][num] = duty; */
/* } */

/* void set_led_line */

void set_color_led(uint8_t red_val, uint8_t green_val, uint8_t blue_val){
    led_status[COLOR][0] = red_val;
    led_status[COLOR][1] = green_val;
    led_status[COLOR][2] = blue_val;
}





void set_ledset(LED_t id, uint8_t *duty){
    int i;
    for(i=0; i<4; i++)
        led_status[id][i] = *(duty+i);
}


void get_led_status_nextline(uint8_t *duty){
    uint8_t i;
    if(nextline >=2) nextline = 0;
    else nextline++;
    for(i=0; i<4; i++,duty++)
        *duty = led_status[nextline][i];
}


void led_control(void){
    uint8_t duty[4]={0};
    uint8_t i;
    
    get_led_status_nextline(duty);
    clear_all_led();
    delay_us(10);
    for(i=0;i<4;i++)
        set_led_pwm(i,duty[i]);
    select_led(nextline);
    
}
