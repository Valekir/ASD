#include <iostream>
#include <cassert>
#include <utility>
// В операционной системе Technux есть планировщик процессов.
// Каждый процесс характеризуется:
// приоритетом P
// временем, которое он уже отработал t
// временем, которое необходимо для завершения работы процесса T

// Планировщик процессов выбирает процесс с минимальным значением P * (t + 1),
// выполняет его время P и кладет обратно в очередь процессов.
// Если выполняется условие t >= T, то процесс считается
// завершенным и удаляется из очереди.
// Требуется посчитать кол-во переключений процессора.

struct Process {
    int priority = 0;
    int time = 0;
    int time_spent = 0;
};

std::istream& operator>>(std::istream& in, Process &proc) {
    int p = 0, t = 0;
    in >> p >> t;
    proc.priority = p;
    proc.time = t;
    proc.time_spent = 0;
    return in;
}

// std::ostream& operator<<(std::ostream& out, Process &proc) {
//     std::cout << proc.priority << ' ' << proc.time << ' ' << proc.time_spent;
//     return out;
// }

bool process_less(const Process &l, const Process &r) {
    return (l.priority * (1 + l.time_spent)) <= (r.priority * (1 + r.time_spent));
}

template <typename T>
class Heap {
 private:
    T* data;
    int buf_size;
    int size;
    bool (*cmp)(const T&, const T&);

    void increaseBuffer() {
        buf_size *= 2;
        T* temp = new T[buf_size];
        for (int i = 0; i < size; i++) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }

    int parent(int index) {
        return (index - 1) / 2;
    }

        void siftUp(int index) {
        if (index && cmp(data[index], data[parent(index)])) {
            std::swap(data[index], data[parent(index)]);
            siftUp(parent(index));
        }
    }

    void siftDown(int index) {
        int min = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && cmp(data[left], data[min])) {
            min = left;
        }

        if (right < size && cmp(data[right], data[min])) {
            min = right;
        }

        if (min != index) {
            std::swap(data[index], data[min]);
            siftDown(min);
        }
    }

 public:
    explicit Heap(bool (*_cmp)(const T&, const T&)) {
        buf_size = 16;
        data = new T[buf_size];
        size = 0;
        cmp = _cmp;
    }

    ~Heap() { delete[] data; }
    Heap(const Heap &p) = delete;
    Heap& operator=(const Heap &p) = delete;



    void insert(const T& item) {
        if (size == buf_size - 1)
            increaseBuffer();
        data[size++] = item;
        siftUp(size - 1);
    }

    T pop(int index) {
        assert(!isEmpty());
        T min = data[index];
        std::swap(data[index], data[size - 1]);
        size--;
        if (!isEmpty()) {
            siftDown(index);
        }
        return min;
    }

    bool isEmpty() {
        return size == 0;
    }

    T getMin() {
        return data[0];
    }

    T* getData() { return data; }
};


int main() {
    Heap <Process> heap(process_less);
    Process temp;
    int n = 0;
    int ans = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        heap.insert(temp);
    }

    Process* arr = new Process[n];

    while (!heap.isEmpty()) {
        temp = heap.pop(0);
        temp.time_spent += temp.priority;

        if (temp.time_spent < temp.time) {
            heap.insert(temp);
        }
        ans++;
    }

    std::cout << ans << std::endl;
    return 0;
}
