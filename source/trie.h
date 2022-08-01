#ifndef TREEMANAGER_TRIE_H
#define TREEMANAGER_TRIE_H

#define TRIE_KEY_COUNT 128

#include "tree.h"

using std::string;

/// Represents a trie
class Trie {

    /// Represents a node in the trie
    struct Node {

        /// ASCII symbol lookup table
        Node *keys[TRIE_KEY_COUNT];

        /// Pointer to tree with that name
        Tree* tree;

        Node();
        ~Node();
    };

    /// Root node of the trie
    Node *root;

    void clearSubtree(Node *currentRoot);
    int getKey(char c);

public:
    Trie();
    Trie(Trie const&) = delete;
    Trie& operator=(Trie const&) = delete;
    ~Trie();

    bool add(const string& name, Tree*& tree);
    Tree* search(const string& name);
    void clear();
};


#endif
