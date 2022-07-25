#include "tree.h"


/// Less than operator
/// \param other node to compare to
/// \return if the values of the node is less than the value of the other node
bool Tree::Node::operator<(Tree::Node const &other) const {
    return value < other.value;
}


/// Greater than operator
/// \param other node to compare to
/// \return if the values of the node is greater than the value of the other node
bool Tree::Node::operator>(Tree::Node const &other) const {
    return value > other.value;
}


/// Equal to operator
/// \param other node to compare to
/// \return if the values of the two nodes are the same
bool Tree::Node::operator==(Tree::Node const &other) const {
    return value == other.value;
}


/// Default constructor
Tree::Tree() {
    root = new Node();
}


/// Destructor
Tree::~Tree() {
    clear(root);
}


/// Clear subtree
/// \param currentRoot the root of the subtree
void Tree::clear(Node *currentRoot) {
    if (!currentRoot) {
        return;
    }

    for (int i = 0; i < currentRoot->children.size(); i++) {
        clear(currentRoot->children[i]);
    }

    delete currentRoot;
    currentRoot = nullptr;
}


/// Binary search for value among children of node
/// \param parent parent node to search in
/// \param value value to search for
/// \return pointer to the child with that value
Tree::Node* Tree::getChild(Tree::Node *parent, int value) const {
    if (!parent) {
        return nullptr;
    }

    int left = 0;
    int right = parent->children.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (parent->children[mid]->value == value) {
            return parent->children[mid];
        }

        if (parent->children[mid]->value < value) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return nullptr;
}


/// Helper for sortChildren function
/// \param a node to compare
/// \param b node to compare
/// \return if the value of b is less than the value of a
bool helperSort(Tree::Node* a, Tree::Node* b) {
    return b->value < a->value;
}


/// Sort children nodes to improve searching
/// \param currentRoot root to sort the children of
void Tree::sortChildren(Node *currentRoot) {
    std::sort(currentRoot->children.begin(),currentRoot->children.end(),&helperSort);
}
