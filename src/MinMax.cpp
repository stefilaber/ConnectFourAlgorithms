#include "MinMax.h"
#include <limits>
#include <algorithm>

int MinMax::evaluate(const Board& board, char player) {
    int score = 0;

    // Evaluate center column preference
    int centerCount = 0;
    for (int i = 0; i < 6; i++) {
        if (board.getBoardElement(i, 3) == player) {
            centerCount++;
        }
    }
    score += centerCount * 3;

    // Horizontal
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            score += evaluateWindow(board, i, j, 0, 1, player);
        }
    }

    // Vertical
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            score += evaluateWindow(board, i, j, 1, 0, player);
        }
    }

    // Diagonal (bottom left to top right)
    for (int i = 3; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            score += evaluateWindow(board, i, j, -1, 1, player);
        }
    }

    // Diagonal (top left to bottom right)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            score += evaluateWindow(board, i, j, 1, 1, player);
        }
    }

    return score;
}

int MinMax::evaluateWindow(const Board& board, int row, int col, int deltaRow, int deltaCol, char player) {
    int score = 0;
    char opponent = (player == 'X') ? 'O' : 'X';

    int playerCount = 0;
    int emptyCount = 0;
    int opponentCount = 0;

    for (int k = 0; k < 4; k++) {
        if (board.getBoardElement(row + k * deltaRow, col + k * deltaCol) == player) {
            playerCount++;
        } else if (board.getBoardElement(row + k * deltaRow, col + k * deltaCol) == opponent) {
            opponentCount++;
        } else {
            emptyCount++;
        }
    }

    if (playerCount == 4) {
        score += 100;
    } else if (playerCount == 3 && emptyCount == 1) {
        score += 5;
    } else if (playerCount == 2 && emptyCount == 2) {
        score += 2;
    }

    if (opponentCount == 3 && emptyCount == 1) {
        score -= 4;
    }

    return score;
}

bool MinMax::isTerminalNode(const Board& board) {
    return board.checkWin('X') || board.checkWin('O') || board.isBoardFull();
}

int MinMax::minimax(Board board, int depth, bool isMaximizing, int alpha, int beta) {
    char player = isMaximizing ? 'X' : 'O';
    char opponent = isMaximizing ? 'O' : 'X';

    if (depth == 0 || isTerminalNode(board)) {
        if (board.checkWin(player)) {
            return isMaximizing ? 1000000 : -1000000;
        } else if (board.checkWin(opponent)) {
            return isMaximizing ? -1000000 : 1000000;
        } else {
            return evaluate(board, player);
        }
    }

    if (isMaximizing) {
        int maxEval = std::numeric_limits<int>::min();
        for (int col = 0; col < 7; ++col) {
            if (board.getBoardElement(5, col) == ' ') {
                Board tempBoard = board;
                tempBoard.makeMove(col, player);
                int eval = minimax(tempBoard, depth - 1, false, alpha, beta);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (int col = 0; col < 7; ++col) {
            if (board.getBoardElement(5, col) == ' ') {
                Board tempBoard = board;
                tempBoard.makeMove(col, player);
                int eval = minimax(tempBoard, depth - 1, true, alpha, beta);
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return minEval;
    }
}

int MinMax::choosePosition(const Board& board, int depth) {
    int bestScore = std::numeric_limits<int>::min();
    int bestCol = -1;

    for (int col = 0; col < 7; ++col) {
        if (board.getBoardElement(5, col) == ' ') {
            Board tempBoard = board;
            tempBoard.makeMove(col, 'X');
            int score = minimax(tempBoard, depth - 1, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            if (score > bestScore) {
                bestScore = score;
                bestCol = col;
            }
        }
    }
    return bestCol;
}
