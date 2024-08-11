#include "MonteCarloTreeSearch.h"
#include <random>
#include <vector>
#include <ctime>

int MonteCarloTreeSearch::choosePosition(const Board& board, int depth) {
    int bestMove = -1;
    double bestWinRatio = -1.0;

    char player = 'O'; // MCTS is always 'O' in this case
    char opponent = getOpponent(player);

    for (int col = 0; col < 7; ++col) {
        if (board.getBoardElement(5, col) == ' ') {
            Board simulatedBoard = board;
            simulatedBoard.makeMove(col, player);

            int wins = 0;
            int simulations = 1000 * depth;  // The depth controls the number of simulations

            for (int i = 0; i < simulations; ++i) {
                Board simBoard = simulatedBoard;
                if (simulate(simBoard, opponent) == player) {
                    wins++;
                }
            }

            double winRatio = static_cast<double>(wins) / simulations;

            if (winRatio > bestWinRatio) {
                bestWinRatio = winRatio;
                bestMove = col;
            }
        }
    }

    return bestMove;
}

int MonteCarloTreeSearch::simulate(Board board, char player) {
    while (!isTerminalNode(board)) {
        int move = randomMove(board);
        board.makeMove(move, player);
        player = getOpponent(player);
    }

    if (board.checkWin('O')) {
        return 'O';
    } else if (board.checkWin('X')) {
        return 'X';
    } else {
        return ' ';  // Draw
    }
}

char MonteCarloTreeSearch::getOpponent(char player) {
    return (player == 'X') ? 'O' : 'X';
}

int MonteCarloTreeSearch::randomMove(const Board& board) {
    std::vector<int> validMoves;
    for (int col = 0; col < 7; ++col) {
        if (board.getBoardElement(5, col) == ' ') {
            validMoves.push_back(col);
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, validMoves.size() - 1);
    return validMoves[dis(gen)];
}

bool MonteCarloTreeSearch::isTerminalNode(const Board& board) {
    return board.checkWin('X') || board.checkWin('O') || board.isBoardFull();
}
