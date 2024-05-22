#include <iostream>

class VectorShort
{
private:
    short *data;
    int size;
    int codeError; // 0 - немає помилок, 1 - недостатньо пам'яті, 2 - вихід за межі масиву

public:
    // Конструктори та деструктор
    VectorShort()
    {
        size = 1;
        data = new short[size];
        data[0] = 0;
        codeError = 0;
    }

    VectorShort(int s)
    {
        size = s;
        data = new short[size];
        for (int i = 0; i < size; ++i)
            data[i] = 0;
        codeError = 0;
    }

    VectorShort(int s, short value)
    {
        size = s;
        data = new short[size];
        for (int i = 0; i < size; ++i)
            data[i] = value;
        codeError = 0;
    }

    VectorShort(const VectorShort &other)
    {
        size = other.size;
        data = new short[size];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
        codeError = other.codeError;
    }

    ~VectorShort()
    {
        delete[] data;
    }

    // Операції перевантаження
    VectorShort &operator++()
    {
        for (int i = 0; i < size; ++i)
            ++data[i];
        return *this;
    }

    VectorShort operator++(int)
    {
        VectorShort temp(*this);
        operator++();
        return temp;
    }

    bool operator!()
    {
        return size != 0;
    }

    friend VectorShort operator~(const VectorShort &vec);
    friend VectorShort operator-(const VectorShort &vec);

    VectorShort &operator=(const VectorShort &other)
    {
        if (this == &other)
            return *this;
        delete[] data;
        size = other.size;
        data = new short[size];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
        codeError = other.codeError;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const VectorShort &vec);
    friend std::istream &operator>>(std::istream &in, VectorShort &vec);

    // Операції підрахунку числа об'єктів та порівняння
    static int countObjects;

    void *operator new(size_t size)
    {
        ++countObjects;
        return ::new VectorShort();
    }

    void operator delete(void *ptr)
    {
        --countObjects;
        ::delete ptr;
    }

    bool operator==(const VectorShort &other) const
    {
        if (size != other.size)
            return false;
        for (int i = 0; i < size; ++i)
        {
            if (data[i] != other.data[i])
                return false;
        }
        return true;
    }

    bool operator!=(const VectorShort &other) const
    {
        return !(*this == other);
    }

    short &operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            codeError = 2; // Вихід за межі масиву
            return data[size - 1];
        }
        return data[index];
    }

    const short &operator[](int index) const
    {
        if (index < 0 || index >= size)
        {
          //  codeError = 2; // Вихід за межі масиву
            return data[size - 1];
        }
        return data[index];
    }

    // Операції з побітовими операціями
    VectorShort &operator|=(const VectorShort &other)
    {
        for (int i = 0; i < size; ++i)
            data[i] |= other.data[i];
        return *this;
    }

    VectorShort &operator^=(const VectorShort &other)
    {
        for (int i = 0; i < size; ++i)
            data[i] ^= other.data[i];
        return *this;
    }

    VectorShort &operator&=(const VectorShort &other)
    {
        for (int i = 0; i < size; ++i)
            data[i] &= other.data[i];
        return *this;
    }

    // Операції порівняння
    bool operator>(const VectorShort &other) const
    {
        for (int i = 0; i < size; ++i)
        {
            if (data[i] <= other.data[i])
                return false;
        }
        return true;
    }

    bool operator>=(const VectorShort &other) const
    {
        return !(*this < other);
    }

    bool operator<(const VectorShort &other) const
    {
        for (int i = 0; i < size; ++i)
        {
            if (data[i] >= other.data[i])
                return false;
        }
        return true;
    }

    bool operator<=(const VectorShort &other) const
    {
        return !(*this > other);
    }
};

// Ініціалізація статичної змінної
int VectorShort::countObjects = 0;

// Додаткові операції перевантаження
VectorShort operator~(const VectorShort &vec)
{
    VectorShort temp(vec.size);
    for (int i = 0; i < vec.size; ++i)
        temp.data[i] = ~vec.data[i];
    return temp;
}

VectorShort operator-(const VectorShort &vec)
{
    VectorShort temp(vec.size);
    for (int i = 0; i < vec.size; ++i)
        temp.data[i] = -vec.data[i];
    return temp;
}

std::ostream &operator<<(std::ostream &out, const VectorShort &vec)
{
    for (int i = 0; i < vec.size; ++i)
        out << vec.data[i] << " ";
    return out;
}

std::istream &operator>>(std::istream &in, VectorShort &vec)
{
    for (int i = 0; i < vec.size; ++i)
        in >> vec.data[i];
    return in;
}

int main()
{
    VectorShort vec1(5, 3);
    VectorShort vec2 = vec1;
    VectorShort vec3;
    std::cin >> vec3;
    std::cout << "Vector 1: " << vec1 << std::endl;
    std::cout << "Vector 2: " << vec2 << std::endl;
    std::cout << "Vector 3: " << vec3 << std::endl;

    // Використання операцій побітового заперечення та унарного мінуса
    VectorShort vec4 = ~vec1;
    VectorShort vec5 = -vec2;
    std::cout << "Bitwise NOT of Vector 1: " << vec4 << std::endl;
    std::cout << "Unary minus of Vector 2: " << vec5 << std::endl;

    // Використання операцій порівняння
    if (vec1 == vec2)
        std::cout << "Vector 1 is equal to Vector 2" << std::endl;
    if (vec1 != vec3)
        std::cout << "Vector 1 is not equal to Vector 3" << std::endl;
    if (vec1 > vec3)
        std::cout << "Vector 1 is greater than Vector 3" << std::endl;
    if (vec3 < vec2)
        std::cout << "Vector 3 is less than Vector 2" << std::endl;

    // Використання операторів присвоєння та операцій з побітовими операціями
    VectorShort vec6;
    vec6 |= vec1;
    std::cout << "Vector 6 after bitwise OR with Vector 1: " << vec6 << std::endl;

    // Використання операції індексації
    std::cout << "Element at index 2 of Vector 2: " << vec2[2] << std::endl;

    // Підрахунок кількості об'єктів
    std::cout << "Number of VectorShort objects: " << VectorShort::countObjects << std::endl;

    return 0;
}
