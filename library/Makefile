# Makefile

LIB = library.a
SRCS := $(wildcard *.c)
OBJS = $(subst .c,.o,$(SRCS))

CC=avr-gcc
TARGET=atmega88p
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
