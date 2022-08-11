#include "executor.h"

#include <iostream>

int main() {
    Executor exec;

    try {
        exec.enter(std::cout, std::cin);
    }
    catch (...) {
        std::cout << "Unexpected error has occurred! Exiting...";
    }

    return 0;
}
