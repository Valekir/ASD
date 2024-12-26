#include <iostream>
using namespace std;

template <typename T>
struct Less {
    bool operator()(const T& a, const T& b) {
        return a > b;
    }
};

template <typename T,typename Comparator>
class AVLTree {
 private:
    struct Node {
        T key;
        int height;
        int size;
        Node* left;
        Node* right;

        Node(T k) : key(k), height(1), size(1), left(nullptr), right(nullptr) {}
    };

    Node* root;
    Comparator cmp;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int size(Node* node) {
        return node ? node->size : 0;
    }

    void update(Node* node) {
        if (node) {
            node->height = 1 + max(height(node->left), height(node->right));
            node->size = 1 + size(node->left) + size(node->right);
        }
    }

    void rotateLeft(Node*& node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        update(node);
        update(newRoot);
        node = newRoot;
    }

    void rotateRight(Node*& node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        update(node);
        update(newRoot);
        node = newRoot;
    }

    int balanceFactor(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void balance(Node*& node) {
        update(node);
        int k = height(node->left) - height(node->right);
        if (balanceFactor(node) > 1) {
            if (balanceFactor(node->left) < 0) rotateLeft(node->left);
            rotateRight(node);
        } else if (balanceFactor(node) < -1) {
            if (balanceFactor(node->right) > 0) rotateRight(node->right);
            rotateLeft(node);
        }
    }

    void insert(Node*& node, int key, int& position, int accumulated) {
        if (!node) {
            node = new Node(key);
            position = accumulated;
            return;
        }
        if (cmp(key, node->key)) {
            insert(node->left, key, position, accumulated);
        } else {
            insert(node->right, key, position, accumulated + size(node->left) + 1);
        }
        balance(node);
    }

    void erase(Node*& node, int pos) {
        if (!node) return;

        int leftSize = size(node->left);
        if (pos < leftSize) {
            erase(node->left, pos);
        } else if (pos > leftSize) {
            erase(node->right, pos - leftSize - 1);
        } else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                node = temp;
            } else {
                Node* minNode = findMin(node->right);
                node->key = minNode->key;
                erase(node->right, 0);
            }
        }
        if (node) balance(node);
    }

    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

 public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() { clear(root); }

    int insert(int key) {
        int position = 0;
        insert(root, key, position, 0);
        return position;
    }

    void erase(int pos) { 
        erase(root, pos); 
    }
};

int main() {
    int n;
    cin >> n;

    AVLTree<int, Less <int>> tree;

    for (int i = 0; i < n; ++i) {
        int command = 0, value = 0;
        cin >> command >> value;
        switch (command) {
            case 1: {
                int position = tree.insert(value);
                cout << position << endl;
                break;
                }
            case 2: {
                tree.erase(value);
                break;
                }
        }
    }
    return 0;
}
