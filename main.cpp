#ifndef UNICODE
#define UNICODE
#endif

#include<iostream>
#include <windows.h>
#include "WindowCreator.h"

using namespace std;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK GameWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[]  = L"TicTacToe";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    WNDCLASS gameWindowClass = { 0 };
    gameWindowClass.lpfnWndProc = GameWindowProc;
    gameWindowClass.hInstance = hInstance;
    gameWindowClass.lpszClassName = TEXT("GameWindowClass");
    RegisterClass(&gameWindowClass);

    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            L"Tic Tac Toe",
            WS_MINIMIZEBOX | WS_SYSMENU ,
            CW_USEDEFAULT, CW_USEDEFAULT, 300, 300,
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
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT rect;
            GetClientRect(hwnd, &rect);
            rect.top = 60;
            DrawTextW(hdc, TEXT("Wybierz tryb gry"), strlen("Wybierz tryb gry"), &rect, DT_CENTER);

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            creator->handleEvent(wmId);

            if(LOWORD(wParam) == 1) {
                cout << "erwq";
                HINSTANCE hInstance = GetModuleHandleW(nullptr);
                HWND gameHwnd = CreateWindowW(TEXT("GameWindowClass"), TEXT("Gra z komputerem"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 200, nullptr, nullptr, hInstance, nullptr);
                ShowWindow(gameHwnd, SW_SHOW);
                UpdateWindow(gameHwnd);
            }
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK GameWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
}

