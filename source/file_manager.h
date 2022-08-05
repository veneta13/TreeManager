#ifndef TREEMANAGER_FILE_MANAGER_H
#define TREEMANAGER_FILE_MANAGER_H

#include <iostream>
#include <fstream>
#include <string>

#include "tree.h"

using std::string;
using std::ifstream;
using std::ofstream;


/// Read and write from files
struct FileManager {
    FileManager();
    FileManager(FileManager const& other) = delete;
    FileManager& operator=(FileManager const& other) = delete;
    ~FileManager();

    void readFile(string const &file, Tree *tree);
    void writeFile(string const &file, Tree *tree);
};


#endif
