#include <iostream>
#include <cassert>
using std::cin, std::cout, std::endl;

// Реализовать дек с динамическим зацикленным буфером.
// Обрабатывать команды push * и pop *.

// Каждая команда задаётся как 2 целых числа: a b.
// a = 1 - push front
// a = 2 - pop front
// a = 3 - push back
// a = 4 - pop back

class Deque {
 private:
    int *data;
    int buf_size;
    int size;
    int head;
    int tail;

    int moveRight(int index) {
        return (index + 1) % buf_size;
    }

    int moveLeft(int index) {
        if (index <= 0) {
            return buf_size - 1;
        }
        return index - 1;
    }

    void resize() {
        int *temp = new int[buf_size * 2]{};
        int i = moveRight(head);
        for (int j = 0; j < buf_size; i = moveRight(i), j++) {
            temp[j] = data[i];
        }
        delete[] data;

        buf_size *= 2;
        head = buf_size - 1;
        tail = size;
        data = temp;
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == buf_size;
    }

 public:
    explicit Deque(int new_size) {
        buf_size = new_size;
        data = new int[buf_size]{};
        size = 0;
        head = 0;
        tail = 1;
    }
    ~Deque() { delete[] data; }
    Deque(const Deque &p) = delete;
    Deque& operator=(const Deque &p) = delete;


    void push_front(int item) {
        if (isFull()) {
            resize();
        }
        data[head] = item;
        head = moveLeft(head);
        size++;
    }

    int pop_front() {
        head = moveRight(head);
        if (isEmpty()) {
            return -1;
        }
        int temp = data[head];
        data[head] = 0;
        size--;
        return temp;
    }

    void push_back(int item) {
        if (isFull()) {
            resize();
        }
        data[tail] = item;
        tail = moveRight(tail);
        size++;
    }

    int pop_back() {
        tail = moveLeft(tail);
        if (isEmpty()) {
            return -1;
        }
        int temp = data[tail];
        data[tail] = 0;
        size--;
        return temp;
    }
};

int main() {
    Deque d(4);
    int n = 0;
    cin >> n;
    assert(n <= 1000000);

    unsigned a = 0;
    int b = 0, temp = 0;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        switch (a) {
        case 1:
            assert(b >= 0);
            d.push_front(b);
            break;
        case 2:
            temp = d.pop_front();
            if (temp != b) {
                cout << "NO" << endl;
                return 0;
            }
            break;
        case 3:
            assert(b >= 0);
            d.push_back(b);
            break;
        case 4:
            temp = d.pop_back();
            if (temp != b) {
                cout << "NO" << endl;
                return 0;
            }
            break;
        default:
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    return 0;
}
