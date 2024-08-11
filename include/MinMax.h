#ifndef MINMAX_H
#define MINMAX_H

#include "Algorithm.h"

class MinMax : public Algorithm {
private:
    int evaluate(const Board& board, char player);
    int evaluateWindow(const Board& board, int row, int col, int deltaRow, int deltaCol, char player);
    bool isTerminalNode(const Board& board);
    int minimax(Board board, int depth, bool isMaximizing, int alpha, int beta);

public:
    int choosePosition(const Board& board, int depth) override;
};

#endif // MINMAX_H
