#include "FileManager.h"

/// Default constructor
FileManager::FileManager() = default;


/// Destructor
FileManager::~FileManager() = default;


/// Read tree from file
/// \param file name of the file to read from
/// \param tree tree to update
void FileManager::readFile(const string& file, Tree* tree) {
    ifstream readFile(file.c_str());
    if (readFile.bad()) {
        throw std::runtime_error("Cannot read file\n");
    }

    readFile >> *tree;
    std::cout << "Tree read from " << file.c_str() << "\n";
}


/// Write tree to file
/// \param file name of the file to write to
/// \param tree tree to update
void FileManager::writeFile(const string& file, Tree* tree) {
    ifstream exists(file.c_str());
    if (exists.good()) {
        std::cout << "File already exists.\nOverwrite existing file? y/n\n";
        char input;
        std::cin >> input;
        if (input != 'y') {
            std::cout << "Writing to file cancelled.\n";
            return;
        }
    }
    std::cout << "Writing to file " << file.c_str() << "\n";

    ofstream writeFile;
    writeFile.open (file.c_str(), std::ios::out);

    if (writeFile.bad()) {
        throw std::runtime_error("File cannot be created.\n");
    }

    writeFile << *tree;
    std::cout << "Tree saved in file " << file.c_str() << "\n";
}
