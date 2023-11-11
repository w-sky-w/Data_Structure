#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    char value;
    TreeNode *left_child;
    TreeNode *right_child;
    TreeNode(): left_child(nullptr), right_child(nullptr) {}
    TreeNode(char _val, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : value(_val), left_child(l), right_child(r) {}
};

class BinaryTree {
protected:
    TreeNode* root;
    void destroy(TreeNode*& subtree);
    int Height(TreeNode *subtree);
    int Size(TreeNode *subtree);
    void createBinTree(char in[], TreeNode *&subtree);
    void PreOrder(TreeNode *subtree);
    void printBinTree(TreeNode *subtree);

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { destroy(root); }
    bool isEmpty() { return root == nullptr; }
    int Height() { return Height(root); }
    int Size() { return Size(root); }
    void createBinTree(char in[]) { createBinTree(in, root); }
    void printBinTree() { printBinTree(root); }
    void PreOrder() { PreOrder(root); }
};

void BinaryTree::destroy(TreeNode*& subtree) {
    if (subtree != nullptr) {
        destroy(subtree->left_child);
        destroy(subtree->right_child);
        delete subtree;
        subtree = nullptr;
    }
}

int BinaryTree::Height(TreeNode* subtree) {
    if (subtree == nullptr)
        return 0;
    else {
        int i = Height(subtree->left_child);
        int j = Height(subtree->right_child);
        return (i < j) ? j + 1 : i + 1;
    }
}

int BinaryTree::Size(TreeNode* subtree) {
    if (subtree == nullptr)
        return 0;
    else {
        return 1 + Size(subtree->left_child) + Size(subtree->right_child);
    }
}

void BinaryTree::createBinTree(char in[], TreeNode*& BT) {
    //input example: A(B(D,E(G,)),C(,F))#
    vector<TreeNode*> S(20);
    int top = -1;
    TreeNode *p, *t;
    int k = 0, flag;//flag marks the left or right subtree
    char ch;
    BT = nullptr;
    ch = in[k++];
    while (ch != '#') {
        switch (ch) {
            case '(': 
                S[++top] = p;
                flag = 1;
                break;
            case ')':
                t = S[--top];
                break;
            case ',':
                flag = 2;
                break;
            default:
                p = new TreeNode(ch);
                if (BT == nullptr)
                    BT = p;
                else {
                    t = S[top];
                    if (flag == 1)
                        t->left_child = p;
                    else
                        t->right_child = p;
                }
        }
        ch = in[k++];
    }
}

void BinaryTree::printBinTree(TreeNode* subtree) {
    if (subtree != nullptr) {
        cout << subtree->value;
        if (subtree->left_child != nullptr || subtree->right_child != nullptr) {
                cout << '(';
                printBinTree(subtree->left_child);
                cout << ',';
                if (subtree->right_child != nullptr)
                    printBinTree(subtree->right_child);
                cout << ')';
        }
    }
}

void BinaryTree::PreOrder(TreeNode* subtree) {
    if (subtree != nullptr) {
        cout << subtree->value;
        PreOrder(subtree->left_child);
        PreOrder(subtree->right_child);
    }
}

int main() {
    char in[] = {'A','(', 'B', '(', 'D', ',', 'E', '(', 'G', ',', ')', ')', ',', 'C', '(', ',', 'F', ')', ')', '#'};
    BinaryTree tree;
    tree.createBinTree(in);
    tree.PreOrder();
    tree.printBinTree();
}