CFLAGS=-Wall -Werror -Wpedantic

.PHONY: all
all: build/program1 build/program2 build/program3 build/submission.zip

build/%: %.c
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	-rm $(executables) submission.zip

build/submission.zip: *.c makefile
	zip -r $@ $^
