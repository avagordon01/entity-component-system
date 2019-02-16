CXX := clang++
CXXFLAGS = -O3 -std=c++17 -MMD -MP \
	-Werror -Wall -Wextra -Wpedantic \
	-Wno-unused-function -Wno-unused-parameter

all: out/example

out:
	@mkdir -p out

sources := $(wildcard src/*.cc)
objects := $(subst src,out,$(sources:.cc=.o))
depends := $(objects:.o=.d)

out/%.o: src/%.cc | out
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

out/example: out/example.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -rf out

.PHONY: all clean out

-include $(depends)
