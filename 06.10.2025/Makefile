BUILDDIR=build

CFLAGS=-Wall -pedantic -Wextra
CC=gcc

all: $(BUILDDIR) $(BUILDDIR)/sortedList_exercise.out

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/sortedList.o: sortedList.c sortedList.h
	$(CC) $(CFLAGS) -c sortedList.c -o $@

$(BUILDDIR)/sortedList_exercise.out: sortedList_exercise.c $(BUILDDIR)/sortedList.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILDDIR)

.PHONY: clean all