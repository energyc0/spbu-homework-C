BUILDDIR=build
SRC=$(wildcard *.c)
OUT=$(patsubst %.c, $(BUILDDIR)/%.out, $(SRC))

CFLAGS=-Wall -pedantic -Wextra
CC=gcc

all: $(BUILDDIR) $(OUT)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.out: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILDDIR)

.PHONY: clean all
