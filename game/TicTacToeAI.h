//
// Created by Wiktor on 23.05.2024.
//

#ifndef TIC_TAC_TOE_TICTACTOEAI_H
#define TIC_TAC_TOE_TICTACTOEAI_H

#define WIN 1000
#define	DRAW 0
#define LOSS -1000

#define EMPTY_SPACE '-'

#include "TicTacToe.h"
#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

class TicTacToeAI {
    vector<vector<pair<int, int>>> winning_states {
        { std::make_pair(0, 0), std::make_pair(0, 1), std::make_pair(0, 2) },
        { std::make_pair(1, 0), std::make_pair(1, 1), std::make_pair(1, 2) },
        { std::make_pair(2, 0), std::make_pair(2, 1), std::make_pair(2, 2) },
        // Every column
        { std::make_pair(0, 0), std::make_pair(1, 0), std::make_pair(2, 0) },
        { std::make_pair(0, 1), std::make_pair(1, 1), std::make_pair(2, 1) },
        { std::make_pair(0, 2), std::make_pair(1, 2), std::make_pair(2, 2) },
        // Every diagonal
        { std::make_pair(0, 0), std::make_pair(1, 1), std::make_pair(2, 2) },
        { std::make_pair(2, 0), std::make_pair(1, 1), std::make_pair(0, 2) }
    };
    vector<pair<int, int>> getLegalMoves();
    vector<pair<int, int>> getOccupiedPositions(char marker);
    bool boardIsFull();
    bool gameIsWon(vector<std::pair<int, int>> occupied_positions);
    static char getOpponentMarker(char marker);
    char (&board)[3][3];
public:
    explicit TicTacToeAI(char (&grid)[3][3]);
    static string printGameState(int state);
    bool positionOccupied(pair<int, int> pos);
    int getBoardState(char marker);
    pair<int, pair<int, int>> minimaxOptimization(char marker, int depth, int alpha, int beta);
    bool gameIsDone();
};


#endif //TIC_TAC_TOE_TICTACTOEAI_H
