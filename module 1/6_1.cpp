#include <iostream>
#include <utility>

// Дано множество целых чисел из [0..10^9] размера n.

// Используя алгоритм поиска k-ой порядковой статистики,
// требуется найти следующие параметры множества:

// 10% перцентиль
// медиана
// 90% перцентиль

// Реализуйте стратегию выбора опорного элемента “медиана трёх”. 
// Функцию Partition реализуйте методом прохода двумя итераторами от 
// начала массива к концу.

template <typename T>
class Less {
 public:
    bool operator()(const T &l, const T &r) {
        return l <= r;
    }
};

// Возвращает индекс медианы трех
template <typename T, typename Comparator = Less<T>>
int median3(T *arr, int left, int right, Comparator cmp = Comparator()) {
    int mid = (left + right) / 2;

    T a = arr[left], b = arr[mid], c = arr[right];
    if (cmp(a, b) && cmp(a, c)) {
        return cmp(b, c) ? mid : right;
    }
    if (cmp(b, a) && cmp(b, c)) {
        return cmp(a, c) ? left : right;
    }
    return cmp(b, a) ? mid : left;
}

// Возвращает индекс вставшего на свое место опорногог элемента
template <typename T, typename Comparator = Less<T>>
int partition(T *arr, int l, int r, Comparator cmp = Comparator()) {
    int pivot = median3(arr, l, r);
    T pivot_item = arr[pivot];
    int i = l, j = l;

    std::swap(arr[r], arr[pivot]);

    while (j < r) {
        if (cmp(arr[j], pivot_item)) {
            std::swap(arr[i], arr[j]);
            i++;
        }
        j++;
    }
    std::swap(arr[i], arr[r]);
    return i;
}

// Возвращает найденную k-ю статистику
template <typename T, typename Comparator = Less<T>>
int quickSelect(T *arr, int size, int k, Comparator cmp = Comparator()) {
    int ans = 0;
    int l = 0, r = size - 1;
    while (ans != k) {
        ans = partition(arr, l, r);
        if (ans > k) {
            r = ans - 1;
        } else {
            l = ans + 1;
        }
    }
    return arr[ans];
}


int main() {
    int n = 0;
    std::cin >> n;

    int *arr = new int[n]{};
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    int k10 = quickSelect(arr, n, n / 10);
    std::cout << k10 << std::endl;
    int median = quickSelect(arr, n, n / 2);
    std::cout << median << std::endl;
    int k90 = quickSelect(arr, n, n * 9 / 10);
    std::cout << k90 << std::endl;

    delete[] arr;
    return 0;
}
