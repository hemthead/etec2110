CFLAGS=-Wall -Werror -Wpedantic

.PHONY: all
all: build/stringReverse build/cryptogramify build/rhombus build/rhombus2

build/%: %.c
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	-rm -rf build
