# Name: John Reed
# Class.Section: etec2110.01 Systems Programming
# Lab_Part: 8 Linked Lists & Dynamic Memory Allocation in C

DEBUG_FLAGS += -g
CFLAGS += -Wall -Werror -Wpedantic -lm

program_LIBRARIES := sdl3

LDLIBS += $(shell pkg-config --libs $(program_LIBRARIES))
CFLAGS += $(shell pkg-config --cflags $(program_LIBRARIES))

.PHONY: all
all: build/blockheads-linked-list build/blockheads-dynamic-array build/submission.zip

build/blockheads-linked-list: build/main.o build/common.o build/blockhead_list.o
	mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) $(TARGET_ARCH) $^ -o $@ $(LDLIBS)

build/blockheads-dynamic-array: build/main.o build/common.o build/blockhead_array.o
	mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) $(TARGET_ARCH) $^ -o $@ $(LDLIBS)

build/%.o: %.c *.h
	mkdir -p build
	$(CC) $(CFLAGS) $(TARGET_ARCH) $< -o $@  -c

.PHONY: clean
clean:
	-rm -rf build

.PHONY: debug
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

build/submission.zip: *.c *.h makefile
	mkdir -p build
	7z a $@ $^
