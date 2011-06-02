/* dynamic_led.h */

#ifndef DYNAMIC_LED_H
#define DYNAMIC_LED_H

uint8_t get_led_status(LED_t id, uint8_t num);
void set_led(LED_t id, uint8_t num, uint8_t duty);
void set_color_led(uint8_t red_val, uint8_t green_val, uint8_t blue_val);
void set_ledset(LED_t id, uint8_t *duty);
void get_led_status_nextline(uint8_t *duty);
void led_control(void);



#endif /* Not def: DYNAMIC_LED_H */
