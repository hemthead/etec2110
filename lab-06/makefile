CFLAGS += -Wall -Werror -Wpedantic

program_LIBRARIES := sdl2

LDLIBS += $(shell pkg-config --libs $(program_LIBRARIES))
CFLAGS += $(shell pkg-config --cflags $(program_LIBRARIES))

.PHONY: all
all: build/main

build/%: %.c
	mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) $(TARGET_ARCH) $^ -o $@ $(LDLIBS)

.PHONY: clean
clean:
	-rm -rf build

build/submission.zip: *.c makefile
	mkdir -p build
	zip -r $@ $^
