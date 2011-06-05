/*!
 \file macros.h
 \autor Shimazu Makoto <smk.hhs@gmail.com>

 \brief 便利なマクロ定義
*/


#ifndef __MACROS_H__
#define __MACROS_H__

/* デバッグ用printfを吐く */
#define DEBUG_PRINT

#define max(val1,val2) (((val1)>(val2))?(val1):(val2))
#define min(val1,val2) (((val1)<(val2))?(val1):(val2))
#define abs(val) (((val)>=0)?(val):(-val))
#define sbi(byte,bit) ((byte)|=1<<(bit))
#define cbi(byte,bit) ((byte)&=~(1<<(bit)))

#endif
