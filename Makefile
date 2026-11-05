CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

clean:
	rm -f main