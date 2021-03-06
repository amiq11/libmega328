/* pwm.h */
#ifndef __PWM_H__
#define __PWM_H__


/* ------------------
   IDの定義
   これをつかってIDを設定してください。
 ------------------*/

#define PWM_PD6 (0)
#define PWM_PD5 (1)
#define PWM_PB1 (2)
#define PWM_PB2 (3)
#define PWM_PB3 (4)
#define PWM_PD3 (5)


/* ------------------
   プロトタイプ宣言
------------------ */

void init_pwm(int id);
void set_pwm(int id, uint8_t duty);
#endif /* Not def: __PWM_H__ */
