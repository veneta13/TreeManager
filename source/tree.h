#ifndef TREEMANAGER_TREE_H
#define TREEMANAGER_TREE_H

#include <algorithm>
#include <vector>
#include <iostream>

using std::vector;

/// Represents a tree
class Tree {
    /// Represents a node in the tree
    struct Node {
        /// The integer saved in the node
        int value;

        /// Children nodes
        vector<Node*> children;

        /// Default constructor
        Node() = default;

        bool operator<(Node const& other) const;
        bool operator>(Node const& other) const;
        bool operator==(Node const& other) const;
    };

    /// The root of the tree
    Node* root;

    void clear(Node* currentRoot);
    Node* getChild(Node* parent, int value) const;

    friend bool helperSort(Node* a, Node* b);
    void sortChildren(Node* currentRoot);

    bool equalSubtrees(const Node* rootA, const Node* rootB);

public:
    Tree();
    Tree(Tree const& other) = delete;
    Tree& operator=(Tree const& other) = delete;
    ~Tree();

    void read(std::istream& in);

    void containsSubtree(const Tree* subtree) const;
    void removeSubtree(const Tree* subtree);
};


#endif //TREEMANAGER_TREE_H
