BUILDDIR:=build
SRC:=$(wildcard *.c)
SRC:=$(filter-out stack.c, $(SRC))
OUT:=$(BUILDDIR)/stack.o $(BUILDDIR)/polishNotation.out

CFLAGS=-Wall -pedantic -Wextra
CC=gcc

all: $(BUILDDIR) $(BUILDDIR)/stack.o $(OUT)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/stack.o: stack.h stack.c
	$(CC) $(CFLAGS) -c stack.c -o $(BUILDDIR)/stack.o

$(BUILDDIR)/polishNotation.out: polishNotation.c polishNotationIO.c polishNotationIO.h $(BUILDDIR)/stack.o
	$(CC) $(CFLAGS) -o $@ polishNotation.c polishNotationIO.c $(BUILDDIR)/stack.o

clean:
	rm -rf $(BUILDDIR)

.PHONY: clean all
