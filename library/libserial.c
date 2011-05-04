/*
  libserial.c
  シリアル通信関連

  機能：printfがつかえます。また、シリアルでデータを受信できます。できません。

  使用方法：uart_init(baud)を実行してください。

*/




#include <avr/interrupt.h>  //受信割り込み
#include "library.h"

#ifndef UNUSE_PRINTF
#include <stdio.h>      //printf
#endif /* Not def: UNUSE_PRINTF */


/* 送信・受信バッファ定義 */
volatile buf_t txbuf;
volatile buf_t rxbuf;



//ISR(USART_RX_vect)
//機能：受信時割り込み。
//
ISR(USART_RX_vect){
    rxbuf.data[rxbuf.in] = UDR0;
    rxbuf.in++;
}

//ISR(USART_UDRE_vect)
//機能：送信終了割り込み
//      txbuf.data[txbuf.sendaddr]を送信
//      txbuf.data[txbuf.sendaddr]=='y'だったら送信終了

ISR(USART_UDRE_vect){
    UDR0 = txbuf.data[txbuf.out];
    txbuf.out++;
    if(txbuf.out==txbuf.in){
        UCSR0B &= ~_BV(UDRIE0); //送信割り込み禁止
    }
}


//send_char(文字)
//機能：一文字送信
int send_char(char data)
{
    if(data == '\n')
        send_char('\r');
    txbuf.data[txbuf.in]=data;
    txbuf.in++;
    UCSR0B |= _BV(UDRIE0);   /* 送信割り込み許可 */
    return 0;
}



/* ピンの初期化。ハードウェア固有。 */
void uart_port_init(void)
{
    sbi(DDRD,PD1);              /* TxD */
    cbi(DDRD,PD0);              /* RxD */
}

//uart_init(baud)
//機能：初期化します。始めに実行してください。
//
void uart_init(const unsigned int baud){
    uart_port_init();
    
    UBRR0H = (baud >> 8);
    UBRR0L = (char)(baud & 0xFF);
    UCSR0A = _BV(U2X0);
    UCSR0B = _BV(TXEN0)|_BV(RXCIE0)|_BV(RXEN0);  /* 送受信許可 受信割り込み有効 */
    UCSR0C = _BV(UCSZ01)|_BV(UCSZ00);    /* フレーム形式設定(8ヒ゛ット) */
    
#ifndef UNUSE_PRINTF
    static FILE mystdout = FDEV_SETUP_STREAM(send_char, NULL, _FDEV_SETUP_WRITE);
    stdout = &mystdout;                 //※stdoutをオーバーライドできる→printfで望む出力が可能になる
#endif /* Not def: UNUSE_PRINTF */

    /* 送信バッファ初期化 */
    int i;
    for(i=0;i<MAX_BUF_SIZE;i++){
        txbuf.data[i]='\0';
    }
    txbuf.out=0;
    txbuf.in=0;

    /* 受信バッファ初期化 */
    for(i=0;i<MAX_BUF_SIZE;i++){
        rxbuf.data[i]='\0';
    }
    rxbuf.out=0;
    rxbuf.in=0;


    /* 割り込み許可 */
    sei();
}


/* r_getc()
   一文字受信
   受信するまでまつ
*/

uint8_t r_getc(void)
{
    while(rxbuf.in==rxbuf.out);
    uint8_t c = rxbuf.data[rxbuf.out];
    rxbuf.out++;
    return c;
}


/* r_getc_noblock()
   一文字受信
   受信してなければ-1
 */
int r_getc_noblock(void)
{
    if(rxbuf.in==rxbuf.out)
        return -1;
    else {
        uint8_t c = rxbuf.data[rxbuf.out];
        rxbuf.out++;
        return c;
    }
}



int16_t char_to_int(uint8_t c){
    int16_t buf = c-'0';
    if(buf<0 || buf>9) return -1;
    else return buf;
}



/* メモリ使用量を減らしたい場合 */
#ifdef UNUSE_PRINTF


// １バイトのバイナリデータをＡＳＣＩＩ文字化したヘキサデータにして返す
uint16_t bin_to_hex(uint8_t bin){
    uint16_t i;
    i = (uint8_t)(bin >> 4);
    if( i > 9)
        i += ('A'-10);
    else
        i += '0';
    i <<= 8;
    bin &= 0x0F;
    if( bin > 9)
        bin += ('A'-10);
    else
        bin += '0';
    return( i += (uint16_t)bin);
}

void print_hex16(uint16_t val){
    send_char((bin_to_hex(val>>8&0xFF)&0xFF00)>>8);
    send_char(bin_to_hex(val>>8&0xFF)&0x00FF);
    send_char((bin_to_hex(val&0xFF)&0xFF00)>>8);
    send_char(bin_to_hex(val&0xFF)&0x00FF);
}


void print_hex8(uint8_t val){
    send_char((bin_to_hex(val&0xFF)&0xFF00)>>8);
    send_char(bin_to_hex(val&0xFF)&0x00FF);
}

void send_ret(void)
{
    send_char('\r');
    send_char('\n');
}

void send_tab(void){
    send_char('\t');
}

#endif
