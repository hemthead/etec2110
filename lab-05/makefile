CFLAGS=-Wall -Werror -Wpedantic

.PHONY: all
all: build/game-of-life build/submission.zip

build/game-of-life: build/game_of_life.o build/main.o
	mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: %.c *.h
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	-rm -rf build

.PHONY: run
run: build/game-of-life
	./build/game-of-life

build/submission.zip: *.c *.h makefile *.gol *.md
	mkdir -p build
	zip -r $@ $^
