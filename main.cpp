#include "ConnectFourGame.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <depth> <num_games>" << std::endl;
        return 1;
    }

    int depth = std::atoi(argv[1]);
    int numGames = std::atoi(argv[2]);

    if (depth <= 0) {
        std::cerr << "Depth must be a positive integer." << std::endl;
        return 1;
    }

    if (numGames <= 0) {
        std::cerr << "Number of games must be a positive integer." << std::endl;
        return 1;
    }

    ConnectFourGame game(depth);
    game.playMultipleGames(numGames);  // Play the specified number of games

    return 0;
}
