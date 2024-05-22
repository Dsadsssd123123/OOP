#include <iostream>

class Matrix
{
private:
    int **data; // Вказівник на матрицю
    int rows;   // Кількість рядків
    int cols;   // Кількість стовпців
    int error;  // Код помилки

public:
    // Конструктор без параметрів
    Matrix() : rows(3), cols(3), error(0)
    {
        // Виділення пам'яті для матриці
        data = new int *[rows];
        for (int i = 0; i < rows; ++i)
        {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j)
            {
                data[i][j] = 0; // Ініціалізація матриці нулями
            }
        }
    }

    // Конструктор з одним параметром - розміром матриці
    Matrix(int n) : rows(n), cols(n), error(0)
    {
        // Виділення пам'яті для матриці
        data = new int *[rows];
        for (int i = 0; i < rows; ++i)
        {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j)
            {
                data[i][j] = 0; // Ініціалізація матриці нулями
            }
        }
    }

    // Конструктор з трьома параметрами - розмірами матриці та значенням ініціалізації
    Matrix(int n, int m, int value) : rows(n), cols(m), error(0)
    {
        // Виділення пам'яті для матриці
        data = new int *[rows];
        for (int i = 0; i < rows; ++i)
        {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j)
            {
                data[i][j] = value; // Ініціалізація матриці заданим значенням
            }
        }
    }

    // Конструктор копії
    Matrix(const Matrix &other)
    {
        rows = other.rows;
        cols = other.cols;
        error = other.error;

        // Виділення пам'яті для матриці
        data = new int *[rows];
        for (int i = 0; i < rows; ++i)
        {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j)
            {
                data[i][j] = other.data[i][j]; // Копіювання значень елементів
            }
        }
    }

    // Оператор присвоєння
    Matrix &operator=(const Matrix &other)
    {
        if (this != &other)
        {
            // Звільнення пам'яті від поточної матриці
            for (int i = 0; i < rows; ++i)
            {
                delete[] data[i];
            }
            delete[] data;

            rows = other.rows;
            cols = other.cols;
            error = other.error;

            // Виділення пам'яті для матриці
            data = new int *[rows];
            for (int i = 0; i < rows; ++i)
            {
                data[i] = new int[cols];
                for (int j = 0; j < cols; ++j)
                {
                    data[i][j] = other.data[i][j]; // Копіювання значень елементів
                }
            }
        }
        return *this;
    }

    // Деструктор
    ~Matrix()
    {
        // Звільнення пам'яті від матриці
        for (int i = 0; i < rows; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
    }

    // Функція для присвоєння значення заданому елементу матриці
    void setValue(int i, int j, int value)
    {
        if (i >= 0 && i < rows && j >= 0 && j < cols)
        {
            data[i][j] = value;
        }
        else
        {
            error = 1; // Встановлюємо код помилки, якщо індекси виходять за межі матриці
            std::cerr << "Помилка: недійсний індекс!" << std::endl;
        }
    }

    // Функція для отримання значення заданого елементу матриці
    int getValue(int i, int j) const
    {
        if (i >= 0 && i < rows && j >= 0 && j < cols)
        {
            return data[i][j];
        }
        else
        {
            error = 1; // Встановлюємо код помилки, якщо індекси виходять за межі матриці
            std::cerr << "Помилка: недійсний індекс!" << std::endl;
            return 0; // Повертаємо 0 в разі помилки
        }
    }

    // Функція друку матриці
    void print() const
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                std::cout << data[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

    // Функція додавання матриць
    Matrix add(const Matrix &other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            error = 1; // Встановлюємо код помилки, якщо розміри матриць не співпадають
            std::cerr << "Помилка: неправильні розміри матриць!" << std::endl;
            return Matrix(); // Повертаємо порожню матрицю в разі помилки
        }

        Matrix result(rows, cols, 0); // Створюємо матрицю результату з нулями

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result.data[i][j] = data[i][j] + other.data[i][j]; // Додаємо елементи матриць
            }
        }
        return result;
    }

    // Функція множення матриць
    Matrix multiply(const Matrix &other) const
    {
        if (cols != other.rows)
        {
            error = 1; // Встановлюємо код помилки, якщо кількість стовпців першої матриці не дорівнює кількості рядків другої матриці
            std::cerr << "Помилка: неправильні розміри матриць для множення!" << std::endl;
            return Matrix(); // Повертаємо порожню матрицю в разі помилки
        }

        Matrix result(rows, other.cols, 0); // Створюємо матрицю результату з нулями

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < other.cols; ++j)
            {
                for (int k = 0; k < cols; ++k)
                {
                    result.data[i][j] += data[i][k] * other.data[k][j]; // Множимо елементи матриць
                }
            }
        }
        return result;
    }

    // Функція віднімання матриць
    Matrix subtract(const Matrix &other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            error = 1; // Встановлюємо код помилки, якщо розміри матриць не співпадають
            std::cerr << "Помилка: неправильні розміри матриць!" << std::endl;
            return Matrix(); // Повертаємо порожню матрицю в разі помилки
        }

        Matrix result(rows, cols, 0); // Створюємо матрицю результату з нулями

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result.data[i][j] = data[i][j] - other.data[i][j]; // Віднімаємо елементи матриць
            }
        }
        return result;
    }

    // Функції порівняння матриць
    bool isEqual(const Matrix &other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            error = 1; // Встановлюємо код помилки, якщо розміри матриць не співпадають
            std::cerr << "Помилка: неправильні розміри матриць!" << std::endl;
            return false; // Повертаємо false, якщо розміри матриць не співпадають
        }
    }

    // Функція порівняння матриць "більше"
    bool isGreaterThan(const Matrix &other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            error = 1; // Встановлюємо код помилки, якщо розміри матриць не співпадають
            std::cerr << "Помилка: неправильні розміри матриць!" << std::endl;
            return false; // Повертаємо false, якщо розміри матриць не співпадають
        }

        // Порівнюємо кожен елемент матриць
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (data[i][j] <= other.data[i][j])
                {
                    return false; // Повертаємо false, якщо хоча б один елемент не відповідає умові
                }
            }
        }
        return true; // Повертаємо true, якщо всі елементи матриці більші за відповідні елементи іншої матриці
    }

    // Функція порівняння матриць "менше"
    bool isLessThan(const Matrix &other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            error = 1; // Встановлюємо код помилки, якщо розміри матриць не співпадають
            std::cerr << "Помилка: неправильні розміри матриць!" << std::endl;
            return false; // Повертаємо false, якщо розміри матриць не співпадають
        }

        // Порівнюємо кожен елемент матриць
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (data[i][j] >= other.data[i][j])
                {
                    return false; // Повертаємо false, якщо хоча б один елемент не відповідає умові
                }
            }
        }
        return true; // Повертаємо true, якщо всі елементи матриці менші за відповідні елементи іншої матриці
    }
};

int main()
{
    // Тестування функціональності класу Matrix

    // Створення матриці без параметрів
    Matrix matrix1;
    std::cout << "Матриця 1:" << std::endl;
    matrix1.print();

    // Створення матриці з одним параметром - розміром 4x4
    Matrix matrix2(4);
    std::cout << "Матриця 2:" << std::endl;
    matrix2.print();

    // Створення матриці з трьома параметрами - розмірами 3x3 та значенням ініціалізації 5
    Matrix matrix3(3, 3, 5);
    std::cout << "Матриця 3:" << std::endl;
    matrix3.print();

    // Копіювання матриці
    Matrix matrix4 = matrix3;
    std::cout << "Матриця 4 (копія матриці 3):" << std::endl;
    matrix4.print();

    // Присвоєння матриці
    matrix2 = matrix3;
    std::cout << "Матриця 2 (після присвоєння матриці 3):" << std::endl;
    matrix2.print();

    // Встановлення значення елементу матриці
    matrix1.setValue(0, 0, 10);
    std::cout << "Матриця 1 (після встановлення значення):" << std::endl;
    matrix1.print();

    // Отримання значення елементу матриці
    std::cout << "Елемент (2, 2) матриці 2: " << matrix2.getValue(2, 2) << std::endl;

    // Додавання матриць
    Matrix sumMatrix = matrix3.add(matrix4);
    std::cout << "Сума матриць 3 і 4:" << std::endl;
    sumMatrix.print();

    // Множення матриць
    Matrix productMatrix = matrix2.multiply(matrix3);
    std::cout << "Добуток матриць 2 і 3:" << std::endl;
    productMatrix.print();

    // Віднімання матриць
    Matrix diffMatrix = matrix3.subtract(matrix4);
    std::cout << "Різниця матриць 3 і 4:" << std::endl;
    diffMatrix.print();

    // Порівняння матриць
    std::cout << "Чи матриці 1 і 2 рівні: " << (matrix1.isEqual(matrix2) ? "Так" : "Ні") << std::endl;
    std::cout << "Чи матриця 3 більша за матрицю 4: " << (matrix3.isGreaterThan(matrix4) ? "Так" : "Ні") << std::endl;
    std::cout << "Чи матриця 4 менша за матрицю 3: " << (matrix4.isLessThan(matrix3) ? "Так" : "Ні") << std::endl;

    return 0;
}
