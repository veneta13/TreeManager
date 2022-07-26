cmake_minimum_required(VERSION 3.22)
project(TreeManager)

set(CMAKE_CXX_STANDARD 14)

include(CTest)
enable_testing()

add_executable(
        main
        source/main.cpp
        source/trie.cpp
        source/tree.cpp
)

add_executable(
        tests
        tests/test.cpp
        source/trie.cpp
        source/tree.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
