#include <iostream>
#include <cmath>

class Triad {
protected:
    int a, b, c;

public:
    Triad(int a_val, int b_val, int c_val) : a(a_val), b(b_val), c(c_val) {}

    // Методи зміни полів
    void setA(int value) { a = value; }
    void setB(int value) { b = value; }
    void setC(int value) { c = value; }

    // Метод обчислення суми чисел
    int sum() const { return a + b + c; }
};

class Triangle : public Triad {
public:
    Triangle(int a_val, int b_val, int c_val) : Triad(a_val, b_val, c_val) {}

    // Методи обчислення кутів трикутника
    double angleA() const { return acos((b*b + c*c - a*a) / (2.0 * b * c)) * 180 / M_PI; }
    double angleB() const { return acos((a*a + c*c - b*b) / (2.0 * a * c)) * 180 / M_PI; }
    double angleC() const { return acos((a*a + b*b - c*c) / (2.0 * a * b)) * 180 / M_PI; }

    // Метод обчислення площі трикутника за формулою Герона
    double area() const {
        double p = static_cast<double>(sum()) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

int main() {
    Triangle triangle(3, 4, 5);

    std::cout << "Triangle sides: " << triangle.sum() << std::endl;
    std::cout << "Angles: A = " << triangle.angleA() << "°, B = " << triangle.angleB() << "°, C = " << triangle.angleC() << "°" << std::endl;
    std::cout << "Area: " << triangle.area() << std::endl;

    return 0;
}
