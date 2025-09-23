.PHONY: all
all: build/submission.pdf

build/%.pdf: %.typ
	mkdir -p build
	typst c $< $@

.PHONY: clean
clean:
	-rm -rf build
