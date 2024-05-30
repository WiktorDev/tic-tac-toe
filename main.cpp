#ifndef UNICODE
#define UNICODE
#endif

#include<iostream>
#include <windows.h>
#include "WindowCreator.h"
#include "game/TicTacToeAI.h"
#include <windowsx.h>
#include <codecvt>
#include "Utils.h"
#include "game/TicTacToe.h"

using namespace std;

TicTacToe* game = new TicTacToe();

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK GameWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    WindowCreator::registerClass(WindowProc, hInstance, L"TicTacToe");
    WindowCreator::registerClass(GameWindowProc, hInstance, L"GameWindowClass");

    HWND hwnd = CreateWindowEx(
            0,L"TicTacToe",L"Tic Tac Toe",
            WS_MINIMIZEBOX | WS_SYSMENU ,
            CW_USEDEFAULT, CW_USEDEFAULT,
            300, 300,
            nullptr,nullptr,
            hInstance,nullptr
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

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    WindowCreator *creator = new WindowCreator(hwnd, lParam);
    switch (uMsg) {
        case WM_CREATE: {
            creator->createButton("Graj z komputerem", 20, 100, 250, 30, []() -> void {
                cout << "Clicked 1";
            });
//            creator->createButton("Graj ze znajomym", 20, 140, 250, 30, []() -> void {
//                cout << "Clicked 2";
//            });
            return 0;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;

            creator->setHdc(BeginPaint(hwnd, &ps));
            creator->createText("Wybierz tryb gry");

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            creator->handleEvent(wmId);

            if(LOWORD(wParam) == 1) {
                game->clearGrid();
                HINSTANCE hInstance = GetModuleHandleW(nullptr);
                HWND gameHwnd = CreateWindowW(
                        L"GameWindowClass",
                        L"Gra z komputerem",
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        WINDOW_SIZE+17, WINDOW_SIZE+40,
                        nullptr, nullptr,
                        hInstance,
                        nullptr
                );
                ShowWindow(gameHwnd, SW_SHOW);
                UpdateWindow(gameHwnd);
            }
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void DrawGrid(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    for (int i = 0; i <= GRID_SIZE; ++i) {
        HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
        SelectObject(hdc, pen);

        MoveToEx(hdc, i * CELL_SIZE, 0, nullptr);
        LineTo(hdc, i * CELL_SIZE, WINDOW_SIZE);
        MoveToEx(hdc, 0, i * CELL_SIZE, nullptr);
        LineTo(hdc, WINDOW_SIZE, i * CELL_SIZE);
    }

    game->drawMarkers(hdc);
    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK GameWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    TicTacToeAI *ai = new TicTacToeAI(game->grid);

    switch (uMsg) {
        case WM_PAINT: {
            DrawGrid(hwnd);
            PostMessageW(hwnd, WM_COMMAND, 2137, 0);
            break;
        }
        case WM_COMMAND: {
            if(LOWORD(wParam) == 2137) {
                if(ai->gameIsDone()) {
                    int player_state = ai->getBoardState(PLAYER_MARKER);
                    int result = MessageBox(hwnd, Utils::stringToWstring(TicTacToeAI::printGameState(player_state)).c_str(), L"Tic Tac Toe", 5);
                    switch(result) {
                        case 4:
                            game->clearGrid();
                            InvalidateRect(hwnd, nullptr, TRUE);
                            break;
                        case 2:
                            PostMessage(hwnd, WM_CLOSE, 0, 0);
                            break;
                        default:
                            break;
                    }
                }
            }
            break;
        }
        case WM_LBUTTONDOWN: {
            int x = GET_Y_LPARAM(lParam) / CELL_SIZE;
            int y = GET_X_LPARAM(lParam) / CELL_SIZE;

            if (x < GRID_SIZE && y < GRID_SIZE) {
                if(ai->positionOccupied(make_pair(x, y))) break;
                game->set(x, y, PLAYER_MARKER);
                pair<int, pair<int, int>> ai_move = ai->minimaxOptimization(AI_MARKER, 0, LOSS, WIN);
                game->set(ai_move.second.first, ai_move.second.second, AI_MARKER);
                InvalidateRect(hwnd, nullptr, TRUE);
            }
            break;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
