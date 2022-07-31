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

TEST_CASE("Subtree - empty tree")
{
    SECTION("Tree 1")
    {
        Tree t, empty;
        std::stringstream input(tree1), output;

        input >> t;
        t.containsSubtree(output, &empty);

        REQUIRE(std::strcmp(output.str().c_str(), "Yes, there is such subtree!\n") == 0);
    }

    SECTION("Tree 2")
    {
        Tree t, empty;
        std::stringstream input(tree2), output;

        input >> t;
        t.containsSubtree(output, &empty);

        REQUIRE(std::strcmp(output.str().c_str(), "Yes, there is such subtree!\n") == 0);
    }

    SECTION("Tree 3")
    {
        Tree t, empty;
        std::stringstream input(tree3), output;

        input >> t;
        t.containsSubtree(output, &empty);

        REQUIRE(std::strcmp(output.str().c_str(), "Yes, there is such subtree!\n") == 0);
    }

    SECTION("Tree 4")
    {
        Tree t, empty;
        std::stringstream input(tree4), output;

        input >> t;
        t.containsSubtree(output, &empty);

        REQUIRE(std::strcmp(output.str().c_str(), "Yes, there is such subtree!\n") == 0);
    }
}

TEST_CASE("Subtree")
{
    SECTION("Tree 1 and tree 2")
    {
        Tree t1, t2;
        std::stringstream input1(tree1), input2(tree2), output1, output2;

        input1 >> t1;
        input2 >> t2;

        t1.containsSubtree(output1, &t2);
        t2.containsSubtree(output2, &t1);

        REQUIRE(std::strcmp(output1.str().c_str(), "Yes, there is such subtree!\n") == 0);
        REQUIRE(std::strcmp(output2.str().c_str(), "No, such subtree does not exist!\n") == 0);
    }

    SECTION("Tree 1 and tree 3")
    {
        Tree t1, t3;
        std::stringstream input1(tree1), input3(tree3), output1, output2;

        input1 >> t1;
        input3 >> t3;

        t1.containsSubtree(output1, &t3);
        t3.containsSubtree(output2, &t1);

        REQUIRE(std::strcmp(output1.str().c_str(), "No, such subtree does not exist!\n") == 0);
        REQUIRE(std::strcmp(output2.str().c_str(), "No, such subtree does not exist!\n") == 0);
    }

    SECTION("Tree 2 and tree 4")
    {
        Tree t2, t4;
        std::stringstream input2(tree2), input4(tree4), output1, output2;

        input2 >> t2;
        input4 >> t4;

        t2.containsSubtree(output1, &t4);
        t4.containsSubtree(output2, &t2);

        REQUIRE(std::strcmp(output1.str().c_str(), "No, such subtree does not exist!\n") == 0);
        REQUIRE(std::strcmp(output2.str().c_str(), "No, such subtree does not exist!\n") == 0);
    }
}

#pragma clang diagnostic pop
