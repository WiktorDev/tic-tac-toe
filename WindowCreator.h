//
// Created by Wiktor on 27.05.2024.
//

#ifndef TIC_TAC_TOE_WINDOWCREATOR_H
#define TIC_TAC_TOE_WINDOWCREATOR_H

#include <functional>
#include <iostream>
#include <windows.h>
#include <map>

class WindowCreator {
    using Function = void(*)();

    HWND hWnd;
    HDC hdc;
    LPARAM lParam;

    RECT rect();

    std::map<int, std::string> events = {};

    void addEvent(int id, std::string func);
public:
    WindowCreator(HWND hwnd, LPARAM lparam);
    void createText(const std::string& text);
    void createButton(std::string label, int x, int y, int width, int height, int id);
    void setHdc(HDC hdc);

    void handleEvent(int id);

    static bool registerClass(WNDPROC proc, HINSTANCE hInstance, const std::wstring& className);
    static HWND createWindow(const std::wstring& windowName, int width, int height);
};


#endif //TIC_TAC_TOE_WINDOWCREATOR_H
