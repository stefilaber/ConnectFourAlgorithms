#include "MockAlgo.h"
#include <random>

int MockAlgo::choosePosition(const Board& board, int depth) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 6);
    while (true) {
        int col = dis(gen);
        if (board.getBoardElement(5, col) == ' ') {
            return col;
        }
    }
    return -1;
}
