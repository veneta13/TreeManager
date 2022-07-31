#include "tree.h"

/// Default constructor
Tree::Node::Node() : value(0), parent(nullptr) {}


/// Constructor with value parameter
/// \param value value of the node
Tree::Node::Node(int _value) : value(_value), parent(nullptr) {}


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


/// Constructor with root value
/// \param _root value of root
Tree::Tree(int _root) {
    root = new Node(_root);
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


/// Add child to parent node
/// \param parent parent to add new value under
/// \param value child value to add
void Tree::addChild(Tree::Node* parent, int value) const {
    if (!getChild(parent, value)) {
        Node* node = new Node(value);
        node->parent = parent;
        parent->children.push_back(node);
    }
    else {
        throw std::invalid_argument("Child with such value already exists in the node!\n");
    }
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


/// Extract number from stream
/// \param in stream to read from
/// \return extracted number
int Tree::readInteger(std::istream& in) const {
    char c = ' ';

    while (c == ' ') {
        c = in.get();
    }

    bool neg = false;
    if (c == '-') {
        neg = true;
        c = in.get();
    }

    if (c == '|') {
        throw std::invalid_argument("End of children nodes reached");
    }

    if (!std::isdigit(c)) {
        throw std::invalid_argument("Reading node from file unsuccessful!\n");
    }

    int number = 0;
    while (std::isdigit(c)) {
        number *= 10;
        number += (c - '0');
        c = in.get();
    }

    number = neg ? number * (-1) : number;

    return number;
}

/// Read all children of a node
/// \param in stream to read from
/// \param parent parent node to add children to
void Tree::readChildren(std::istream& in, Node* parent) const {
    int current;

    while (true) {
        try {
            current = readInteger(in);
        }
        catch (std::invalid_argument& e) {
            if (strcmp(e.what(), "End of children nodes reached") == 0) {
                return;
            }
            throw e;
        }

        try {
            addChild(parent, current);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what();
            throw std::invalid_argument("The tree representation in the file is invalid!\n");
        }
    }
}


/// Read and move reading to next nodes' children
/// \param in stream to read from
/// \param nodes vector to update with next nodes
void Tree::readLineAndUpdate(std::istream& in, vector<Node*>& nodes) const {
    vector<Node*> temp;

    readLine(in, nodes); // read child nodes of parents

    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes[i]->children.size(); j++) {
            temp.push_back(nodes[i]->children[j]);
        }
    }

    nodes = temp;
}


/// Reads information for all nodes on a level and saves them
/// \param in stream to read from
/// \param parents parent nodes
void Tree::readLine(std::istream& in, vector<Node*>& parents) const {
    char c = ' ';
    while ( c == ' ') {
        c = (char)(in.get());
    }

    if (c != '|') {
        throw std::invalid_argument("The tree representation is not correct!\n");
    }
    else {
        in.ignore(); // the structure is correct and the | can be ignored
    }

    for (int i = 0; i < parents.size(); i++) {
        readChildren(in, parents[i]);
    }

    std::string str;
    getline(in, str); // move on to the next line
}

std::istream &operator>>(std::istream &in, Tree& t) {
    vector<Tree::Node*> nodes;
    nodes.push_back(t.root);

    while(!in.eof()) {
        t.readLineAndUpdate(in, nodes);
    }

    // update root
    Tree::Node* temp = t.root;
    t.root = t.root->children[0];
    t.root->parent = nullptr;
    delete temp;
}

