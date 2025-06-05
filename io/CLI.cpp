#include "CLI.h"
#include <iostream>
#include <limits>

char CLI::getUserInput() {
    while (true) {
        display("w,a,s,d or q to exit: ");
        char in{};
        std::cin >> in;

        if (std::cin.fail()) {
            clearCinBuffer();
            std::cout << "Invalid input\n";
            continue;
        }

        // clear buffer in case user entered more than one character
        clearCinBuffer();

        return in;
    }
}

void CLI::clearCinBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
