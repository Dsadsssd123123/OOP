#include <iostream>
#include <string>
#include <cctype>

class String
{
protected:
    std::string str;

public:
    String() : str("") {}
    String(const std::string &s) : str(s) {}

    // Конструктор копіювання
    String(const String &other) : str(other.str) {}

    // Оператор присвоювання
    String &operator=(const String &other)
    {
        if (this != &other)
        {
            str = other.str;
        }
        return *this;
    }

    // Оператор виведення у потік
    friend std::ostream &operator<<(std::ostream &out, const String &s)
    {
        out << s.str;
        return out;
    }

    // Оператор введення з потоку
    friend std::istream &operator>>(std::istream &in, String &s)
    {
        in >> s.str;
        return in;
    }
};

class UppercaseString : public String
{
public:
    UppercaseString() : String() {}
    UppercaseString(const std::string &s) : String(s) {}

    // Конструктор копіювання
    UppercaseString(const UppercaseString &other) : String(other) {}

    // Оператор присвоювання
    UppercaseString &operator=(const UppercaseString &other)
    {
        if (this != &other)
        {
            str = other.str;
        }
        return *this;
    }

    // Перевизначення методу виведення у потік
    friend std::ostream &operator<<(std::ostream &out, const UppercaseString &s)
    {
        for (char c : s.str)
        {
            out << static_cast<char>(toupper(c));
        }
        return out;
    }
};

int main()
{
    String s1("Hello");
    String s2;
    std::cin >> s2;

    std::cout << "String s1: " << s1 << std::endl;
    std::cout << "String s2: " << s2 << std::endl;

    UppercaseString u1("world");
    UppercaseString u2 = u1;

    std::cout << "UppercaseString u1: " << u1 << std::endl;
    std::cout << "UppercaseString u2: " << u2 << std::endl;

    return 0;
}
