#ifndef BST_H
#define BST_H

#include <iostream>
#include <iomanip>
#include <functional>
#include <queue>


class BST
{
public:
    class Node
    {
        public:
            Node(int value, Node* left, Node* right);
            Node();
            Node(const Node& node);

            int value;
            Node* left;
            Node* right;
    };

private:
    Node* root;

public:
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    BST& operator++();
    const BST operator++(int);
    ~BST();
    BST();
    BST(const BST&);
    BST(BST&&);
    BST(const std::initializer_list<int>& );
    BST& operator=(const BST&);
    BST& operator=(BST&&);

};

std::ostream& operator << (std::ostream& out, const BST::Node& node);
bool operator > (const BST::Node& node, int num);
bool operator > (int num, const BST::Node& node);
bool operator < (const BST::Node& node, int num);
bool operator < (int num, const BST::Node& node);
bool operator >= (const BST::Node& node, int num);
bool operator >= (int num, const BST::Node& node);
bool operator <= (const BST::Node& node, int num);
bool operator <= (int num, const BST::Node& node);
bool operator == (const BST::Node& node, int num);
bool operator == (int num, const BST::Node& node);
std::ostream& operator<<(std::ostream& out, BST& bst);

#endif //BST_H