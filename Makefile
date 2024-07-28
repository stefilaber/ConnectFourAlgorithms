default: all

all: clean build

clean:
	rm -f connectFour

build: main.cpp
	g++ main.cpp -o connectFour -std=c++20 -Wall