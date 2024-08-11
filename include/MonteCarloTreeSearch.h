#ifndef MONTECARLOTREESEARCH_H
#define MONTECARLOTREESEARCH_H

#include "Algorithm.h"
#include "Board.h"

class MonteCarloTreeSearch : public Algorithm {
public:
    int choosePosition(const Board& board, int depth) override;

private:
    int simulate(Board board, char player);
    char getOpponent(char player);
    int randomMove(const Board& board);
    bool isTerminalNode(const Board& board);
};

#endif // MONTECARLOTREESEARCH_H
