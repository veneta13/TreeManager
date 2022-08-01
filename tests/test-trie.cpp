#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../source/trie.h"

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

TEST_CASE("Add tree")
{
    SECTION("Add single tree")
    {
        Trie trie;
        Tree* t = new Tree();
        std::stringstream input(tree1), output, output_result;

        input >> *t;
        output << *t;

        trie.add(string("tree1"), t);

        Tree* result = trie.search(string("tree1"));

        output_result << *result;

        REQUIRE(std::strcmp(output.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(output_result.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(output.str().c_str(), output_result.str().c_str()) == 0);
    }

    SECTION("Add multiple trees")
    {
        Trie trie;
        Tree* t1 = new Tree();
        Tree* t2 = new Tree();
        std::stringstream input1(tree1), input2(tree2), output1, output2, output_result1, output_result2;

        input1 >> *t1;
        input2 >> *t2;

        output1 << *t1;
        output2 << *t2;

        REQUIRE(std::strcmp(output1.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(output2.str().c_str(), tree2) == 0);

        trie.add(string("tree1"), t1);
        trie.add(string("tree2"), t2);

        Tree* result_t1 = trie.search(string("tree1"));
        Tree* result_t2 = trie.search(string("tree2"));

        output_result1 << *result_t1;
        output_result2 << *result_t2;

        REQUIRE(std::strcmp(output1.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(output_result1.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(output1.str().c_str(), output_result1.str().c_str()) == 0);

        REQUIRE(std::strcmp(output2.str().c_str(), tree2) == 0);
        REQUIRE(std::strcmp(output_result2.str().c_str(), tree2) == 0);
        REQUIRE(std::strcmp(output2.str().c_str(), output_result2.str().c_str()) == 0);
    }

    SECTION("Replace tree")
    {
        Trie trie;
        Tree* t1 = new Tree();
        Tree* t2 = new Tree();
        std::stringstream input1(tree1), input2(tree2), output1, output2, output_result1, output_result2;

        input1 >> *t1;
        input2 >> *t2;

        output1 << *t1;
        output2 << *t2;

        trie.add(string("tree"), t1);

        Tree* result_t1 = trie.search(string("tree"));

        output_result1 << *result_t1;

        REQUIRE(std::strcmp(output1.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(output_result1.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(output1.str().c_str(), output_result1.str().c_str()) == 0);

        trie.add(string("tree"), t2);

        Tree* result_t2 = trie.search(string("tree"));

        output_result2 << *result_t2;

        REQUIRE(std::strcmp(output2.str().c_str(), tree2) == 0);
        REQUIRE(std::strcmp(output_result2.str().c_str(), tree2) == 0);
        REQUIRE(std::strcmp(output2.str().c_str(), output_result2.str().c_str()) == 0);

        REQUIRE(result_t2);

        REQUIRE(!t1);
        REQUIRE(!t2);
    }

    SECTION("Tree that does not exist")
    {
        Trie trie;

        Tree* t = trie.search(string("tree"));

        REQUIRE(!t);
    }
}

#pragma clang diagnostic pop
