DEBUG_FLAGS += -g
CFLAGS += -Wall -Werror -Wpedantic -lm

program_LIBRARIES := sdl3

LDLIBS += $(shell pkg-config --libs $(program_LIBRARIES))
CFLAGS += $(shell pkg-config --cflags $(program_LIBRARIES))

.PHONY: all
all: build/program1 build/program2 build/submission.zip

build/program1: build/main.o build/common.o build/blockhead_list.o
	mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) $(TARGET_ARCH) $^ -o $@ $(LDLIBS)

build/program2: build/main.o build/common.o build/blockhead_array.o
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
debug: clean all

build/submission.zip: *.c *.h makefile
	mkdir -p build
	7z a $@ $^
