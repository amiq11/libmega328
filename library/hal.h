#ifndef HAL_H
#define HAL_H

typedef enum _COLOR{
    R=0,
    G=1,
    B=2
} COLOR_t;

typedef enum _LED{
    RED=0,
    COLOR=1,
    GREEN=2
} LED_t;




void clear_all_led(void);
void select_led(LED_t id);
void set_led_pwm(uint8_t id, uint8_t duty);
void init_led(void);
void init_accel(void);
#endif /* Not def: HAL_H */
