#include <iostream>

class Vector
{
private:
    unsigned int *data; // Вказівник на масив
    unsigned int size;  // Розмір вектора
    bool state;         // Змінна стану

public:
    // Конструктор без параметрів
    Vector() : data(new unsigned int[1]), size(1), state(false)
    {
        data[0] = 0; // Ініціалізація першого елемента нулем
    }

    // Конструктор з одним параметром - розміром вектора
    Vector(unsigned int s) : size(s), state(false)
    {
        data = new unsigned int[size];
        for (unsigned int i = 0; i < size; ++i)
        {
            data[i] = 0; // Ініціалізація всіх елементів нулем
        }
    }

    // Конструктор з двома параметрами - розміром вектора та значенням ініціалізації
    Vector(unsigned int s, unsigned int initValue) : size(s), state(false)
    {
        data = new unsigned int[size];
        for (unsigned int i = 0; i < size; ++i)
        {
            data[i] = initValue; // Ініціалізація всіх елементів заданим значенням
        }
    }

    // Конструктор копії
    Vector(const Vector &other) : size(other.size), state(other.state)
    {
        data = new unsigned int[size];
        for (unsigned int i = 0; i < size; ++i)
        {
            data[i] = other.data[i]; // Копіювання значень елементів
        }
    }

    // Оператор присвоєння
    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            delete[] data; // Звільнення пам'яті від поточного масиву
            size = other.size;
            state = other.state;
            data = new unsigned int[size];
            for (unsigned int i = 0; i < size; ++i)
            {
                data[i] = other.data[i]; // Копіювання значень елементів
            }
        }
        return *this;
    }

    // Деструктор
    ~Vector()
    {
        delete[] data; // Звільнення пам'яті
    }

    // Функція для присвоєння значення заданому елементу масиву
    void setValue(unsigned int index, unsigned int value)
    {
        if (index >= 0 && index < size)
        {
            data[index] = value;
        }
        else
        {
            std::cerr << "Помилка: недійсний індекс!" << std::endl;
        }
    }

    // Функція для отримання значення заданого елементу масиву
    unsigned int getValue(unsigned int index) const
    {
        if (index >= 0 && index < size)
        {
            return data[index];
        }
        else
        {
            std::cerr << "Помилка: недійсний індекс!" << std::endl;
            return 0; // Повертаємо 0 в разі помилки
        }
    }
};

int main()
{
    // Тестування класу Vector

    // Створення вектора з конструктором без параметрів
    Vector v1;
    v1.setValue(0, 5); // Присвоєння значення першому елементу

    // Створення вектора з конструктором з одним параметром
    Vector v2(3);
    v2.setValue(1, 10); // Присвоєння значення другому елементу

    // Створення вектора з конструктором з двома параметрами
    Vector v3(5, 7);
    v3.setValue(2, 15); // Присвоєння значення третьому елементу

    // Копіювання вектора
    Vector v4 = v3;
    v4.setValue(3, 20); // Присвоєння значення четвертому елементу

    // Виведення значень елементів векторів
    std::cout << "Елемент 0 вектора v1: " << v1.getValue(0) << std::endl;
    std::cout << "Елемент 1 вектора v2: " << v2.getValue(1) << std::endl;
    std::cout << "Елемент 2 вектора v3: " << v3.getValue(2) << std::endl;
    std::cout << "Елемент 3 вектора v4: " << v4.getValue(3) << std::endl;


       return 0;
}
