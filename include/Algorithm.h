#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Board.h"

class Algorithm {
public:
    virtual int choosePosition(const Board& board, int depth) = 0;
};

#endif // ALGORITHM_H
