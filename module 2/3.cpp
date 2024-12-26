#include <iostream>
#include <vector>
#include <queue>
#include <functional>

// Постройте B-дерево минимального порядка t и выведите его по слоям.
// В качестве ключа используются числа, лежащие в диапазоне [0..(2^32)-1]

// Требования:

// B-дерево должно быть реализовано в виде шаблонного класса.
// Решение должно поддерживать передачу функции сравнения снаружи.


template <typename T, typename Compare = std::less<T>>
class BTree {
 public:
    struct Node {
        explicit Node(bool leaf) : leaf(leaf) {}

        ~Node() {
            for (Node* child : children) {
                delete child;
            }
        }

        bool leaf;
        std::vector<T> keys;
        std::vector<Node*> children;
    };

    explicit BTree(size_t min_degree, Compare comp = Compare())
        : t(min_degree), root(nullptr), compare(comp) {}

    ~BTree() {
        if (root)
            delete root;
    }

    void insert(const T& key) {
        if (!root)
            root = new Node(true);

        if (isNodeFull(root)) {
            Node* newRoot = new Node(false);
            newRoot->children.push_back(root);
            root = newRoot;
            splitChild(root, 0);
        }

        insertNonFull(root, key);
    }

    void print() const {
        if (!root) return;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            size_t levelSize = q.size();

            std::vector<T> levelKeys;
            for (size_t i = 0; i < levelSize; ++i) {
                Node* node = q.front();
                q.pop();

                for (const T& key : node->keys)
                    levelKeys.push_back(key);

                if (!node->leaf) {
                    for (Node* child : node->children) {
                        q.push(child);
                    }
                }
            }

            for (const T& key : levelKeys) {
                std::cout << key << " ";
            }
            std::cout << "\n";
        }
    }

    // void debugPrint() {
    //     debugPrintInternal(root, 0);
    // }

 private:
    // void debugPrintInternal(Node *node, int indent) {
    //     std::cout << std::string(indent, ' ');
    //     std::cout << "keys: [";
    //     for (auto it = node->keys.begin(); it != node->keys.end(); it++) {
    //         std::cout << (*it);
    //         if (it + 1 != node->keys.end())
    //             std::cout << ", ";
    //     }
    //     std::cout << "]" << std::endl;

    //     for (auto child: node->children) {
    //         debugPrintInternal(child, indent + 4);
    //     }
    // }

    bool isNodeFull(Node* node) {
        return node->keys.size() == 2 * t - 1;
    }

    void splitChild(Node* node, size_t index) {
        Node* child = node->children[index];
        Node* new_children = new Node(child->leaf);

        size_t mid = t - 1;
        node->keys.insert(node->keys.begin() + index, child->keys[mid]);
        node->children.insert(node->children.begin() + index + 1, new_children);

        new_children->keys.assign(child->keys.begin() + t, child->keys.end());
        child->keys.resize(mid);

        if (!child->leaf) {
            new_children->children.assign(child->children.begin() + t, child->children.end());
            child->children.resize(t);
        }
    }

    void insertNonFull(Node* node, const T& key) {
        int pos = node->keys.size() - 1;

        if (node->leaf) {
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && compare(key, node->keys[pos])) {
                node->keys[pos + 1] = node->keys[pos];
                pos--;
            }
            node->keys[pos + 1] = key;
        } else {
            while (pos >= 0 && compare(key, node->keys[pos])) {
                pos--;
            }

            if (isNodeFull(node->children[pos + 1])) {
                splitChild(node, pos + 1);
                if (compare(node->keys[pos + 1], key))
                    pos++;
            }
            insertNonFull(node->children[pos + 1], key);
        }
    }

    size_t t;
    Node* root;
    Compare compare;
};


// void test() {
//     std::vector<int> arr;
//     int t = 20;

//     BTree<int> tree(t);
//     for (int i = 1; i < 1000000; i++) {
//         arr.push_back(i);
//     }

//     for (int key : arr) {
//         tree.insert(key);
//     }

//     tree.print();
// }


int main() {
    int t = 1;
    std::cin >> t;
    std::cin.ignore();
    BTree<int> tree(t);

    int key = 0;
    while (std::cin.peek() != '\n') {
        std::cin >> key;
        tree.insert(key);
    }

    tree.print();

    return 0;
}
