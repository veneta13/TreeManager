#include "executor.h"

/// Default constructor
Executor::Executor() {
    trie = new Trie();
    fileManager = new FileManager();
}


/// Destructor
Executor::~Executor() {
    delete trie;
    trie = nullptr;

    delete fileManager;
    fileManager = nullptr;
}


/// Tokenize user input
/// \param line user input line
/// \param tokens tokens extracted by line
void Executor::tokenize(string &line, vector<string> &tokens) {
    int beg = 0, end = 0;

    while ((end = line.find(' ', beg)) != std::string::npos) {
        tokens.push_back(line.substr(beg, end - beg));
        beg = end + 1;
    }

    tokens.push_back(line.substr(beg));
}


/// Picks which command to execute
/// \param line user command line
/// \param out user output stream
/// \param in user input stream
/// \return if the execution of the program should continue
bool Executor::commandPicker(std::vector<string>& tokens ,std::ostream &out, std::istream &in) {
    string command = tokens[0];
    tokens.erase(tokens.cbegin()); // remove command name from tokens

    if (command == "LOAD") {
        load(tokens, out);
    }
    else if (command == "SAVE") {
        save(tokens, out, in);
    }
    else if (command == "CONTAINS") {
        contains(tokens, out);
    }
    else if (command == "REMOVE") {
        remove(tokens, out);
    }
    else {
        return false;
    }

    return true;
}


/// Load tree from file
/// \param tokens filename and tree name
/// \param out user output stream
void Executor::load(std::vector<string>& tokens, std::ostream &out) {

    Tree* tree = new Tree();

    try {
        fileManager->readFile(out, tokens[1], tree);
        trie->add(tokens[0], tree);
    }
    catch (std::exception& e) {
        out << e.what() << "\n";
    }
    catch (...) {
        out << "Error has occurred!\n";
    }
}


/// Save tree in file
/// \param tokens filename and tree name
/// \param out user output stream
/// \param in user input stream
void Executor::save(std::vector<string>& tokens, std::ostream &out, std::istream &in) {
    try {
        Tree* tree = trie->search(tokens[0]);
        if (!tree) {
            out << "Tree with this name does not exist!\n";
            return;
        }

        fileManager->writeFile(out, in, tokens[1], tree);
    }
    catch (std::exception& e) {
        out << e.what() << "\n";
    }
    catch (...) {
        out << "Error has occurred!\n";
    }
}


/// Check if tree is a subtree of another
/// \param tokens names of the trees
/// \param out user output stream
void Executor::contains(std::vector<string>& tokens, std::ostream &out) {
    try {
        Tree* tree1 = trie->search(tokens[0]);
        Tree* tree2 = trie->search(tokens[1]);

        if (!tree1 || !tree2) {
            out << "Tree not found!\n";
            return;
        }

        tree1->containsSubtree(out, tree2);
    }
    catch (std::exception& e) {
        out << e.what() << "\n";
    }
    catch (...) {
        out << "Error has occurred!\n";
    }
}


/// Remove all occurrences of one tree in another
/// \param tokens names of the trees
/// \param out user output stream
void Executor::remove(std::vector<string>& tokens, std::ostream &out) {
    try {
        Tree* tree1 = trie->search(tokens[0]);
        Tree* tree2 = trie->search(tokens[1]);

        if (!tree1 || !tree2) {
            out << "Tree not found!\n";
            return;
        }

        tree1->removeSubtree(out, tree2);
    }
    catch (std::exception& e) {
        out << e.what() << "\n";
    }
    catch (...) {
        out << "Error has occurred!\n";
    }
}


/// Read user command
/// \param out user output stream
/// \param in user input stream
void Executor::enter(std::ostream &out, std::istream &in) {
    string line;
    std::vector<string> tokens;

    std::getline(in, line);
    tokenize(line, tokens);

    while (commandPicker(tokens, out, in)) {
        tokens.clear();
        std::getline(in, line);
        tokenize(line, tokens);
    }
}
