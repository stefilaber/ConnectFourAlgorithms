#include "ConnectFourGame.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>  // Include this for time measurement

ConnectFourGame::ConnectFourGame(int depth) : board(), depth(depth) {}

void ConnectFourGame::playMultipleGames(int numGames) {
    MinMax player1;  // MinMax agent is 'X'
    MonteCarloTreeSearch player2;  // MCTS agent is 'O'

    int minMaxWins = 0;
    int mctsWins = 0;
    int draws = 0;
    double totalTime = 0.0;
    double totalDecisionTimePlayer1 = 0.0;
    double totalDecisionTimePlayer2 = 0.0;
    int totalRounds = 0;

    for (int game = 0; game < numGames; ++game) {
        board = Board();  // Reset the board
        bool gameOver = false;
        int turn = (game % 2 == 0) ? 1 : 2; // Alternate who starts first
        bool isFirstMove1 = true;
        bool isFirstMove2 = true;
        auto gameStart = std::chrono::high_resolution_clock::now();

        while (!gameOver) {
            int col;
            auto decisionStart = std::chrono::high_resolution_clock::now();

            if (turn == 1) {  // MinMax player's turn
                if (isFirstMove1) {
                    col = randomMove();
                    isFirstMove1 = false;
                } else {
                    col = player1.choosePosition(board, depth);
                }
            } else {  // MCTS player's turn
                if (isFirstMove2) {
                    col = randomMove();
                    isFirstMove2 = false;
                } else {
                    col = player2.choosePosition(board, depth);
                }
            }

            auto decisionEnd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> decisionTime = decisionEnd - decisionStart;

            if (turn == 1) {
                totalDecisionTimePlayer1 += decisionTime.count();
            } else {
                totalDecisionTimePlayer2 += decisionTime.count();
            }

            totalRounds++;

            if (col != -1 && board.makeMove(col, turn == 1 ? 'X' : 'O')) {
                if (board.checkWin(turn == 1 ? 'X' : 'O')) {
                    std::string winner = (turn == 1) ? "MinMax (X)" : "MCTS (O)";
                    gameOver = true;

                    if (turn == 1) {
                        minMaxWins++;
                    } else {
                        mctsWins++;
                    }
                } else if (board.isBoardFull()) {
                    gameOver = true;
                    draws++;
                }
                turn = (turn == 1) ? 2 : 1; // Switch turns
            }
        }

        auto gameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> gameTime = gameEnd - gameStart;
        totalTime += gameTime.count();

        // Print the final board after each game
        std::cout << "Final board after game " << game + 1 << ":" << std::endl;
        board.printBoard();

        // Optional: Save the final board to the file as well
        std::ofstream outfile("game_results.txt", std::ios::app);
        outfile << "Final board after game " << game + 1 << ":\n";
        for (int i = 5; i >= 0; --i) {
            for (int j = 0; j < 7; ++j) {
                outfile << board.getBoardElement(i, j) << " ";
            }
            outfile << "\n";
        }
        outfile << "\n";
        outfile.close();
    }

    double avgTimePerGame = totalTime / numGames;
    double avgDecisionTimePlayer1PerGame = totalDecisionTimePlayer1 / numGames;
    double avgDecisionTimePlayer2PerGame = totalDecisionTimePlayer2 / numGames;
    double avgDecisionTimePlayer1PerRound = totalDecisionTimePlayer1 / (totalRounds / 2);
    double avgDecisionTimePlayer2PerRound = totalDecisionTimePlayer2 / (totalRounds / 2);

    // Save the overall results after all games are complete
    std::ofstream outfile("game_results.txt", std::ios::app);
    outfile << "Total games: " << numGames << std::endl;
    outfile << "MinMax wins: " << minMaxWins << std::endl;
    outfile << "MCTS wins: " << mctsWins << std::endl;
    outfile << "Draws: " << draws << std::endl;
    outfile << "Average time per game: " << avgTimePerGame << " seconds" << std::endl;
    outfile << "Average decision time for MinMax per game: " << avgDecisionTimePlayer1PerGame << " seconds" << std::endl;
    outfile << "Average decision time for MCTS per game: " << avgDecisionTimePlayer2PerGame << " seconds" << std::endl;
    outfile << "Average decision time for MinMax per round: " << avgDecisionTimePlayer1PerRound << " seconds" << std::endl;
    outfile << "Average decision time for MCTS per round: " << avgDecisionTimePlayer2PerRound << " seconds" << std::endl;
    outfile.close();

    // Also print these statistics to the console
    std::cout << "Total games: " << numGames << std::endl;
    std::cout << "MinMax wins: " << minMaxWins << std::endl;
    std::cout << "MCTS wins: " << mctsWins << std::endl;
    std::cout << "Draws: " << draws << std::endl;
    std::cout << "Average time per game: " << avgTimePerGame << " seconds" << std::endl;
    std::cout << "Average decision time for MinMax per game: " << avgDecisionTimePlayer1PerGame << " seconds" << std::endl;
    std::cout << "Average decision time for MCTS per game: " << avgDecisionTimePlayer2PerGame << " seconds" << std::endl;
    std::cout << "Average decision time for MinMax per round: " << avgDecisionTimePlayer1PerRound << " seconds" << std::endl;
    std::cout << "Average decision time for MCTS per round: " << avgDecisionTimePlayer2PerRound << " seconds" << std::endl;
}

// Function to generate a random valid move
int ConnectFourGame::randomMove() {
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
