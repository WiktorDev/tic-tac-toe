//
// Created by Wiktor on 29.05.2024.
//

#include "Utils.h"
#include "iostream"
#include "random"

int Utils::randomId() {
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> dis(100000, 999999);
    return dis(gen);
}

std::wstring Utils::stringToWstring(const std::string &str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}
