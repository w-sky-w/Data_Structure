#include <queue>

template<class T>
void print_tree(TreeNode<T>* subtree) {
    if (subtree != nullptr) {
        cout << subtree->data;
        if (subtree->left_child != nullptr || subtree->right_child != nullptr) {
            cout << '(';
            print_tree(subtree->left_child);
            if (subtree->right_child != nullptr)
                cout << ',';
            print_tree(subtree->right_child);
            cout << ')';
        }
    }
}

template<class T>
TreeNode<T>* createBinTree(T* LVR, T* LRV, int n) {
    if (n == 0)
        return nullptr;
    int k = 0;
    while (LRV[n - 1] != LVR[k])
        k++;
    TreeNode<T> *t = new TreeNode<T>(LRV[n - 1]);
    t->left_child = createBinTree(LVR, LRV, k);
    t->right_child = createBinTree(LVR + k + 1, LRV + k, n - k - 1);
    return t;
};

template<class T>
void print_leaf(TreeNode<T>* root) {
    queue<pair<int, TreeNode<T>*>> Q;
    TreeNode<T>* p = root;
    pair<int, TreeNode<T>*> current_pair(1, p);
    Q.push(current_pair);
    while (!Q.empty()) {
        current_pair = Q.front();
        Q.pop();
        if (current_pair.second->left_child == nullptr
            && current_pair.second->right_child == nullptr)
            cout << "level " << current_pair.first << ": " << current_pair.second->value << endl;
        else {
            if (current_pair.second->left_child != nullptr) {
                pair<int, TreeNode<T>*> left(current_pair.first + 1, current_pair.second->left_child);
                Q.push(left);
            }
            if (current_pair.second->right_child != nullptr) {
                pair<int, TreeNode<T>*> right(current_pair.first + 1, current_pair.second->right_child);
                Q.push(right);
            }
        }
    }
};

struct TreeNode {
    int value;
    TreeNode* child;
    TreeNode* sibling;
    TreeNode(int val) : value(val), child(nullptr), sibling(nullptr) {}
};

int max(int a, int b) {
    return a > b ? a : b;
}

int count_leaf(TreeNode* root) {
    if (root == nullptr)
        return 0;
    if (root->child == nullptr)
        return 1;
    int count = 0;
    TreeNode* subtree = root->child;
    while (subtree != nullptr) {
        count += count_leaf(subtree);
        subtree = subtree->sibling;
    }
    return count;
}

int degree(TreeNode* root) {
    if (root == nullptr)
        return 0;
    int degree_of_root = 0;
    TreeNode* subtree = root->child;
    while (subtree != nullptr) {
        degree_of_root++;
        subtree = subtree->sibling;
    }
    int degree_of_child = degree(root->child);
    int degree_of_sibling = degree(root->sibling);
    return max(degree_of_root, max(degree_of_child, degree_of_sibling));
}

int height(TreeNode* root) {
    if (root == nullptr)
        return 0;
    int height_of_child = 1 + height(root->child);
    int height_of_sibling = height(root->sibling);
    return max(height_of_child, height_of_sibling);
}

struct HFNode {
	char data;
	int weight;
	int lchild, rchild;
	HFNode():data('#'), weight(0), lchild(-1), rchild(-1) {}
	HFNode(char c, int w) : data(c), weight(w), lchild(-1), rchild(-1) {}
};

struct HFTree {
	HFNode elem[40];
	int num;//权值个数
	int root;//根
	HFTree():num(0), root(0){}
};

HFTree createHuffmanTree(char data[], int weight[]) {
	HFTree HuffmanTree;
	HuffmanTree.num = sizeof(data) / sizeof(data[0]);
	if (HuffmanTree.num == 1) {
		HFNode node(data[0], weight[0]);
		HuffmanTree.elem[0] = node;
		HuffmanTree.root = 0;
		return HuffmanTree;
	}
	Heap<HFNode> minheap;
	for (int i = 0; i < HuffmanTree.num; i++) {
		HFNode node(data[i], weight[i]);
		HuffmanTree.elem[i] = node;
		minheap.insert(node);
	}
	while (minheap.size() > 1) {
		HFNode node1 = minheap.top();
		int point1 = minheap.elem[0].id;
		minheap.pop();
		HFNode node2 = minheap.top();
		int point2 = minheap.elem[0].id;
		minheap.pop();
		HFNode newNode('#', node1.weight + node2.weight);
		newNode.lchild = point1;
		newNode.rchild = point2;
		minheap.insert(newNode);
	}
	HuffmanTree.root = minheap.top();
	return HuffmanTree;
}