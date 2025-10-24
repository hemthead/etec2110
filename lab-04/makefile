CFLAGS=-Wall -Werror -Wpedantic

.PHONY: all
all: build/program1 build/program2 build/submission.zip

build/%: %.c
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	-rm -rf build

build/submission.zip: *.c makefile
	mkdir -p build
	zip -r $@ $^
