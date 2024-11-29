#include <iostream>
using std::cin, std::cout;

// Подсчитать кол-во единичных бит в входном числе, стоящих на четных позициях. 
// Позиции битов нумеруются с 0.

int main() {
    unsigned num = 0;
    cin >> num;
    unsigned answer = num & 1;
    while (num > 0) {
        answer += (num >> 2) & 1;
        num = num >> 2;
    }
    cout << answer;
}
