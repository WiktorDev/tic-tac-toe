//
// Created by Wiktor on 30.05.2024.
//

#ifndef TIC_TAC_TOE_TICTACTOE_H
#define TIC_TAC_TOE_TICTACTOE_H

#include <windows.h>

#define OPPONENT_MARKER 'O'
#define PLAYER_MARKER 'X'

#define GRID_SIZE 3
#define CELL_SIZE 100

const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;

class TicTacToe {
public:
    bool withAi = true;
    char move = PLAYER_MARKER;

    char grid[GRID_SIZE][GRID_SIZE] = { 0 };
    void drawMarkers(HDC hdc, bool clear);
    void set(int x, int y, char marker);
    void clearGrid();
};


#endif //TIC_TAC_TOE_TICTACTOE_H
