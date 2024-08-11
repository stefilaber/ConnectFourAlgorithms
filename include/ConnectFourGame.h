#ifndef CONNECTFOURGAME_H
#define CONNECTFOURGAME_H

#include "HumanPlayer.h"
#include "MinMax.h"
#include "MonteCarloTreeSearch.h"
#include "Board.h"

class ConnectFourGame {
public:
    ConnectFourGame(int depth);
    void playGame();

private:
    Board board;
    int depth;  // Depth for the MinMax and MCTS algorithms
};

#endif // CONNECTFOURGAME_H
