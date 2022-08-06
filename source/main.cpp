#include "executor.h"

#include <iostream>

int main() {
    Executor exec;
    exec.enter(std::cout, std::cin);
    return 0;
}
