#include <iostream>
#include <limits>
#include <random>
#include <time.h> 
using namespace std;

class Algorithm
{
    public:
        virtual int choosePosition(const char board[6][7], int depth) = 0;
};

class HumanPlayer : public Algorithm
{
    public:
        int choosePosition(const char board[6][7], int depth)
        {
            int move;
            cin >> move;
            return move;
        }
};

class MockAlgo : public Algorithm
{
    public:
        int choosePosition(const char board[6][7], int depth)
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, 6);
            while (true)
            {
                int col = dis(gen);
                if (board[5][col] == ' ')
                {   
                    return col;
                }
            }
            return -1;
        }
};

class MinMax : public Algorithm
{
    private:
        int evaluate(const char board[6][7], char player) {
            int score = 0;

            // Evaluate center column preference
            int centerCount = 0;
            for (int i = 0; i < 6; i++) {
                if (board[i][3] == player) {
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

        int evaluateWindow(const char board[6][7], int row, int col, int deltaRow, int deltaCol, char player) {
            int score = 0;
            char opponent = (player == 'X') ? 'O' : 'X';

            int playerCount = 0;
            int emptyCount = 0;
            int opponentCount = 0;

            for (int k = 0; k < 4; k++) {
                if (board[row + k * deltaRow][col + k * deltaCol] == player) {
                    playerCount++;
                } else if (board[row + k * deltaRow][col + k * deltaCol] == opponent) {
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

        bool isTerminalNode(const char board[6][7]) {
            return checkWin(board, 'X') || checkWin(board, 'O') || isBoardFull(board);
        }

        bool checkWin(const char board[6][7], char player) {
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

        bool isBoardFull(const char board[6][7]) {
            for (int j = 0; j < 7; ++j) {
                if (board[5][j] == ' ') {
                    return false;
                }
            }
            return true;
        }

        void copyBoard(const char source[6][7], char destination[6][7]) {
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 7; ++j) {
                    destination[i][j] = source[i][j];
                }
            }
        }

        int minimax(char board[6][7], int depth, bool isMaximizing, int alpha, int beta) {
            char player = isMaximizing ? 'X' : 'O';
            char opponent = isMaximizing ? 'O' : 'X';

            if (depth == 0 || isTerminalNode(board)) {
                if (checkWin(board, player)) {
                    return isMaximizing ? 1000000 : -1000000;
                } else if (checkWin(board, opponent)) {
                    return isMaximizing ? -1000000 : 1000000;
                } else {
                    return evaluate(board, player);
                }
            }

            if (isMaximizing) {
                int maxEval = numeric_limits<int>::min();
                for (int col = 0; col < 7; ++col) {
                    if (board[5][col] == ' ') {
                        char tempBoard[6][7];
                        copyBoard(board, tempBoard);
                        makeMove(tempBoard, col, player);
                        int eval = minimax(tempBoard, depth - 1, false, alpha, beta);
                        maxEval = max(maxEval, eval);
                        alpha = max(alpha, eval);
                        if (beta <= alpha) {
                            break;
                        }
                    }
                }
                return maxEval;
            } else {
                int minEval = numeric_limits<int>::max();
                for (int col = 0; col < 7; ++col) {
                    if (board[5][col] == ' ') {
                        char tempBoard[6][7];
                        copyBoard(board, tempBoard);
                        makeMove(tempBoard, col, player);
                        int eval = minimax(tempBoard, depth - 1, true, alpha, beta);
                        minEval = min(minEval, eval);
                        beta = min(beta, eval);
                        if (beta <= alpha) {
                            break;
                        }
                    }
                }
                return minEval;
            }
        }

        bool makeMove(char board[6][7], int col, char player) {
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

    public:
        int choosePosition(const char board[6][7], int depth) override {
            int bestScore = numeric_limits<int>::min();
            int bestCol = -1;

            for (int col = 0; col < 7; ++col) {
                if (board[5][col] == ' ') {
                    char tempBoard[6][7];
                    copyBoard(board, tempBoard);
                    makeMove(tempBoard, col, 'X');
                    int score = minimax(tempBoard, depth - 1, false, numeric_limits<int>::min(), numeric_limits<int>::max());
                    if (score > bestScore) {
                        bestScore = score;
                        bestCol = col;
                    }
                }
            }
            return bestCol;
        }
};

class ConnectFourGame {
public:
    ConnectFourGame() {
        // Initialize the board with empty spaces
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                board[i][j] = ' ';
            }
        }
    }

    void playGame() {
        HumanPlayer player1;
        MinMax player2;

        bool gameOver = false;
        int turn = 1; // Player 1 starts
        int depth = 10; // Not used in MockAlgo, but included for compatibility

        while (!gameOver) {
            printBoard();
            int col = (turn == 1) ? player1.choosePosition(board, depth) : player2.choosePosition(board, depth);
            if (col != -1 && makeMove(col, turn == 1 ? 'X' : 'O')) {
                if (checkWin(turn == 1 ? 'X' : 'O')) {
                    printBoard();
                    std::cout << "Player " << turn << " wins!" << std::endl;
                    gameOver = true;
                } else if (isBoardFull()) {
                    printBoard();
                    std::cout << "It's a draw!" << std::endl;
                    gameOver = true;
                }
                turn = (turn == 1) ? 2 : 1; // Switch turns
            } else {
                std::cout << "Invalid move. Try again." << std::endl;
            }
        }
    }

private:
    char board[6][7];

    void printBoard() {
        std::cout << " 0 1 2 3 4 5 6" << std::endl;
        for (int i = 5; i >= 0; --i) {
            for (int j = 0; j < 7; ++j) {
                std::cout << "|" << board[i][j];
            }
            std::cout << "|" << std::endl;
        }
        std::cout << "---------------" << std::endl;
    }

    bool makeMove(int col, char player) {
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

    bool checkWin(char player) {
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

    bool isBoardFull() {
        for (int j = 0; j < 7; ++j) {
            if (board[5][j] == ' ') {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    ConnectFourGame game;
    game.playGame();
    return 0;
}