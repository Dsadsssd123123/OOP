#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

class Parallelogram
{
private:
    double base;       // Основа
    double height;     // Висота
    double side;       // Бічна сторона
    std::string color; // Колір

public:
    // Конструктор за замовчуванням
    Parallelogram() : base(0), height(0), side(0), color("black") {}

    // Конструктор з параметрами
    Parallelogram(double b, double h, double s, const std::string &c)
    {
        if (b > 0 && h > 0 && s > 0)
        {
            base = b;
            height = h;
            side = s;
            color = c;
        }
        else
        {
            std::cerr << "Помилка: некоректні параметри для створення паралелограму!" << std::endl;
            base = height = side = 0;
            color = "black";
        }
    }

    // Функція обчислення площі паралелограму
    double area() const
    {
        return base * height;
    }

    // Функція обчислення периметру паралелограму
    double perimeter() const
    {
        return 2 * (base + side);
    }

    // Функції-члени для встановлення значень полів
    void setBase(double b)
    {
        if (b > 0)
            base = b;
        else
            std::cerr << "Помилка: некоректне значення для основи!" << std::endl;
    }

    void setHeight(double h)
    {
        if (h > 0)
            height = h;
        else
            std::cerr << "Помилка: некоректне значення для висоти!" << std::endl;
    }

    void setSide(double s)
    {
        if (s > 0)
            side = s;
        else
            std::cerr << "Помилка: некоректне значення для бічної сторони!" << std::endl;
    }

    void setColor(const std::string &c)
    {
        color = c;
    }

    // Функції-члени для отримання значень полів
    double getBase() const
    {
        return base;
    }

    double getHeight() const
    {
        return height;
    }

    double getSide() const
    {
        return side;
    }

    std::string getColor() const
    {
        return color;
    }

    // Функція для друку параметрів паралелограму
    void print() const
    {
        std::cout << "Паралелограм:" << std::endl;
        std::cout << "Основа: " << base << std::endl;
        std::cout << "Висота: " << height << std::endl;
        std::cout << "Бічна сторона: " << side << std::endl;
        std::cout << "Колір: " << color << std::endl;
        std::cout << "Площа: " << area() << std::endl;
        std::cout << "Периметр: " << perimeter() << std::endl;
    }
};

// Функція для генерації випадкових чисел в заданому діапазоні
double random(double min, double max)
{
    return min + static_cast<double>(rand()) / RAND_MAX * (max - min);
}

int main()
{
    // Тестування класу Parallelogram

    // Створення паралелограму з введенням даних з клавіатури
    double base, height, side;
    std::string color;

    std::cout << "Введіть значення основи паралелограму: ";
    std::cin >> base;
    std::cout << "Введіть значення висоти паралелограму: ";
    std::cin >> height;
    std::cout << "Введіть значення бічної сторони паралелограму: ";
    std::cin >> side;
    std::cout << "Введіть колір паралелограму: ";
    std::cin >> color;

    Parallelogram p1(base, height, side, color);

    // Створення паралелограму з введенням даних з файлу
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Помилка відкриття файлу!" << std::endl;
        return 1;
    }

    inputFile >> base >> height >> side >> color;
    Parallelogram p2(base, height, side, color);

    inputFile.close();

    // Створення паралелограму з випадковими значеннями
    srand(time(nullptr));
    Parallelogram p3(random(1, 10), random(1, 10), random(1, 10), "green");

    // Друкування параметрів паралелограмів
    p1.print();
    std::cout << std::endl;

    p2.print();
    std::cout << std::endl;

    p3.print();

    return 0;
}
