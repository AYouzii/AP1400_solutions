#include "bst.h"

BST::Node::Node(int value, Node* left, Node* right)
    : value(value), left(left), right(right) {}

BST::Node::Node(const Node& node)
    : value(node.value), left(node.left), right(node.right) {}

BST::Node::Node()
    : value(0), left(nullptr), right(nullptr) {}

std::ostream& operator<<(std::ostream& out, const BST::Node& node)
{
    out << std::setw(15) << std::setiosflags(std::ios::left) << &node << "=>" <<
        " value:" << std::setw(15) << node.value <<
        " left:" << std::setw(15) << node.left <<
        " right:" << node.right; 
    return out;
}

bool operator > (const BST::Node& node, int num)
{
    return node.value > num;
}

bool operator > (int num, const BST::Node& node)
{
    return num > node.value;
}

bool operator < (const BST::Node& node, int num)
{
    return node.value < num;
}

bool operator < (int num, const BST::Node& node)
{
    return num < node.value;
}

bool operator >= (const BST::Node& node, int num)
{
    return node.value >= num;
}

bool operator >= (int num, const BST::Node& node)
{
    return num >= node.value;
}

bool operator <= (const BST::Node& node, int num)
{
    return node.value <= num;
}

bool operator <= (int num, const BST::Node& node)
{
    return num <= node.value;
}

bool operator == (const BST::Node& node, int num)
{
    return node.value == num;
}

bool operator == (int num, const BST::Node& node)
{
    return num == node.value;
}

BST::Node*& BST::get_root()
{
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func)
{
    if (! root) {
        return;
    }
    std::queue<Node*> node_queue;
    node_queue.push(root);
    while (! node_queue.empty()) {
        Node* curr_node = node_queue.front();
        func(curr_node);
        if (curr_node->left) {
            node_queue.push(curr_node->left);
        }
        if (curr_node->right) {
            node_queue.push(curr_node->right);
        }
        node_queue.pop();
    }

}

size_t BST::length()
{
    size_t count = 0;
    auto count_nodes = [&count] (Node*& root) {++count;};
    bfs(count_nodes);
    return count;
}

bool BST::add_node(int value)
{
    bool value_already_exsits = false;
    std::function<void(Node*&)> func_add_node = [value, &value_already_exsits, &func_add_node] (Node*& root) {
        if (! root) {
            root = new Node(value, nullptr, nullptr);
            return;
        }
        if (value == root->value) {
            value_already_exsits = true;
            return;
        }

        if (value < root->value) {
            if (root->left) {
                func_add_node(root->left);
            }
            else {
                root->left = new Node(value, nullptr, nullptr);
                return;
            }
        }
        else {
            if (root->right) {
                func_add_node(root->right);
            }
            else {
                root->right = new Node(value, nullptr, nullptr);
                return;
            }
        }
    };
    func_add_node(root);
    if (value_already_exsits) {
        return false;
    }
    else {
        return true;
    }
}

BST::Node** BST::find_node(int value)
{
    std::function<Node**(Node*&)> recursion_find_node = [value, &recursion_find_node] (Node*& root) -> Node** {
        if (! root) {
            return nullptr;
        }
        else {
            if (root->value == value) {
                return &root;
            }
            else if (root->value > value) {
                return recursion_find_node(root->left);
            }
            else if (root->value < value) {
                return recursion_find_node(root->right);
            }
        }
    };
    return recursion_find_node(root);
}

BST::Node** BST::find_parrent(int value)
{
    std::function<Node**(Node*&, Node*&)> recursion_find_parent = [value, &recursion_find_parent] (Node*& root, Node*& parent) -> Node** {
        if (! root) {
            return nullptr;
        }
        else {
            if (root->value == value) {
                return &parent;
            }
            else if (root->value > value) {
                return recursion_find_parent(root->left, root);
            }
            else if (root->value < value) {
                return recursion_find_parent(root->right, root);
            }
        }
    };
    return recursion_find_parent(root, root);
}

BST::Node** BST::find_successor(int value)
{
    // Maybe the author meant to find *PREDECESSOR*?
    std::vector<Node**> nodes;
    std::function<void(Node*& root)> inorder = [&] (Node*& root) {
        if (! root) {
            return;
        }
        else {
            if (root->left) {
                inorder(root->left);
            }
            nodes.push_back(&root);
            if (root->right) {
                inorder(root->right);
            }
        }

    };
    inorder(root);
    for (unsigned i = 0; i < nodes.size(); ++i) {
        if ((*nodes[i])->value == value) {
            if (i == 0) 
                return nullptr;
            else 
                return nodes[i-1];
        }
    }
    return nullptr;
}

bool BST::delete_node(int value)
{
    Node** node_to_delete = find_node(value);
    if (! node_to_delete) {
        // not found
        return false;
    }
    // leaf node
    if ((*node_to_delete)->right == nullptr && (*node_to_delete)->left == nullptr) {
        delete *node_to_delete;
        *node_to_delete = nullptr;
        return true;
    }
    else if ((*node_to_delete)->left == nullptr && (*node_to_delete)->right != nullptr) {
        // only right child
        Node* temp = *node_to_delete;
        *node_to_delete = (*node_to_delete)->right;
        delete temp;
        temp = nullptr;
    }
    else if ((*node_to_delete)->left != nullptr && (*node_to_delete)->right == nullptr) {
        // only left child
        Node* temp = *node_to_delete;
        *node_to_delete = (*node_to_delete)->left;
        delete temp;
        temp = nullptr;
    }
    else {
        // both left child and right child exist
        // find the predecessor of current node
        // since both left child and right child exist, the predecessor can not be nullptr
        Node** predecessor = find_successor(value);
        int new_value = (*predecessor)->value;
        delete_node((*predecessor)->value);
        (*node_to_delete)->value = new_value;
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, BST& bst)
{
    std::string stars(80, '*');
    out << stars << '\n';
    bst.bfs([&out] (BST::Node*& node) {out << *node << '\n';});
    out << "binary search tree size: " << bst.length() << '\n';
    out << stars << '\n';
    return out;
}

BST& BST::operator++()
{
    bfs([] (Node*& node) {++(node->value);});
    return *this;
}

const BST BST::operator++(int)
{
    const BST curr_bst = BST(*this);
    bfs([] (Node*& node) {++(node->value);});
    return curr_bst;    
}

BST::~BST()
{
    std::vector<Node*> nodes;
	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
	for(auto node: nodes)
		delete node;
}

BST::BST()
    : root(nullptr) {}

BST::BST(const BST& bst)
{
    // deep copy
    std::function<Node*(const Node*)> copy_tree = [&copy_tree] (const Node* root) {
        if (! root) {
            return static_cast<Node*>(nullptr);
        }
        Node* ltree = copy_tree(root->left);
        Node* rtree = copy_tree(root->right);

        Node* new_tree = new Node(root->value, ltree, rtree);
        return new_tree;
    };
    root = copy_tree(bst.root);
}

BST::BST(BST&& bst)
{
    root = bst.root;
    bst.root = nullptr;
}

BST& BST::operator=(const BST& bst)
{
    if (bst.root == root) {
        return *this;
    }

    // step 1, delete original tree
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
    for(auto node: nodes)
        delete node;
    std::vector<Node*> ().swap(nodes);

    // step 2, copy tree
    std::function<Node*(const Node*)> copy_tree = [&copy_tree] (const Node* root) {
        if (! root) {
            return static_cast<Node*>(nullptr);
        }
        Node* ltree = copy_tree(root->left);
        Node* rtree = copy_tree(root->right);

        Node* new_tree = new Node(root->value, ltree, rtree);
        return new_tree;
    };
    root = copy_tree(bst.root);   
    return *this;
}

BST& BST::operator=(BST&& bst)
{
    root = bst.root;
    bst.root = nullptr;
    return *this;
}

BST::BST(const std::initializer_list<int>& lst)
{
    root = nullptr;
    for (int v : lst) {
        add_node(v);
    }
}