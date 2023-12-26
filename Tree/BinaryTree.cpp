#include <iostream>
#include <vector>
#include <queue>

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
    //void createBinTree_Pre(char in[], TreeNode *&subtree, int n);
    void PreOrder(TreeNode *subtree);
    void InOrder(TreeNode *subtree);
    void PostOrder(TreeNode *subtree);
    void printBinTree(TreeNode *subtree);
    void Traverse(TreeNode *subtree, int k);

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { destroy(root); }
    bool isEmpty() { return root == nullptr; }
    int Height() { return Height(root); }
    int Size() { return Size(root); }
    void createBinTree(char in[]) { createBinTree(in, root); }
    //void createBinTree_Pre(char in[]) { createBinTree_Pre(in, root, 0); }
    void printBinTree() { printBinTree(root); }
    void Traverse() { Traverse(root, 1); }
    void PreOrder() { PreOrder(root); }
    void InOrder() { InOrder(root); }
    void PostOrder() { PostOrder(root); }
    void LevelOrder();
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

/*void BinaryTree::createBinTree_Pre(char in[], TreeNode *&subtree, int n) {
    char ch = in[n++];
    if (ch == ';')
        return;
    if (ch != '#') {
        subtree = new TreeNode(ch);
        createBinTree_Pre(in, subtree->left_child, n);
        createBinTree_Pre(in, subtree->right_child, n);
    }
    else
        subtree = nullptr;
}*/

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

void BinaryTree::Traverse(TreeNode* subtree, int k) {
    for (int i = 0; i < 5 * (k - 1); i++)
        cout << ' ';
    if (subtree != nullptr) {
        cout << subtree->value << endl;
        Traverse(subtree->left_child, k + 1);
        Traverse(subtree->right_child, k + 1);
    }
    else
        cout << '#' << endl;
}

void BinaryTree::PreOrder(TreeNode* subtree) {
    if (subtree != nullptr) {
        cout << subtree->value;
        PreOrder(subtree->left_child);
        PreOrder(subtree->right_child);
    }
}

void BinaryTree::InOrder(TreeNode* subtree) {
    if (subtree != nullptr) {
        InOrder(subtree->left_child);
        cout << subtree->value;
        InOrder(subtree->right_child);
    }
}

void BinaryTree::PostOrder(TreeNode* subtree) {
    if (subtree != nullptr) {
        PostOrder(subtree->left_child);
        PostOrder(subtree->right_child);
        cout << subtree->value;
    }
}

void BinaryTree::LevelOrder() {
    if (root == nullptr)
        return;
    queue<TreeNode*> Q;
    TreeNode* p = root;
    Q.push(p);
    while (!Q.empty()) {
        p = Q.front();
        Q.pop();
        cout << p->value;
        if (p->left_child != nullptr)
            Q.push(p->left_child);
        if (p->right_child != nullptr)
            Q.push(p->right_child);
    }
}

int main() {
    char in[] = {'A','(', 'B', '(', 'D', ',', 'E', '(', 'G', ',', ')', ')', ',', 'C', '(', ',', 'F', ')', ')', '#'};
    //char pre[] = {'A', 'B', 'C', '#', '#', 'D', 'E', '#', 'G', '#', '#', 'F', '#', '#', '#'};
    BinaryTree tree;//, tree_pre;
    tree.createBinTree(in);
    //tree_pre.createBinTree_Pre(pre);
    tree.PreOrder();
    cout << endl;
    //tree_pre.PreOrder();
    //cout << endl;
    tree.printBinTree();    
    cout << endl;
    tree.Traverse();
}