CFLAGS=-Wall -Werror -Wpedantic

.PHONY: all
all: build/program1 build/program2 build/program3 build/submission.zip

build/%: %.c
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	-rm $(executables) submission.zip

.PHONY: run
run: build/program1 build/program2 build/program3
	./build/program1
	@echo
	./build/program2
	@echo
	./build/program3

build/submission.zip: *.c makefile
	zip -r $@ $^
