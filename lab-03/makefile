CFLAGS=-Wall -Werror -Wpedantic -O2
CC=clang

.PHONY: all
all: build/main build/submission.zip

build/main: main.c
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	-rm main

.PHONY: run
run: build/main
	./build/main

build/submission.zip: main.c makefile
	mkdir -p build
	zip -r $@ $^
