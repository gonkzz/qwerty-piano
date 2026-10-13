CXX      ?= g++
CXXFLAGS := -std=c++23 -Wall -Wextra -O2
LDLIBS   := -lraylib

keyboard: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)

run: keyboard
	./keyboard

clean:
	rm -f keyboard

.PHONY: run clean
