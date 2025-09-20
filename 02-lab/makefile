CFLAGS=-Wall -Werror -Wpedantic -O2
CC=clang

build/main: main.c
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	-rm main

.PHONY: test
test: build/main main.py
	hyperfine './build/main' 'python ./main.py'

build/submission.zip: main.c main.py makefile results.md
	mkdir -p build
	zip -r $@ $^
