#pragma once
#include <iostream>


class CLI {
public:
    static char getUserInput();

    static void clearCinBuffer();

    // To use the display function, the content object must overload the << operator for std::ostream.
    template<typename T>
    static void display(const T& obj) {
        std::cout << obj << '\n';
    }
};
