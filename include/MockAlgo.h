#ifndef MOCKALGO_H
#define MOCKALGO_H

#include "Algorithm.h"

class MockAlgo : public Algorithm {
public:
    int choosePosition(const Board& board, int depth) override;
};

#endif // MOCKALGO_H
