#ifndef MONTECARLOTREESEARCH_H
#define MONTECARLOTREESEARCH_H

#include "Algorithm.h"
#include "Board.h"
#include <unordered_map>
#include <string>

class MonteCarloTreeSearch : public Algorithm {
public:
    int choosePosition(const Board& board, int depth) override;

    // Functions to save and load cache
    void saveCache();
    void loadCache();

private:
    std::unordered_map<std::string, int> cache;

    int simulate(Board board, char player, int alpha, int beta);
    char getOpponent(char player);
    int randomMove(const Board& board);
    bool isTerminalNode(const Board& board);
    std::string hashBoard(const Board& board);
};

#endif // MONTECARLOTREESEARCH_H
