//
// Created by Wiktor on 30.05.2024.
//

#include "TicTacToe.h"

void TicTacToe::drawMarkers(HDC hdc, bool clear = false) {
    int padding = 15;
    if(clear) this->clearGrid();
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            if (grid[y][x] == 'X') {
                MoveToEx(hdc, x * CELL_SIZE + padding, y * CELL_SIZE + padding, nullptr);
                LineTo(hdc, (x + 1) * CELL_SIZE - padding, (y + 1) * CELL_SIZE - padding);
                MoveToEx(hdc, (x + 1) * CELL_SIZE - padding, y * CELL_SIZE + padding, nullptr);
                LineTo(hdc, x * CELL_SIZE + padding, (y + 1) * CELL_SIZE - padding);
            } else if (grid[y][x] == 'O') {
                Ellipse(hdc, x * CELL_SIZE + padding, y * CELL_SIZE + padding, (x + 1) * CELL_SIZE - padding, (y + 1) * CELL_SIZE - padding);
            }
        }
    }
}

void TicTacToe::set(int x, int y, char marker) {
    grid[x][y] = marker;
}

void TicTacToe::clearGrid() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j] = 0;
        }
    }
}
