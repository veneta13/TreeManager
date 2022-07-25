#ifndef TREEMANAGER_TRIE_H
#define TREEMANAGER_TRIE_H

#define TRIE_KEY_COUNT 128

#include <string>

using std::string;

/// Represents a trie
class Trie {

    /// Represents a node in the trie
    struct Node {
        Node *keys[TRIE_KEY_COUNT];
        bool exists;

        Node();
    };

    Node *root; // Root node of the trie

    void clearSubtree(Node *currentRoot);
    int getKey(char c);

public:
    Trie();
    Trie(Trie const&) = delete;
    Trie& operator=(Trie const&) = delete;
    ~Trie();

    bool add(const string& name);
    bool search(const string& name);
    void clear();
};


#endif
