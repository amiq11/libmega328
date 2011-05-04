#ifndef __UART_CLK_H__
#define __UART_CLK_H__

#if (F_CPU==14745600UL)
// SYSCLOCK 14.7456MHz
typedef enum {
  br2400   = 767,
  br4800   = 383,
  br9600   = 191,
  br14400  = 127,
  br19200  = 95,
  br28800  = 63,
  br38400  = 47,
  br57600  = 31,
  br115200 = 15,
  br230400 = 7,
  br460800 = 3,
  br921600 = 1,
} TBaudRate;
#elif (F_CPU==16000000UL)
// SYSCLOCK 16MHz
typedef enum {
  br2400   = 832,
  br4800   = 416,
  br9600   = 207,
  br14400  = 138,
  br19200  = 103,
  br28800  = 68,
  br38400  = 51,
  br57600  = 34,
  br115200 = 16,
  br200k   = 9,
  br250k   = 7,
  br400k   = 4,
  br500k   = 3,
  br1M     = 1,
} TBaudRate;
#elif (F_CPU==20000000UL)
// SYSCLOCK 20MHz
typedef enum {
  br2400   = 1041,
  br4800   = 520,
  br9600   = 259,
  br14400  = 173,
  br19200  = 129,
  br28800  = 86,
  br38400  = 64,
  br57600  = 42,
  br76800 = 32,
  br115200   = 21,
  br230400   = 10,
  br250k   = 9,
  br500k   = 4,
} TBaudRate;
#else
#error Given F_CPU not supported.
#endif

#endif
