CFLAGS=
CC=gcc

OUTDIR=bin
OUTNAME=$(OUTDIR)/syslog
FILES=src/main.c

clean: $(OUTDIR)
	rm -rf $(OUTDIR)

compile: $(FILES)
	mkdir -p $(OUTDIR)
	$(CC) -o $(OUTNAME) $(FILES) $(CFLAGS)

compile-debug: CFLAGS += -g
compile-debug: compile

run: compile $(OUTNAME)
	$(OUTNAME)

install:
	sudo cp -p $(OUTNAME) /bin/syslog

uninstall: /bin/syslog
	sudo rm /bin/syslog

.PHONY: clean compile compile-debug run install uninstall