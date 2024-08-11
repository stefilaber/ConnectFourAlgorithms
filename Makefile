# Default target
default: all

# Build all targets
all: clean build

# Clean up the previous build
clean:
	rm -f connectFour *.o

# Compile and link the project
build: main.o ConnectFourGame.o Board.o HumanPlayer.o MockAlgo.o MinMax.o MonteCarloTreeSearch.o
	g++ main.o ConnectFourGame.o Board.o HumanPlayer.o MockAlgo.o MinMax.o MonteCarloTreeSearch.o -o connectFour -std=c++20 -Wall

# Compile main.cpp
main.o: main.cpp include/ConnectFourGame.h
	g++ -Iinclude -c main.cpp -o main.o -std=c++20 -Wall

# Compile ConnectFourGame.cpp
ConnectFourGame.o: src/ConnectFourGame.cpp include/ConnectFourGame.h include/Board.h include/HumanPlayer.h include/MinMax.h include/MonteCarloTreeSearch.h
	g++ -Iinclude -c src/ConnectFourGame.cpp -o ConnectFourGame.o -std=c++20 -Wall

# Compile Board.cpp
Board.o: src/Board.cpp include/Board.h
	g++ -Iinclude -c src/Board.cpp -o Board.o -std=c++20 -Wall

# Compile HumanPlayer.cpp
HumanPlayer.o: src/HumanPlayer.cpp include/HumanPlayer.h include/Algorithm.h
	g++ -Iinclude -c src/HumanPlayer.cpp -o HumanPlayer.o -std=c++20 -Wall

# Compile MockAlgo.cpp
MockAlgo.o: src/MockAlgo.cpp include/MockAlgo.h include/Algorithm.h
	g++ -Iinclude -c src/MockAlgo.cpp -o MockAlgo.o -std=c++20 -Wall

# Compile MinMax.cpp
MinMax.o: src/MinMax.cpp include/MinMax.h include/Algorithm.h
	g++ -Iinclude -c src/MinMax.cpp -o MinMax.o -std=c++20 -Wall

# Compile MonteCarloTreeSearch.cpp
MonteCarloTreeSearch.o: src/MonteCarloTreeSearch.cpp include/MonteCarloTreeSearch.h include/Algorithm.h
	g++ -Iinclude -c src/MonteCarloTreeSearch.cpp -o MonteCarloTreeSearch.o -std=c++20 -Wall