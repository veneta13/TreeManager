#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

const char* tree1 = "| 8 |\n"
                    "| 3 2 9 |\n"
                    "| 2 | 8 6 | 2 |\n"
                    "| 8 6 | 11 | 12 | 8 5 |\n"
                    "| 11 | 4 3 | | | 11 | 6 |\n"
                    "| | | | | | ";

const char* tree2 = "| 2 |\n"
                    "| 8 6 |\n"
                    "| 11 | |\n"
                    "| |";

const char* tree3 = "| 8 |\n"
                    "| 3 12 9 |\n"
                    "| 7 | | 2 |\n"
                    "| | 8 5 |\n"
                    "| 11 | 6 |\n"
                    "| | |";

#pragma clang diagnostic pop
