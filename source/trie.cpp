#include "trie.h"


/// Default constructor
Trie::Node::Node() : tree(nullptr) {
    for (int i = 0; i < TRIE_KEY_COUNT; i++) {
        keys[i] = nullptr;
    }
}


/// Destructor
Trie::Node::~Node() {
    delete tree;
    tree = nullptr;
}


/// Default constructor
Trie::Trie() {
    root = new Node();
}


/// Destructor
Trie::~Trie() {
    clearSubtree(root);
}


/// Delete a subtree
/// \param currentRoot the root node of the subtree
void Trie::clearSubtree(Node *currentRoot) {
    if (!currentRoot) {
        return;
    }

    for (int i = 0; i < TRIE_KEY_COUNT; i++) {
        if (currentRoot->keys[i]) {
            clearSubtree(currentRoot->keys[i]);
        }
    }

    delete currentRoot;
    currentRoot = nullptr;
}


/// Get index of the current symbol
/// \param c symbol to get key from
/// \return key index
int Trie::getKey(char c) {
    return (int)(c);
}


/// Add a word to the trie
/// \param name of the tree to add
/// \param tree pointer to the tree to add
/// \return if the word was added successfully
bool Trie::add(const string& name, Tree* tree) {
    if (!root) {
        root = new Node();
    }

    int currentKey;
    Node* currentNode = root;

    for (int i = 0; i < name.size(); i++) {
        currentKey = getKey(name[i]);

        if (!currentNode->keys[currentKey]) {
            currentNode->keys[currentKey] = new Node();
        }

        currentNode = currentNode->keys[currentKey];
    }

    delete currentNode->tree; // if there was another tree remove it
    currentNode->tree = tree;

    return true;
}


/// Search for tree in trie
/// \param name name to search for
/// \return pointer to the tree
Tree* Trie::search(const string& name) {
    if (!root) {
        return nullptr;
    }

    int currentKey;
    Node* currentNode = root;

    for (size_t i = 0; i < name.size(); i++) {
        currentKey = getKey(name[i]);

        if (!currentNode->keys[currentKey]) {
            return nullptr;
        }

        currentNode = currentNode->keys[currentKey];
    }

    return currentNode->tree;
}


/// Clear all nodes of the trie
void Trie::clear() {
    clearSubtree(root);
    root = nullptr;
}
