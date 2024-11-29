#include <iostream>
#include <vector>
#include <cassert>
using std::cin, std::cout, std::vector, std::endl;


int bin_search(vector <int> array, int num) {
    int center = 0;
    int left = 0;
    int right = array.size() - 1;  
    int ans = -1;  
    while (left <= right) {
        center = (left + right) / 2;
        if (array[center] >= num){
            ans = center;
            right = center - 1;
        }
        else if (num > array[center])
            left = center + 1;
        else
            right = center - 1;
    }
    return ans;
}

int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    assert (m <= 10000 && n <= 10000);
    vector <int> A;
    vector <int> B;
    int temp = 0;
    for (int i=0; i < n; i++) {
        cin >> temp;
        A.push_back(temp);
    }
    for (int i=0; i < m; i++) {
        cin >> temp;
        B.push_back(temp);
    }

    for (auto item : B) {
        temp = bin_search(A, item);
        if (temp == -1)
            cout << n << ' ';
        else
            cout << temp << ' ';
    }

    return 0;
}
