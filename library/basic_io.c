/* basic_io.c */

#include "library.h"

void init_sw(void){
    pin_in_init(SW0_DDR,SW0_PIN);
    set_pin_hi(SW0_PORT,SW0_PIN);
}
    

/* スイッチを読み取る */
/* hardware.hにあるPOS,NEGの設定により0,1が反転する */
uint8_t get_sw(uint8_t val){
    switch(val){
    case 0:
#if SW0_DIR==POS
        return (read_pin(SW0_REG,SW0_PIN)==0?0:1);
#else
        return (read_pin(SW0_REG,SW0_PIN)==0?1:0);
#endif
    }
    return 0xFF;
}



