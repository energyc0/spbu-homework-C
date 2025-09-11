SRC=$(wildcard *.c)
OUT=$(patsubst %.c, %.out, $(SRC))

CFLAGS=-Wall -pedantic -Wextra
CC=gcc

all: $(OUT)

%.out: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.out

.PHONY: clean
