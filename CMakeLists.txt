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
        source/executor.cpp
        source/file_manager.cpp
)

add_executable(
        tree-tests
        tests/test-tree.cpp
        source/tree.cpp
)

add_executable(
        trie-tests
        tests/test-trie.cpp
        source/trie.cpp
        source/tree.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
