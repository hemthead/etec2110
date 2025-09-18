CFLAGS=-Wall -Werror -Wpedantic

executables=program1 program2 program3

all: $(executables)

.PHONY: clean
clean:
	-rm $(executables) submission.zip

submission.zip: *.c makefile
	zip -r submission.zip *.c makefile
