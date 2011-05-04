#ifndef __LIB_SERIAL_H__
#define __LIB_SERIAL_H__

/* -------------
   各種設定
------------- */

/* printfを使いたくないときはこちらを定義 */
/* #define UNUSE_PRINTF */

/* バッファサイズ定義 */
#define MAX_BUF_SIZE 256


/* -------------
   プロトタイプ宣言
------------- */

void uart_init(const unsigned int baud);
int send_char(char data);

uint8_t r_getc(void);
int r_getc_noblock(void);

int16_t char_to_int(uint8_t c);

#ifdef UNUSE_PRINTF
uint16_t bin_to_hex(uint8_t bin);
void print_hex16(uint16_t val);
void print_hex8(uint8_t val);
void send_ret(void);
void send_tab(void);
#endif


/* -------------
   バッファの定義
------------- */

typedef struct _buf{
    char data[MAX_BUF_SIZE];
    uint8_t out;
    uint8_t in;
}buf_t;


#endif
