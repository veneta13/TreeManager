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
        std::stringstream input(tree1), output, outputResult;

        input >> *t;
        output << *t;

        trie.add(string("tree1"), t);

        Tree* result = trie.search(string("tree1"));

        outputResult << *result;

        REQUIRE(std::strcmp(output.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(outputResult.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(output.str().c_str(), outputResult.str().c_str()) == 0);
    }

    SECTION("Add multiple trees")
    {
        Trie trie;
        Tree* t1 = new Tree();
        Tree* t2 = new Tree();
        std::stringstream input1(tree1), input2(tree2), output1, output2, outputResult1, outputResult2;

        input1 >> *t1;
        input2 >> *t2;

        output1 << *t1;
        output2 << *t2;

        REQUIRE(std::strcmp(output1.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(output2.str().c_str(), tree2) == 0);

        trie.add(string("tree1"), t1);
        trie.add(string("tree2"), t2);

        Tree* resultT1 = trie.search(string("tree1"));
        Tree* resultT2 = trie.search(string("tree2"));

        outputResult1 << *resultT1;
        outputResult2 << *resultT2;

        REQUIRE(std::strcmp(output1.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(outputResult1.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(output1.str().c_str(), outputResult1.str().c_str()) == 0);

        REQUIRE(std::strcmp(output2.str().c_str(), tree2) == 0);
        REQUIRE(std::strcmp(outputResult2.str().c_str(), tree2) == 0);
        REQUIRE(std::strcmp(output2.str().c_str(), outputResult2.str().c_str()) == 0);
    }

    SECTION("Replace tree")
    {
        Trie trie;
        Tree* t1 = new Tree();
        Tree* t2 = new Tree();
        std::stringstream input1(tree1), input2(tree2), output1, output2, outputResult1, outputResult2;

        input1 >> *t1;
        input2 >> *t2;

        output1 << *t1;
        output2 << *t2;

        trie.add(string("tree"), t1);

        Tree* resultT1 = trie.search(string("tree"));

        outputResult1 << *resultT1;

        REQUIRE(std::strcmp(output1.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(outputResult1.str().c_str(), tree1) == 0);
        REQUIRE(std::strcmp(output1.str().c_str(), outputResult1.str().c_str()) == 0);

        trie.add(string("tree"), t2);

        Tree* resultT2 = trie.search(string("tree"));

        outputResult2 << *resultT2;

        REQUIRE(std::strcmp(output2.str().c_str(), tree2) == 0);
        REQUIRE(std::strcmp(outputResult2.str().c_str(), tree2) == 0);
        REQUIRE(std::strcmp(output2.str().c_str(), outputResult2.str().c_str()) == 0);

        REQUIRE(resultT2);

        REQUIRE(!t1);
        REQUIRE(!t2);
    }
}

TEST_CASE("Search for tree")
{
    SECTION("Tree that does not exist")
    {
        Trie trie;

        Tree* t = trie.search(string("tree"));

        REQUIRE(!t);
    }
}

TEST_CASE("Clear")
{
    SECTION("Clear trees")
    {
        Trie trie;
        Tree* t1 = new Tree();
        Tree* t2 = new Tree();
        std::stringstream input1(tree1), input2(tree2);

        input1 >> *t1;
        input2 >> *t2;

        REQUIRE(t1);
        REQUIRE(t2);

        trie.add(string("tree1"), t1);
        trie.add(string("tree2"), t2);

        REQUIRE(!t1);
        REQUIRE(!t2);

        Tree* resultT1 = trie.search(string("tree1"));
        Tree* resultT2 = trie.search(string("tree2"));

        REQUIRE(resultT1);
        REQUIRE(resultT2);

        trie.clear();

        Tree* resultT3 = trie.search(string("tree1"));
        Tree* resultT4 = trie.search(string("tree2"));
        Tree* resultT5 = trie.search(string("name"));


        REQUIRE(!resultT3);
        REQUIRE(!resultT4);
        REQUIRE(!resultT5);
    }
}

#pragma clang diagnostic pop
