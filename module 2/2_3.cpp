#include <iostream>
#include <stack>

// Дано число N ≤ 10^4 и последовательность целых чисел из [-2^31..2^31] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
// то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// Выведите элементы в порядке post-order (снизу вверх).
// Рекурсия запрещена.

template <typename T>
class Less {
 public:
    bool operator()(const T& l, const T& r) {
        return l <= r;
    }
};

struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}
};


template <typename T, typename Comparator = Less<T>>
class BinaryTree {
 private:
    TreeNode* root;
    Comparator cmp;

 public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { clear(root); }
    BinaryTree(const BinaryTree &p) = delete;
    BinaryTree& operator=(const BinaryTree &p) = delete;

    void insert(const T& key) {
        TreeNode* newNode = new TreeNode(key);
        if (!root) {
            root = newNode;
            return;
        }

        TreeNode* current = root;
        while (true) {
            if (cmp(key, current->key)) {
                if (!current->left) {
                    current->left = newNode;
                    return;
                }
                current = current->left;
            } else {
                if (!current->right) {
                    current->right = newNode;
                    return;
                }
                current = current->right;
            }
        }
    }

    void post_order() const {
        if (!root)
            return;

        std::stack<TreeNode*> stack;
        TreeNode* current = root;
        TreeNode* last = nullptr;

        while (!stack.empty() || current) {
            if (current) {
                stack.push(current);
                current = current->left;
            } else {
                TreeNode* node = stack.top();
                if (node->right && last != node->right) {
                    current = node->right;
                } else {
                    std::cout << node->key << " ";
                    last = node;
                    stack.pop();
                }
            }
        }
        std::cout << std::endl;
    }

    void clear(TreeNode* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

int main() {
    BinaryTree<int> tree;

    int N;
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        int value;
        std::cin >> value;
        tree.insert(value);
    }

    tree.post_order();
    return 0;
}
