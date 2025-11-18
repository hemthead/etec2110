DEBUG_FLAGS += -g
CFLAGS += -Wall -Werror -Wpedantic

program_LIBRARIES := sdl2

LDLIBS += $(shell pkg-config --libs $(program_LIBRARIES))
CFLAGS += $(shell pkg-config --cflags $(program_LIBRARIES))

.PHONY: all
all: build/game-of-life build/submission.zip

build/game-of-life: build/main.o build/game_of_life.o
	mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) $(TARGET_ARCH) $^ -o $@ $(LDLIBS)

build/%.o: %.c *.h
	mkdir -p build
	$(CC) $(CFLAGS) $(TARGET_ARCH) $< -o $@  -c

.PHONY: clean
clean:
	-rm -rf build

.PHONY: run
run: build/game-of-life
	./build/game-of-life

.PHONY: debug
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean build/game-of-life

build/submission.zip: *.c makefile
	mkdir -p build
	zip -r $@ $^
