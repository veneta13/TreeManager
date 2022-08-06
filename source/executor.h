#ifndef TREEMANAGER_EXECUTOR_H
#define TREEMANAGER_EXECUTOR_H

#include "trie.h"
#include "file_manager.h"

/// User interface provider
class Executor {

    /// Trie of trees
    Trie* trie;

    /// File reader and writer
    FileManager* fileManager;

    void tokenize(string& command, std::vector<string>& tokens);

    bool commandPicker(std::vector<string>& tokens, std::ostream &out, std::istream &in);
    void load(std::vector<string>& tokens, std::ostream &out);
    void save(std::vector<string>& tokens, std::ostream &out, std::istream &in);
    void contains(std::vector<string>& tokens, std::ostream &out);
    void remove(std::vector<string>& tokens, std::ostream &out);

public:
    Executor();
    Executor(Executor const& other) = delete ;
    Executor& operator=(Executor const& other) = delete;
    ~Executor();

    void enter(std::ostream& out, std::istream& in);
};


#endif
