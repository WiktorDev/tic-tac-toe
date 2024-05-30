//
// Created by Wiktor on 27.05.2024.
//

#include "WindowCreator.h"
#include "ctime"
#include "Utils.h"
#include "Utils.h"
#include <codecvt>

void WindowCreator::createText(const std::string& text) {
    RECT rect;
    GetClientRect(this->hWnd, &rect);
    rect.top = 60;
    DrawTextW(hdc, TEXT(Utils::stringToWstring(text).c_str()), text.size(), &rect, DT_CENTER);
}

void WindowCreator::setHdc(HDC hdc) {
    this->hdc = hdc;
}

WindowCreator::WindowCreator(HWND hwnd, LPARAM lparam) {
    this->hWnd = hwnd;
    this->lParam = lparam;
}

RECT WindowCreator::rect() {
    RECT rect;
    GetClientRect(this->hWnd, &rect);
    return rect;
}

void WindowCreator::createButton(std::string label, int x, int y, int width, int height, Function func) {
    int id = Utils::randomId();
    std::string controlClass = "BUTTON";
    HWND hwndButton = CreateWindow(
            controlClass.c_str(),
            label.c_str(),
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styl przycisku
            x,         // Pozycja X
            y,         // Pozycja Y
            width,        // Szerokość
            height,         // Wysokość
            this->hWnd,       // Rodzic
            (HMENU)1,   // Id przycisku
            (HINSTANCE)GetWindowLongPtr(this->hWnd, GWLP_HINSTANCE),
            NULL);      // Dodatkowe dane
    this->addEvent(id, label);
}

void WindowCreator::handleEvent(int id) {
//    auto it = this->events.find(id);
//    if (it != this->events.end()) {
//        it->second();
//    } else {
//        std::cout << "Funkcja nieznaleziona!" << std::endl;
//    }
//    for (const auto &item: this->events) {
//        std::cout << item.first << " " << item.second << std::endl;
//    }
}

void WindowCreator::addEvent(int id, std::string func) {
    events[id] = func;
}

bool WindowCreator::registerClass(WNDPROC proc, HINSTANCE hInstance, const std::wstring &className) {
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = proc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className.c_str();

    if (!RegisterClassW(&wc)) {
        MessageBoxW(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        return false;
    }

    return true;
}
