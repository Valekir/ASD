#include <iostream>
#include <string>

// Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы
// с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
// Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
// Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов
// в случае, когда коэффициент заполнения таблицы достигает 3/4.
// Структура данных должна поддерживать операции добавления строки в множество, удаления строки
// из множества и проверки принадлежности данной строки множеству.
// Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
// g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

struct HashMapItem {
    std::string str = "";
    // E - empty, F - full, D - deleted
    char status = 'E';
};

class HashMap {
private:
    int size;
    int count;
    HashMapItem* data;

    void resize() {
        int old_size = size;
        size *= 2;
        count = 0;

        HashMapItem* old_data = data;
        data = new HashMapItem[size]{};

        for (int i = 0; i < old_size; i++) {
            if (old_data[i].status == 'F') {
                add(old_data[i].str);
            }
        }
        delete[] old_data;
    }

    int hash(const std::string& item) {
        int res = 0;
        int k = 31;
        for (char ch : item) {
            res = (res * k + ch) % size;
        }
        return res;
    }

    int probe(const std::string& item, bool for_insert) {
        int index = hash(item);
        int first_DEL = -1;

        for (int i = 0; i < size; i++) {
            int index = (index + i) % size;

            if (data[index].status == 'E') {
                return (first_DEL != -1 && for_insert) ? first_DEL : index;
            }
            if (data[index].status == 'D' && first_DEL == -1) {
                first_DEL = index;
            }
            if (data[index].status == 'F' && data[index].str == item) {
                return index;
            }
        }
        return for_insert ? first_DEL : -1;
    }

public:
    HashMap() : size(8), count(0), data(new HashMapItem[8]{}) {}

    ~HashMap() { delete[] data; }

    bool add(const std::string& item) {
        if (static_cast<double>(count + 1) / size >= 0.75) {
            resize();
        }

        int index = probe(item, true);
        if (index == -1 || (data[index].status == 'F' && data[index].str == item)) {
            return false;
        }

        data[index].str = item;
        data[index].status = 'F';
        count++;
        return true;
    }

    bool remove(const std::string& item) {
        int index = probe(item, false);
        if (index == -1 || data[index].status != 'F' || data[index].str != item) {
            return false;
        }

        data[index].status = 'D';
        count--;
        return true;
    }

    bool has(const std::string& item) {
        int index = probe(item, false);
        return index != -1 && data[index].status == 'F' && data[index].str == item;
    }
};

int main() {
    HashMap table;

    char op;
    std::string key;

    while (std::cin >> op >> key) {
        switch (op) {
            case '?':
                std::cout << (table.has(key) ? "OK" : "FAIL") << std::endl;
                break;
            case '+':
                std::cout << (table.add(key) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (table.remove(key) ? "OK" : "FAIL") << std::endl;
                break;
            default:
                std::cout << "FAIL" << std::endl;
        }
    }

    return 0;
}
