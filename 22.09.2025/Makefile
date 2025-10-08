BUILDDIR=build

CFLAGS=-Wall -pedantic -Wextra -O3
CC=gcc

all: $(BUILDDIR) $(BUILDDIR)/merge_sort.out

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/merge_sort.out: $(BUILDDIR)/merge_sort.o $(BUILDDIR)/sorter.o
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/merge_sort.o: merge_sort.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

$(BUILDDIR)/sorter.o: $(BUILDDIR)/sorter.S
	$(CC) $(CFLAGS) -c $(BUILDDIR)/sorter.S -o $@

$(BUILDDIR)/sorter.S: sorter.h sorter.c
	$(CC) $(CFLAGS) -S sorter.c -o $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: clean all