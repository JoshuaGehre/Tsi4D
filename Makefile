CPP = g++
CFLAGS = -Wall -Wextra -Wno-implicit-fallthrough --std=c++17 -g
BUILDFLAGS = ${CFLAGS} -O3

OBJECTS = $(shell find src -type f -name "*.cpp" | sed 's/^src/build/g; s/.cpp$$/.o/g')

.PHONY: all clean format

all: $(OBJECTS)
	@echo "Done!"

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(BUILDFLAGS) -o $@ $<

clean:
	rm -rf build

format:
	clang-format-10 -style=file -i $(shell find src/ -type f -regextype posix-egrep -regex ".*\.(h|cpp)$$")
