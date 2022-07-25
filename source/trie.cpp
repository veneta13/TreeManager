#include "trie.h"


/// Default constructor
Trie::Node::Node() {
    exists = false;

    for (int i = 0; i < TRIE_KEY_COUNT; i++) {
        keys[i] = nullptr;
    }
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
/// \param word word to add
/// \return if the word was added successfully
bool Trie::add(const string& word) {
    if (!root) {
        root = new Node();
    }

    int currentKey;
    Node* currentNode = root;

    for (int i = 0; i < word.size(); i++) {
        currentKey = getKey(word[i]);

        if (!currentNode->keys[currentKey]) {
            currentNode->keys[currentKey] = new Node();
        }

        currentNode = currentNode->keys[currentKey];
    }

    currentNode->exists = true;
    return true;
}


/// Search for name in trie
/// \param word name to search for
/// \return if tree with such name exists
bool Trie::search(const string& word) {
    if (!root) {
        return false;
    }

    int currentKey;
    Node* currentNode = root;

    for (size_t i = 0; i < word.size(); i++) {
        currentKey = getKey(word[i]);

        if (!currentNode->keys[currentKey]) {
            return false;
        }

        currentNode = currentNode->keys[currentKey];
    }

    return currentNode->exists;
}


/// Clear all nodes of the trie
void Trie::clear() {
    clearSubtree(root);
    root = nullptr;
}
