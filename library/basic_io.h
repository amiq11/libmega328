#ifndef __BASIC_IO_H__
#define __BASIC_IO_H__

#include "library.h"

/* 初期化 */
#define pin_out_init(ddr,pin) ((ddr) |= 1<<(pin))
#define pin_in_init(ddr,pin) ((ddr) &= ~(1<<(pin)))

/* 出力 */
#define set_pin_hi(port,pin) ((port) |= 1<<(pin))
#define set_pin_low(port,pin) ((port) &= ~(1<<(pin)))
#define set_pin_toggle(port,pin) ((port) ^= 1<<(pin))

/* 入力 */
#define read_pin(port,pin) (((port)>>(pin))&0x01)


#endif /* Not def: __BASIC_IO_H__ */
