/* hardware.h */

/* ピンアサイン等 */
#ifndef __HARDWARE_H__
#define __HARDWARE_H__


#define RED_sel_PIN    PD7
#define RED_sel_PORT   PORTD
#define GREEN_sel_PIN  PD4
#define GREEN_sel_PORT PORTD
#define COLOR_sel_PIN  PB4
#define COLOR_sel_PORT PORTB

#define LED0 (0)
#define LED1 (1)
#define LED2 (2)
#define LED3 (3)

#define LED(id) LED##id

#define LED0_PWM PWM_PD6
#define LED1_PWM PWM_PD5
#define LED2_PWM PWM_PB3
#define LED3_PWM PWM_PD3



#endif /* Not def: __HARDWARE_H__ */
