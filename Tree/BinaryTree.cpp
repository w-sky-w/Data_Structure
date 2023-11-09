#include <iostream>

using namespace std;

struct TreeNode {
    int value;
    TreeNode *left_child;
    TreeNode *right_child;
    TreeNode(): left_child(nullptr), right_child(nullptr) {}
    TreeNode(int _val, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : value(_val), left_child(l), right_child(r) {}
};

class BinaryTree {
private:
    
};