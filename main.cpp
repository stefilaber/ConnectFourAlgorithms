#include "ConnectFourGame.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <depth>" << std::endl;
        return 1;
    }

    int depth = std::atoi(argv[1]);
    if (depth <= 0) {
        std::cerr << "Depth must be a positive integer." << std::endl;
        return 1;
    }

    ConnectFourGame game(depth);
    game.playGame();

    return 0;
}
