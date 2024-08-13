#ifndef CONNECTFOURGAME_H
#define CONNECTFOURGAME_H

#include "HumanPlayer.h"
#include "MinMax.h"
#include "MonteCarloTreeSearch.h"
#include "Board.h"

class ConnectFourGame {
public:
    ConnectFourGame(int depth);
    void playMultipleGames(int numGames);

private:
    Board board;
    int depth;  // Depth for the MinMax and MCTS algorithms

    int randomMove();  // Function to generate a random valid move
};

#endif // CONNECTFOURGAME_H
