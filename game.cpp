#ifndef UNICODE
#define UNICODE
#endif

#include<iostream>
#include <windows.h>
#include <windowsx.h>
#include "TicTacToeAI.h"

const int GRID_SIZE = 3;
const int CELL_SIZE = 100;
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;

char grid[GRID_SIZE][GRID_SIZE] = { 0 };

TicTacToeAI *ai = new TicTacToeAI(grid);

using namespace std;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[]  = L"TicTacToe";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            L"Tic Tac Toe",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_SIZE, WINDOW_SIZE,
            nullptr,
            nullptr,
            hInstance,
            nullptr
    );

    if (hwnd == nullptr) return 0;
    ShowWindow(hwnd, nCmdShow);
    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void DrawGrid(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    for (int i = 0; i <= GRID_SIZE; ++i) {
        MoveToEx(hdc, i * CELL_SIZE, 0, nullptr);
        LineTo(hdc, i * CELL_SIZE, WINDOW_SIZE);
        MoveToEx(hdc, 0, i * CELL_SIZE, nullptr);
        LineTo(hdc, WINDOW_SIZE, i * CELL_SIZE);
    }

    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            if (grid[y][x] == 'X') {
                MoveToEx(hdc, x * CELL_SIZE, y * CELL_SIZE, nullptr);
                LineTo(hdc, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
                MoveToEx(hdc, (x + 1) * CELL_SIZE, y * CELL_SIZE, nullptr);
                LineTo(hdc, x * CELL_SIZE, (y + 1) * CELL_SIZE);
            } else if (grid[y][x] == 'O') {
                Ellipse(hdc, x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
            }
        }
    }
    EndPaint(hwnd, &ps);
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            CreateWindowW(TEXT("button"), TEXT("&Red"),
                          WS_CHILD | WS_VISIBLE | WS_GROUP ,
                          0, 0, 100, 30, hwnd, (HMENU) 1, ((LPCREATESTRUCT)lParam)->hInstance, nullptr);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT: {
            DrawGrid(hwnd);
            if(ai->gameIsDone()) {
                int player_state = ai->getBoardState(PLAYER_MARKER);
                cout << TicTacToeAI::printGameState(player_state);
                MessageBoxW(hwnd, L"Gra zakończona!", L"Tic Tac Toe", 2);
            }
            break;
        }
        case WM_LBUTTONDOWN: {
            int x = GET_Y_LPARAM(lParam) / CELL_SIZE;
            int y = GET_X_LPARAM(lParam) / CELL_SIZE;

            if (x < GRID_SIZE && y < GRID_SIZE) {
                if(ai->positionOccupied(make_pair(x, y))) break;
                grid[x][y] = PLAYER_MARKER;
                pair<int, pair<int, int>> ai_move = ai->minimaxOptimization(AI_MARKER, 0, LOSS, WIN);
                grid[ai_move.second.first][ai_move.second.second] = AI_MARKER;
                InvalidateRect(hwnd, nullptr, TRUE);
            }
            break;
        }
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
