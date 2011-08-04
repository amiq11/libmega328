# Makefile

API = api.a
SRCS := $(wildcard *.c)
OBJS = $(subst .c,.o,$(SRCS))

LIB_PATH = ../library
LIB = $(LIB_PATH)/library.a


CC=avr-gcc
TARGET=atmega328p
CLOCK=20000000

CFLAGS=-W -Wall -mmcu=$(TARGET) -Os -DF_CPU=$(CLOCK) -I$(LIB_PATH) 

.SUFFIXES: .c .o .h

all: api.a

api.a: $(OBJS) $(LIB)
	avr-ar cr $(API) $(OBJS)
	avr-ranlib $(API)

$(LIB):
	(cd $(LIB_PATH); make)


.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.h.o:
	$(CC) $(CFLAGS) -c -o $@ $<



.PHONY: clean
clean:
	rm -f $(OBJS) $(API)

# dynamic_led.o: dynamic_led.h api.h 