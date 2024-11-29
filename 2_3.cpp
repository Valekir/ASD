#include <iostream>
#include <stack>
#include <functional>


// Дано число N ≤ 10^4 и последовательность целых чисел из [-2^31..2^31] длиной N. 
// Требуется построить бинарное дерево, заданное наивным порядком вставки. 
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, 
// то узел K добавляется в правое поддерево root; иначе в левое поддерево root. 
// Выведите элементы в порядке post-order (снизу вверх).
// Рекурсия запрещена.


// Узел дерева
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

// Класс бинарного дерева
class BinaryTree {
private:
    TreeNode* root;
    std::function<bool(int, int)> compare;

public:
    // Конструктор с функцией сравнения
    BinaryTree(std::function<bool(int, int)> cmp = [](int a, int b) { return a < b; }) : root(nullptr), compare(cmp) {}

    void insert(int key) {
        TreeNode* newNode = new TreeNode(key);

        if (!root) {
            root = newNode;
            return;
        }

        TreeNode* current = root;
        while (true) {
            if (compare(key, current->key)) {
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
        TreeNode* lastVisited = nullptr;

        while (!stack.empty() || current) {
            if (current) {
                stack.push(current);
                current = current->left;
            } else {
                TreeNode* node = stack.top();
                if (node->right && lastVisited != node->right) {
                    current = node->right;
                } else {
                    std::cout << node->key << " ";
                    lastVisited = node;
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

    ~BinaryTree() { clear(root); }
};

int main() {
    BinaryTree tree([](int a, int b) { return a <= b; });

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
