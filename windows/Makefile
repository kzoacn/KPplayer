
CC=gcc
override CFLAGS+=-Wall -O3  -static
override LDFLAGS+= -lm

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
