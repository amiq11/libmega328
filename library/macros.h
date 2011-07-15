/*!
 \file macros.h
 \autor Shimazu Makoto <smk.hhs@gmail.com>

 \brief 便利なマクロ定義
*/


#ifndef __MACROS_H__
#define __MACROS_H__

/* デバッグ用printfを吐く */
#define DEBUG_PRINT


#define max(val1,val2) (((val1)>(val2))?(val1):(val2)) /* val1とval2の最大値 */
#define min(val1,val2) (((val1)<(val2))?(val1):(val2)) /* val1とval2の最小値 */
#define abs(val) (((val)>=0)?(val):(-val))             /* valの絶対値 */
#define sbi(byte,bit) ((byte)|=1<<(bit))               /* byteのうちbitビットを1にする */
#define cbi(byte,bit) ((byte)&=~(1<<(bit)))            /* byteのうちbitビットを0にする */

#endif
