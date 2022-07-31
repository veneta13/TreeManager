#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../source/tree.h"

const char* tree1 = "| 8 |\n"
                    "| 3 2 9 |\n"
                    "| 2 | 8 6 | 2 |\n"
                    "| 8 6 | 11 | 12 | 8 5 |\n"
                    "| 11 | 4 3 | | | 11 | 6 |\n"
                    "| | | | | |\n";

const char* tree2 = "| 2 |\n"
                    "| 8 6 |\n"
                    "| 11 | |\n"
                    "| |\n";

const char* tree3 = "| 8 |\n"
                    "| 3 12 9 |\n"
                    "| 7 | | 2 |\n"
                    "| | 8 5 |\n"
                    "| 11 | 6 |\n"
                    "| | |\n";

const char* tree4 = "| -2 |\n"
                    "| 8 -6 |\n"
                    "| -11 | |\n"
                    "| |\n";

TEST_CASE("Read and write")
{
    SECTION("Tree 1")
    {
        Tree t;
        std::stringstream input(tree1), output;

        input >> t;
        output << t;

        REQUIRE(std::strcmp(output.str().c_str(), tree1) == 0);
    }

    SECTION("Tree 2")
    {
        Tree t;
        std::stringstream input(tree2), output;

        input >> t;
        output << t;

        REQUIRE(std::strcmp(output.str().c_str(), tree2) == 0);
    }

    SECTION("Tree 3")
    {
        Tree t;
        std::stringstream input(tree3), output;

        input >> t;
        output << t;

        REQUIRE(std::strcmp(output.str().c_str(), tree3) == 0);
    }

    SECTION("Tree 4")
    {
        Tree t;
        std::stringstream input(tree4), output;

        input >> t;
        output << t;

        REQUIRE(std::strcmp(output.str().c_str(), tree4) == 0);
    }
}

TEST_CASE("Subtree - self")
{
    SECTION("Tree 1")
    {
        Tree t;
        std::stringstream input(tree1), output;

        input >> t;
        t.containsSubtree(output, &t);

        REQUIRE(std::strcmp(output.str().c_str(), "Yes, there is such subtree!\n") == 0);
    }

    SECTION("Tree 2")
    {
        Tree t;
        std::stringstream input(tree2), output;

        input >> t;
        t.containsSubtree(output, &t);

        REQUIRE(std::strcmp(output.str().c_str(), "Yes, there is such subtree!\n") == 0);
    }

    SECTION("Tree 3")
    {
        Tree t;
        std::stringstream input(tree3), output;

        input >> t;
        t.containsSubtree(output, &t);

        REQUIRE(std::strcmp(output.str().c_str(), "Yes, there is such subtree!\n") == 0);
    }

    SECTION("Tree 4")
    {
        Tree t;
        std::stringstream input(tree4), output;

        input >> t;
        t.containsSubtree(output, &t);

        REQUIRE(std::strcmp(output.str().c_str(), "Yes, there is such subtree!\n") == 0);
    }
}

#pragma clang diagnostic pop
