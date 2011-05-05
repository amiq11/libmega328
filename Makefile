# Makefile
objs = main.o
LIB_PATH = ./library
LIB = $(LIB_PATH)/library.a
API_PATH = ./api
API = $(API_PATH)/api.a

CC=avr-gcc
WP=avrdude
WRITER=usbasp

DEVICE=atmega88p
CLOCK=20000000
CFLAGS=-W -Wall -mmcu=$(DEVICE) -Os -DF_CPU=$(CLOCK) -I$(LIB_PATH)


.SUFFIXES: .c .o


# make だけでライブラリも更新
# all: lib main.hex api

# make だけだとカレントフォルダのみ
all: main.hex



.PHONY: full
# full: lib main.hex
full: api lib main.hex

.PHONY: lib
lib:
	(cd $(LIB_PATH); make)

.PHONY: api
api:
	(cd $(API_PATH); make)

main.hex: main.elf
	avr-objcopy $< -O ihex $@

main.elf: $(objs) $(LIB) $(API)
	$(CC) $(CFLAGS) -o $@ $(objs) $(LIB)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: full_clean
full_clean: clean
	(cd $(LIB_PATH); make clean)
	(cd $(API_PATH); make clean)

.PHONY: clean
clean:
	rm -f $(objs) main.elf main.hex

.PHONY: write
write:
	make
	$(WP) -c $(WRITER) -p $(DEVICE) -U flash:w:main.hex

.PHONY: t
t:
	$(WP) -c $(WRITER) -p $(DEVICE) -t -B50

