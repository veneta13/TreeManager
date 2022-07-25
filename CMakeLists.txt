cmake_minimum_required(VERSION 3.22)
project(TreeManager)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        main
        source/main.cpp
        source/trie.cpp
        source/tree.cpp source/tree.h)
