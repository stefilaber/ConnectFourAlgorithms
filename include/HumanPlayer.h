#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Algorithm.h"

class HumanPlayer : public Algorithm {
public:
    int choosePosition(const Board& board, int depth) override;
};

#endif // HUMANPLAYER_H
