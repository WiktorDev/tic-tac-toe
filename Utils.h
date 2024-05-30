//
// Created by Wiktor on 29.05.2024.
//

#ifndef TIC_TAC_TOE_UTILS_H
#define TIC_TAC_TOE_UTILS_H

#include <format>
#include <codecvt>

class Utils {
public:
    static int randomId();
    static std::wstring stringToWstring(const std::string& str);
};


#endif //TIC_TAC_TOE_UTILS_H
