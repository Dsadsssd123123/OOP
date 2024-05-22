#include <iostream>
#include <algorithm>

template<typename T>
void findAndRemoveMin(T arr[], int size) {
    if (size == 0) return;

    // Знаходження мінімального значення
    T minValue = *std::min_element(arr, arr + size);

    // Видалення всіх екземплярів мінімального значення
    int newSize = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] != minValue) {
            arr[newSize++] = arr[i];
        }
    }

    // Зміна розміру масиву
    size = newSize;

    // Виведення масиву після видалення мінімальних значень
    std::cout << "Масив після видалення мінімальних значень: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Спеціалізація функції-шаблону для типу char*
template<>
void findAndRemoveMin<char*>(char* arr[], int size) {
    if (size == 0) return;

    // Знаходження мінімального значення
    char* minValue = *std::min_element(arr, arr + size, [](const char* a, const char* b) {
        return std::strcmp(a, b) < 0;
    });

    // Видалення всіх екземплярів мінімального значення
    int newSize = 0;
    for (int i = 0; i < size; ++i) {
        if (std::strcmp(arr[i], minValue) != 0) {
            arr[newSize++] = arr[i];
        }
    }

    // Зміна розміру масиву
    size = newSize;

    // Виведення масиву після видалення мінімальних значень
    std::cout << "Масив після видалення мінімальних значень: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arrInt[] = {3, 1, 4, 1, 5, 9, 2, 6};
    findAndRemoveMin(arrInt, sizeof(arrInt) / sizeof(arrInt[0]));

    char* arrStr[] = {"apple", "banana", "apple", "orange", "pear"};
    findAndRemoveMin(arrStr, sizeof(arrStr) / sizeof(arrStr[0]));

    return 0;
}
