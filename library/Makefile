# Makefile

LIB = library.a
SRCS := $(wildcard *.c)
OBJS = $(subst .c,.o,$(SRCS))

CC=avr-gcc
TARGET=atmega168p
CLOCK=20000000

CFLAGS=-W -Wall -mmcu=$(TARGET) -Os -DF_CPU=$(CLOCK)

.SUFFIXES: .c .o

all: library.a

library.a: $(OBJS)
	avr-ar cr $(LIB) $(OBJS)
	avr-ranlib $(LIB)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<


.PHONY: clean
clean:
	rm -f $(OBJS) $(LIB)


basic_io.o: basic_io.h library.h
delay.o: delay.h library.h
init.o: init.h library.h
interrupt.o: interrupt.h library.h
libserial.o: libserial.h library.h
