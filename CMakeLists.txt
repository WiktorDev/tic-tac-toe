cmake_minimum_required(VERSION 3.28)
project(tic_tac_toe)

#dependencies
#include(FetchContent)
#
#set(IMGUI_VERSION 1.90.6)
#FetchContent_Declare(
#        imgui
#        URL https://github.com/ocornut/imgui/archive/refs/tags/v${IMGUI_VERSION}.tar.gz
#        FIND_PACKAGE_ARGS ${IMGUI_VERSION}
#)
#set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
#FetchContent_MakeAvailable(imgui)

set(CMAKE_CXX_STANDARD 23)
#set(SOURCE_FILES main.cpp)
#add_executable(${PROJECT_NAME} ${SOURCE_FILES})
#target_link_libraries(${PROJECT_NAME} imgui)

add_executable(tic_tac_toe main.cpp
        game/TicTacToeAI.cpp
        game/TicTacToeAI.h
        WindowCreator.cpp
        WindowCreator.h
        Utils.cpp
        Utils.h
        windows/GameWindow.cpp
        game/TicTacToe.cpp
        game/TicTacToe.h
)
