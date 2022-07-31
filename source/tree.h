#ifndef TREEMANAGER_TREE_H
#define TREEMANAGER_TREE_H

#include <iostream>
#include <string>
#include <cstring>
#include <exception>
#include <algorithm>
#include <vector>


using std::vector;

/// Represents a tree
class Tree {
public: // TODO remove line
    /// Represents a node in the tree
    struct Node {
        /// The integer saved in the node
        int value;

        /// Children nodes
        vector<Node*> children;

        /// Parent node
        Node* parent;

        Node();
        Node(int _value);

        bool operator<(Node const& other) const;
        bool operator>(Node const& other) const;
        bool operator==(Node const& other) const;
    };

    /// The root of the tree
    Node* root;

    void clear(Node* currentRoot);
    Node* getChild(Node* parent, int value) const;
    void addChild(Node* parent, int value);

    friend bool helperSort(Node* a, Node* b);
    void sortChildren(Node* currentRoot);

    bool equalSubtrees(const Node* rootA, const Node* rootB);

    int readInteger(std::istream &in) const;
    void readChildren(std::istream& in, Node* parent);
    void readLine(std::istream &in, vector<Node *> &parents);
    void readLineAndUpdate(std::istream &in, vector<Node *> &nodes);

public:
    Tree();
    Tree(int _root);
    Tree(Tree const& other) = delete;
    Tree& operator=(Tree const& other) = delete;
    ~Tree();

    void read(std::istream& in);

    void containsSubtree(const Tree* subtree) const;
    void removeSubtree(const Tree* subtree);
};


#endif //TREEMANAGER_TREE_H
