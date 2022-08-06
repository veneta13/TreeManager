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

const char* tree5 = "| 8 |\n"
                    "| 3 2 9 |\n"
                    "| 2 | 8 6 | 2 |\n"
                    "| 8 6 | 11 | 12 | 8 5 |\n"
                    "| 11 | 4 3 | 5 | 5 8 1 | 11 | 6 |\n"
                    "| | | | | | | | | |\n";

const char* tree6 = "| 2 |\n"
                    "| 8 6 |\n"
                    "| 11 | 12 |\n"
                    "| | |\n";

const char* tree7 = "| 8 |\n"
                    "| 3 19 9 |\n"
                    "| 2 | | 2 |\n"
                    "| 8 6 | 8 5 |\n"
                    "| 11 | 4 3 | 11 | 6 |\n"
                    "| | | | | |\n";

const char* tree8 = "| 2 |\n"
                    "| 8 6 |\n"
                    "| 2 | |\n"
                    "| 8 6 |\n"
                    "| 11 | |\n"
                    "| 9 2 |\n"
                    "| | |\n";

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

TEST_CASE("Remove tree")
{
    SECTION("Remove tree 2 from tree 1")
    {
        const char* answer = "New Tree:\n"
                             "| 8 |\n"
                             "| 3 12 9 |\n"
                             "| 7 | | 2 |\n"
                             "| | 8 5 |\n"
                             "| 11 | 6 |\n"
                             "| | |\n";

        Tree t1, t2, t3;

        std::stringstream input1(tree1), input2(tree2), input3(tree3), output1, output2, output3;

        input1 >> t1;
        input2 >> t2;
        input3 >> t3;

        t1.removeSubtree(output1, &t2);
        output2 << t1;
        output3 << t3;

        REQUIRE(std::strcmp(output1.str().c_str(), answer) == 0);
        REQUIRE(std::strcmp(output2.str().c_str(), output3.str().c_str()) == 0);
    }

    SECTION("Remove tree 6 from tree 5")
    {
        const char* answer = "New Tree:\n"
                             "| 8 |\n"
                             "| 3 19 9 |\n"
                             "| 2 | | 2 |\n"
                             "| 8 6 | 8 5 |\n"
                             "| 11 | 4 3 | 11 | 6 |\n"
                             "| | | | | |\n";

        Tree t1, t2, t3;

        std::stringstream input1(tree5), input2(tree6), input3(tree7), output1, output2, output3;

        input1 >> t1;
        input2 >> t2;
        input3 >> t3;

        t1.removeSubtree(output1, &t2);
        output2 << t1;
        output3 << t3;

        REQUIRE(std::strcmp(output1.str().c_str(), answer) == 0);
        REQUIRE(std::strcmp(output2.str().c_str(), output3.str().c_str()) == 0);

    }

    SECTION("Recursive remove tree 2 from tree 8")
    {
        const char* answer = "New Tree:\n"
                             "| |\n";

        Tree t1, t2;

        std::stringstream input1(tree8), input2(tree2), output1, output2;

        input1 >> t1;
        input2 >> t2;

        t1.removeSubtree(output1, &t2);
        output2 << t1;

        REQUIRE(std::strcmp(output1.str().c_str(), answer) == 0);
        REQUIRE(std::strcmp(output2.str().c_str(), "| |\n") == 0);
    }

    SECTION("Recursive remove self")
    {
        const char* answer = "New Tree:\n"
                             "| |\n";

        Tree t1, t2;

        std::stringstream input1(tree1), input2(tree1), output1, output2;

        input1 >> t1;
        input2 >> t2;

        t1.removeSubtree(output1, &t2);
        output2 << t1;

        REQUIRE(std::strcmp(output1.str().c_str(), answer) == 0);
        REQUIRE(std::strcmp(output2.str().c_str(), "| |\n") == 0);
    }
}

#pragma clang diagnostic pop
