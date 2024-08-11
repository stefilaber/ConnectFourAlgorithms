#include "ConnectFourGame.h"
#include <iostream>

ConnectFourGame::ConnectFourGame(int depth) : board(), depth(depth) {}

void ConnectFourGame::playGame() {
    MinMax player1;  // MinMax agent is 'X'
    MonteCarloTreeSearch player2;  // MCTS agent is 'O'

    bool gameOver = false;
    int turn = 1; // Player 1 (MinMax) starts

    while (!gameOver) {
        board.printBoard();
        int col = (turn == 1) ? player1.choosePosition(board, depth) : player2.choosePosition(board, depth);
        if (col != -1 && board.makeMove(col, turn == 1 ? 'X' : 'O')) {
            if (board.checkWin(turn == 1 ? 'X' : 'O')) {
                board.printBoard();
                std::cout << "Player " << (turn == 1 ? "MinMax (X)" : "MCTS (O)") << " wins!" << std::endl;
                gameOver = true;
            } else if (board.isBoardFull()) {
                board.printBoard();
                std::cout << "It's a draw!" << std::endl;
                gameOver = true;
            }
            turn = (turn == 1) ? 2 : 1; // Switch turns
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }
}
