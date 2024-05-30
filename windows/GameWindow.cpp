//
// Created by Wiktor on 30.05.2024.
//

//#include<iostream>
//#include "string"
//#include <windows.h>
//
//LRESULT CALLBACK GameWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
//class GameWindow {
//public:
//    GameWindow(HINSTANCE hInstance) {
//        WNDCLASS wc = { };
//        wc.lpfnWndProc = GameWindowProc;
//        wc.hInstance = hInstance;
//        wc.lpszClassName = TEXT("GameWindowClass");
//
//        RegisterClass(&wc);
//    }
//    static void open() {
//        HINSTANCE hInstance = GetModuleHandleW(nullptr);
//        HWND gameHwnd = CreateWindowW(
//                L"GameWindowClass",
//                L"Gra z komputerem",
//                WS_OVERLAPPEDWINDOW,
//                CW_USEDEFAULT,
//                CW_USEDEFAULT,
//                400, 200,
//                nullptr, nullptr,
//                hInstance,
//                nullptr
//        );
//        ShowWindow(gameHwnd, SW_SHOW);
//        UpdateWindow(gameHwnd);
//    }
//};
//
//LRESULT CALLBACK GameWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//    switch (uMsg) {
//        case WM_DESTROY:
//            PostQuitMessage(0);
//            return 0;
//        default:
//            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
//    }
//}
