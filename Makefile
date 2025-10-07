HOMETASKS:=$(shell find -maxdepth 1 -type d ! -name .git ! -name .)

all:
	for task in $(HOMETASKS); do \
		make -C $$task ; \
	done

clean:
		for task in $(HOMETASKS); do \
		make -C $$task clean; \
	done

.PHONY: clean all
