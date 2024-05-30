//
// Created by Wiktor on 27.05.2024.
//

#include "WindowCreator.h"
#include "ctime"
#include "Utils.h"

void WindowCreator::createText(const std::string& text) {
    RECT rect = this->rect();

    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

    SetTextAlign(hdc, TA_CENTER | TA_BASELINE);

    TextOut(hdc, windowWidth / 2, windowHeight/6, text.c_str(), text.length());

    SelectObject(hdc, hOldFont);
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
    std::cout << events.size();
//    auto it = this->events.find(id);
//    if (it != this->events.end()) {
//        it->second();
//    } else {
//        std::cout << "Funkcja nieznaleziona!" << std::endl;
//    }
}

void WindowCreator::addEvent(int id, std::string func) {
    events[id] = func;
}
