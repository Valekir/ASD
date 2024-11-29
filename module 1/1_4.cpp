#include <iostream>
#include <cassert>
using std::cin, std::cout;


int main() {
    unsigned int num = 0;
    unsigned int k = 0;
    assert ((0 <= k) && (k <= 31));
    cin >> num >> k;
    num ^= (1 << k);
    cout << num;
    return 0;
}
