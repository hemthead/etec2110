CFLAGS=-Wall -Werror -Wpedantic -O2
CC=clang

main: main.c

.PHONY: clean test
clean:
	-rm main

test: main main.py
	hyperfine './main' 'python ./main.py'

submission.zip: main.c main.py makefile
	zip -r submission.zip main.c main.py results.md
