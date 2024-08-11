#include "Board.h"
#include <iostream>

Board::Board() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            board[i][j] = ' ';
        }
    }
}

void Board::printBoard() const {
    std::cout << " 0 1 2 3 4 5 6" << std::endl;
    for (int i = 5; i >= 0; --i) {
        for (int j = 0; j < 7; ++j) {
            std::cout << "|" << board[i][j];
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "---------------" << std::endl;
}

bool Board::makeMove(int col, char player) {
    if (col < 0 || col >= 7 || board[5][col] != ' ') {
        return false;
    }
    for (int i = 0; i <= 5; ++i) {
        if (board[i][col] == ' ') {
            board[i][col] = player;
            return true;
        }
    }
    return false;
}

bool Board::checkWin(char player) const {
    // Check horizontal, vertical, and two diagonal directions for a win
    // Horizontal
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == player && board[i][j+1] == player &&
                board[i][j+2] == player && board[i][j+3] == player) {
                return true;
            }
        }
    }

    // Vertical
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (board[i][j] == player && board[i+1][j] == player &&
                board[i+2][j] == player && board[i+3][j] == player) {
                return true;
            }
        }
    }

    // Diagonal (bottom left to top right)
    for (int i = 3; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == player && board[i-1][j+1] == player &&
                board[i-2][j+2] == player && board[i-3][j+3] == player) {
                return true;
            }
        }
    }

    // Diagonal (top left to bottom right)
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == player && board[i+1][j+1] == player &&
                board[i+2][j+2] == player && board[i+3][j+3] == player) {
                return true;
            }
        }
    }

    return false;
}

bool Board::isBoardFull() const {
    for (int j = 0; j < 7; ++j) {
        if (board[5][j] == ' ') {
            return false;
        }
    }
    return true;
}

void Board::copyBoard(char destination[6][7]) const {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            destination[i][j] = board[i][j];
        }
    }
}

char Board::getBoardElement(int row, int col) const {
    return board[row][col];
}
