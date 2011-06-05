/* hardware.h */
/* ピンアサイン等 */

#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#ifndef POS
#define POS 0
#define NEG 1
#endif

/* スイッチ設定 */
/* DIR：POS,NEG */
/* DIRがNEGならhiで0 */
#define SW0_PIN PD2
#define SW0_REG PIND
#define SW0_DDR DDRD
#define SW0_PORT PORTD
#define SW0_DIR NEG


/* LED設定 */
/* LEDのセットの指定 */
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

/* 各LEDのPWMのID */
#define LED0_PWM PWM_PD6
#define LED1_PWM PWM_PD5
#define LED2_PWM PWM_PB3
#define LED3_PWM PWM_PD3



#endif /* Not def: __HARDWARE_H__ */
