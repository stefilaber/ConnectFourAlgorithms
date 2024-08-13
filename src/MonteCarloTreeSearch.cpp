#include "MonteCarloTreeSearch.h"
#include <fstream>
#include <limits>
#include <random>
#include <vector>

// Hashes the current board state into a string
std::string MonteCarloTreeSearch::hashBoard(const Board& board) {
    std::string boardHash;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            boardHash += board.getBoardElement(i, j);
        }
    }
    return boardHash;
}

// Main function to choose the best position using MCTS with caching
int MonteCarloTreeSearch::choosePosition(const Board& board, int depth) {
    std::string boardHash = hashBoard(board);

    // Check if the board state is already cached
    if (cache.find(boardHash) != cache.end()) {
        return cache[boardHash];
    }

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
                int alpha = std::numeric_limits<int>::min();
                int beta = std::numeric_limits<int>::max();
                if (simulate(simBoard, opponent, alpha, beta) == player) {
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

    // Cache the result before returning
    cache[boardHash] = bestMove;
    return bestMove;
}

// Simulates a random game and uses alpha-beta pruning to speed up the search
int MonteCarloTreeSearch::simulate(Board board, char player, int alpha, int beta) {
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

    int score;
    if (player == 'O') {  // Maximizing player
        score = std::numeric_limits<int>::min();
        for (int col = 0; col < 7; ++col) {
            if (board.getBoardElement(5, col) == ' ') {
                Board childBoard = board;
                childBoard.makeMove(col, player);
                int childScore = simulate(childBoard, getOpponent(player), alpha, beta);
                score = std::max(score, childScore);
                alpha = std::max(alpha, score);
                if (alpha >= beta) {
                    break;  // Beta cut-off
                }
            }
        }
    } else {  // Minimizing player
        score = std::numeric_limits<int>::max();
        for (int col = 0; col < 7; ++col) {
            if (board.getBoardElement(5, col) == ' ') {
                Board childBoard = board;
                childBoard.makeMove(col, player);
                int childScore = simulate(childBoard, getOpponent(player), alpha, beta);
                score = std::min(score, childScore);
                beta = std::min(beta, score);
                if (alpha >= beta) {
                    break;  // Alpha cut-off
                }
            }
        }
    }
    return score;
}

// Utility function to get the opponent's player symbol
char MonteCarloTreeSearch::getOpponent(char player) {
    return (player == 'X') ? 'O' : 'X';
}

// Generates a random valid move
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

// Checks if the current board state is terminal (win, loss, or draw)
bool MonteCarloTreeSearch::isTerminalNode(const Board& board) {
    return board.checkWin('X') || board.checkWin('O') || board.isBoardFull();
}

// Saves the cache to a file
void MonteCarloTreeSearch::saveCache() {
    std::ofstream outFile("cache.txt");
    for (const auto& entry : cache) {
        outFile << entry.first << " " << entry.second << std::endl;
    }
    outFile.close();
}

// Loads the cache from a file
void MonteCarloTreeSearch::loadCache() {
    std::ifstream inFile("cache.txt");
    std::string boardHash;
    int result;
    while (inFile >> boardHash >> result) {
        cache[boardHash] = result;
    }
    inFile.close();
}
