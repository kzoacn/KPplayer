
CC=gcc
override CFLAGS+=-Wall -O3 $(shell pkg-config --cflags fftw3 glib-2.0)
override LDFLAGS+=$(shell pkg-config --libs fftw3 glib-2.0) -lm

.PHONY: all clean

all:  kpenc kpdec
 

kpenc: kpenc.o kpmain.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
kpdec: kpdec.o kpmain.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $^

kpenc.c : kpcommon.h
kpdec.c : kpcommon.h 

clean:
	rm -f kpenc kpdec kpmain.o kpenc.o kpdec.o kpenc.o kpdec.o kpenc kpdec
