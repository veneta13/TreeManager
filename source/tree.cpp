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
    root = nullptr;
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
Tree::Node* Tree::getChildBinarySearch(Tree::Node *parent, int value) const {
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


/// Linear search for value among children of node
/// \param parent parent node to search in
/// \param value value to search for
/// \return pointer to the child with that value
Tree::Node* Tree::getChildLinearSearch(Tree::Node *parent, int value) const {
    if (!parent) {
        return nullptr;
    }

    for (int i = 0; i < parent->children.size(); i++) {
        if (parent->children[i]->value == value) {
            return parent->children[i];
        }
    }

    return nullptr;
}


/// Add child to parent node
/// \param parent parent to add new value under
/// \param value child value to add
void Tree::addChild(Tree::Node* parent, int value) const {
    if (!getChildLinearSearch(parent, value)) {
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


/// Move to children of current nodes
/// \param nodes current nodes
void Tree::moveToNextLevel(vector<Node*>& nodes) const {
    vector<Node*> temp;

    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes[i]->children.size(); j++) {
            temp.push_back(nodes[i]->children[j]);
        }
    }

    nodes = temp;
}


/// Read and move reading to next nodes' children
/// \param in stream to read from
/// \param nodes vector to update with next nodes
void Tree::readLineAndUpdate(std::istream& in, vector<Node*>& nodes) const {
    readLine(in, nodes); // read child nodes of parents
    moveToNextLevel(nodes);
}


/// Reads information for all nodes on a level and saves them
/// \param in stream to read from
/// \param parents parent nodes
void Tree::readLine(std::istream& in, vector<Node*>& parents) const {
    char c = ' ';
    while ( c == ' ') {
        c = (char)(in.get());
    }
    if(in.eof()) {
        return;
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


/// Print children of node
/// \param out output stream
/// \param parent parent of the nodes to print
/// \return if the node has any children
bool Tree::printChildren(std::ostream &out, Node* parent) const {
    for (int i = 0; i < parent->children.size(); i++) {
        out << " " << parent->children[i]->value;
    }
    out << " |";

    return parent->children.empty();
}


/// Print tree level
/// \param out output stream
/// \param nodes nodes on the current level
/// \return if there are any more levels under this one
bool Tree::printLevel(std::ostream &out, vector<Node *>& nodes) const {
    bool nextLine = false;

    out << "|";
    for (int i = 0; i < nodes.size(); i++) {
        if (!printChildren(out, nodes[i])) {
            nextLine = true;
        }
    }
    out << "\n";

    moveToNextLevel(nodes);

    return nextLine;
}


/// Check if the searched for subtree begins at the current node
/// \param currentRoot current node in tree
/// \param otherRoot root of subtree
/// \return if the searched for subtree begins at the current node
bool Tree::equalSubtrees(const Node* currentRoot, const Node* otherRoot) {
    if ((!currentRoot && !otherRoot) || !otherRoot) {
        return true;
    }
    if (!currentRoot) {
        return false;
    }
    if (currentRoot->value != otherRoot->value) {
        return false;
    }

    // TODO can be optimised for sorted arrays
    bool found = true;
    for (int i = 0; i < otherRoot->children.size(); i++) {
        found = false;

        for (int j = 0; j < currentRoot->children.size(); j++) {
            if (equalSubtrees(currentRoot->children[j], otherRoot->children[i])) {
                found = true;
                break;
            }
        }
        if (!found) { break; }
    }

    return found;
}


/// Find subtree in current tree
/// \param currentRoot root of tree to search in
/// \param rootToFind root of tree to search for
/// \return root of subtree
Tree::Node * Tree::findSubtree(Node* currentRoot, Node* rootToFind) {
    if (!rootToFind || !currentRoot) { return nullptr; }

    // TODO sort for faster operations

    Node* subtreeRoot; // root of found subtree

    for (int i = 0; i < currentRoot->children.size(); i++) {
        subtreeRoot = findSubtree(currentRoot->children[i], rootToFind);
        if (subtreeRoot) {
            return subtreeRoot;
        }
    }

    if (equalSubtrees(currentRoot, rootToFind)) {
        return currentRoot;
    }

    return nullptr;
}


/// Helper for subtree operations
/// \param remove if the found subtrees must be removed
/// \param subtree tree to search for
/// \return if any such subtrees were found
bool Tree::helperSubtree(bool remove, const Tree* subtree) {
    if (!subtree->root) { return true; }

    Node* inner = findSubtree(root, subtree->root);

    if (!remove) {
        return inner != nullptr;
    }

    return true;
}


/// Check if current tree contains a subtree
/// \param out output stream to print the result in
/// \param subtree tree to search for
void Tree::containsSubtree(std::ostream &out, Tree *subtree) {
    if (helperSubtree(false, subtree)) {
        out << "Yes, there is such subtree!\n";
        return;
    }
    out << "No, such subtree does not exist!\n";
}


/// Stream extraction operator
/// \param in input stream
/// \param t tree to input
/// \return updated input stream
std::istream &operator>>(std::istream &in, Tree& t) {
    vector<Tree::Node*> nodes;

    if (!t.root) {
         t.root = new Tree::Node();
    }
    nodes.push_back(t.root);

    while(!in.eof()) {
        t.readLineAndUpdate(in, nodes);
    }

    // update root
    Tree::Node* temp = t.root;
    t.root = t.root->children[0];
    t.root->parent = nullptr;
    delete temp;

    return in;
}


/// Stream insertion operator
/// \param out output stream
/// \param w tree to output
/// \return the stream with table information inserted
std::ostream &operator<<(std::ostream &out, Tree const& t) {
    vector<Tree::Node*> nodes;
    nodes.push_back(t.root);

    out << "| " << t.root->value << " |\n";
    while (t.printLevel(out, nodes)) ;
    return out;
}

