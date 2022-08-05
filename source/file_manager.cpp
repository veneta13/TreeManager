#include "file_manager.h"

/// Default constructor
FileManager::FileManager() = default;


/// Destructor
FileManager::~FileManager() = default;


/// Read tree from file
/// \param file name of the file to read from
/// \param tree tree to update
void FileManager::readFile(std::ostream& out, const string& file, Tree* tree) {
    ifstream readFile(file.c_str());
    if (readFile.bad()) {
        throw std::runtime_error("Cannot read file\n");
    }

    readFile >> *tree;
    out << "Tree read from " << file.c_str() << "\n";

    readFile.close();
}


/// Write tree to file
/// \param file name of the file to write to
/// \param tree tree to update
void FileManager::writeFile(std::ostream& out, std::istream& in, const string& file, Tree* tree) {
    ifstream exists(file.c_str());
    if (exists.good()) {
        out << "File already exists.\nOverwrite existing file? y/n\n";
        char input;
        in >> input;
        if (input != 'y') {
            out << "Writing to file cancelled.\n";
            return;
        }
    }
    out << "Writing to file " << file.c_str() << "\n";

    ofstream writeFile;
    writeFile.open (file.c_str(), std::ios::out);

    if (writeFile.bad()) {
        throw std::runtime_error("File cannot be created.\n");
    }

    writeFile << *tree;
    out << "Tree saved in file " << file.c_str() << "\n";

    writeFile.close();
}
