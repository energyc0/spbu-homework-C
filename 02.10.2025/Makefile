BUILDDIR:=build
SRC:=$(wildcard *.c)
SRC:=$(filter-out stack.c, $(SRC))
OUT:=$(patsubst %.c, $(BUILDDIR)/%.out, $(SRC))

CFLAGS=-Wall -pedantic -Wextra
CC=gcc

all: $(BUILDDIR) $(BUILDDIR)/stack.o $(OUT)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/stack.o: stack.h stack.c
	$(CC) $(CFLAGS) -c stack.c -o $(BUILDDIR)/stack.o

$(BUILDDIR)/%.out: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(BUILDDIR)/stack.o

clean:
	rm -rf $(BUILDDIR)

.PHONY: clean all
