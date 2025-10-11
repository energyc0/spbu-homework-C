BUILDDIR=build

CFLAGS=-Wall -pedantic -Wextra
CC=gcc

all: $(BUILDDIR) $(BUILDDIR)/sortedList_exercise.out $(BUILDDIR)/recursiveList_exercise.out

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/sortedList.o: sortedList.c sortedList.h
	$(CC) $(CFLAGS) -c sortedList.c -o $@

$(BUILDDIR)/sortedList_exercise.out: sortedList_exercise.c $(BUILDDIR)/sortedList.o
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)/recursiveList.o: recursiveList.c recursiveList.h
	$(CC) $(CFLAGS) -c recursiveList.c -o $@

$(BUILDDIR)/recursiveList_exercise.out: recursiveList_exercise.c $(BUILDDIR)/recursiveList.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILDDIR)

.PHONY: clean all