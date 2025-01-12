.PHONY: all
all: format test build run

.PHONY: format
format:
	clang-format src/* include/* -i

.PHONY: build
build:
	mkdir -p build
	cd build && \
	cmake .. && \
	make
	cp ./src/score ./build

.PHONY: debug
debug:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make
	cp ./src/score ./build


.PHONY: run
run:
	build/SnakeGame 


.PHONY: clean
clean:
	rm -rf build