CFLAGS=-Wall -Werror -Wpedantic
DEBUG_FLAGS=-g

.PHONY: all
all: build/game-of-life build/submission.zip

.PHONY: debug
debug: CFLAGS += $(DEBUG_FLAGS)
debug: build/game-of-life

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

build/submission.zip: *.c *.h makefile *.md examples/*
	mkdir -p build
	zip -r $@ $^
