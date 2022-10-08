CFLAGS=-Wall -Wextra -Wpedantic -std=gnu17 -O3
CC=gcc

OUTDIR=bin
OUTNAME=$(OUTDIR)/syslog
FILES=$(wildcard src/*.c) $(wildcard src/components/*.c)
OBJ=$(FILES:.c=.o)

.PHONY: all clean install uninstall

all: dir compile

dir:
	mkdir -p $(OUTDIR)

compile: $(OBJ)
	$(CC) -o $(OUTNAME) $^

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -Iheaders/

clean: $(OUTDIR) $(OBJ)
	rm -rf $(OUTDIR) $(OBJ)

install:
	sudo cp -p $(OUTNAME) /bin/syslog

uninstall: /bin/syslog
	sudo rm /bin/syslog