#ifndef BOARD_H
#define BOARD_H

class Board {
public:
    Board();

    void printBoard() const;
    bool makeMove(int col, char player);
    bool checkWin(char player) const;
    bool isBoardFull() const;
    void copyBoard(char destination[6][7]) const;

    char getBoardElement(int row, int col) const;

private:
    char board[6][7];
};

#endif // BOARD_H
