#include <iostream>
#include <vector>
#include <cassert>
using std::cin, std::cout, std::vector, std::endl, std::srand;

// Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
// A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение.
// Требуемое время работы: O(m * log k), где k - позиция элемента B[m-1]
// в массиве A. В процессе поиска очередного элемента
// B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1].
// n, k ≤ 10000.

int bin_search(vector <int> array, int left, int num) {
    int right = array.size();
    int mid = 0;

    while (left <= right) {
        mid = (left + right) / 2;
        if (array[mid] == num)
            return mid;
        else if (array[mid] > num)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    assert(m <= 10000 && n <= 10000);
    vector <int> A;
    vector <int> B;
    int temp = 0;
    int last = 0;

    for (int i = 0; i < n; i++) {
        cin >> temp;
        A.push_back(temp);
    }

    for (int i = 0; i < m; i++) {
        cin >> temp;
        B.push_back(temp);
    }

    for (auto item : B) {
        temp = bin_search(A, last, item);
        if (temp != -1) {
            last = temp;
            cout << A[last] << ' ';
        }
    }
    return 0;
}
