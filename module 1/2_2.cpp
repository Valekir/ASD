#include <iostream>
#include <cassert>

// Дан массив целых чисел А [0...n-1].
// Известно, что на интервале [0, m] значения массива строго возрастают,
// а на интервале [m, n-1] строго убывают. Найти m за O(log m).

int bin_search(int *arr, int l, int r) {
    int mid = 0;
    while (l < r) {
        mid = (l + r) / 2;
        if (arr[mid] >= arr[mid - 1] && arr[mid] >= arr[mid + 1]) {
            return mid;
        } else if (arr[mid] < arr[mid + 1]) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return r;
}

int main() {
    int n = 0, temp = 0;
    std::cin >> n;
    assert(2 <= n && n <= 10000);

    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    if (arr[0] > arr[1]) {
        std::cout << 0 << std::endl;
        return 0;
    }

    int right = 2;
    bool flag = 0;
    while (right < n && !(flag = (arr[right - 1] > arr[right]))) {
        right *= 2;
    }

    right = right >= n ? n - 1 : right;

    std::cout << bin_search(arr, 0, right) << std::endl;
}