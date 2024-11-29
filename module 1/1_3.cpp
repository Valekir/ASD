#include <iostream>
using std::cin, std::cout;

// Вернуть значение бита в числе N по его номеру K.
// Позиции битов нумеруются с 0.
// Необходимо использование битовых операций.
// Использование арифметических операций запрещено.

int main() {
    unsigned num = 0;
    cin >> num;
    unsigned ans = 0;
    while (num > 0) {
        ans += num & 1;
        num = num >> 1;
    }
    if (ans != 1)
        cout << "FAIL";
    else
        cout << "OK";
}
