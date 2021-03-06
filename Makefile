# Makefile
objs = main.o control.o

# m168p
# EFUSE=0x01
# HFUSE=0xdc
# LFUSE=0xc7

# m328p
EFUSE=0x04
HFUSE=0xd9
LFUSE=0xc7


LIB_PATH = ./library
LIB = $(LIB_PATH)/library.a
API_PATH = ./api
API = $(API_PATH)/api.a

CC=avr-gcc
# WP=avrdude
# WRITER=usbasp
WP=hidspx
WRITER=hidaspx

DEVICE=atmega328p
CLOCK=20000000
# CFLAGS=-W -Wall -mmcu=$(DEVICE) -Os -std=gnu99 -DF_CPU=$(CLOCK) -L$(LIB_PATH) -L$(API_PATH) -I$(LIB_PATH) -I$(API_PATH) -g
CFLAGS=-W -Wall -mmcu=$(DEVICE) -Os -std=gnu99 -DF_CPU=$(CLOCK) -I$(LIB_PATH) -I$(API_PATH) -g
# CFLAGS=-W -Wall -mmcu=$(DEVICE) -Os -DF_CPU=$(CLOCK)
# WFLAGS=-c $(WRITER) -p $(DEVICE) -U flash:w:main.hex
WFLAGS=main.hex -d0

.SUFFIXES: .c .o


# make だけでライブラリも更新
# all: lib main.hex api

# make だけだとカレントフォルダのみ
all: main.hex



.PHONY: full
# full: lib main.hex
full: api lib main.hex
# full: main.hex

.PHONY: lib
lib:
	(cd $(LIB_PATH); make)

.PHONY: api
api:
	(cd $(API_PATH); make)

main.hex: main.elf
	avr-objcopy $< -O ihex $@
	avr-size $@

main.elf: $(objs) $(LIB) $(API)
	$(CC) $(CFLAGS) -o $@ $(objs) $(API) $(LIB)

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
	$(WP) $(WFLAGS)

.PHONY: t
t:
	$(WP) -c $(WRITER) -p $(DEVICE) -t -B50

.PHONY: fusewrite
fusewrite:
#	# $(WP) -c $(WRITER) -p $(DEVICE) -U efuse:w:$(EFUSE):m -U hfuse:w:$(HFUSE):m -U lfuse:w:$(LFUSE):m -B50
	$(WP) -fX$(EFUSE) -fH$(HFUSE) -fL$(LFUSE)
