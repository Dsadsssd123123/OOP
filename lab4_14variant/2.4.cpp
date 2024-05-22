#include <iostream>
#include <unordered_map>
#include <string>

class Association
{
private:
    std::unordered_map<std::string, std::string> data; // Електронна пошта як ключ, номер телефону як значення
    int codeError;                                     // 0 - немає помилок, 1 - відсутність сутності

public:
    // Конструктор за замовчуванням
    Association() : codeError(0) {}

    // Додавання асоціативної сутності
    void add(const std::string &email, const std::string &phoneNumber)
    {
        data[email] = phoneNumber;
    }

    // Перевантаження оператора індексації []
    std::string &operator[](const std::string &email)
    {
        if (data.find(email) != data.end())
        {
            codeError = 0;
            return data[email];
        }
        else
        {
            codeError = 1; // Відсутня сутність
            static std::string empty;
            return empty;
        }
    }

    // Дружня функція для виведення
    friend std::ostream &operator<<(std::ostream &out, const Association &assoc);
};

// Перевантаження оператора виведення
std::ostream &operator<<(std::ostream &out, const Association &assoc)
{
    for (const auto &pair : assoc.data)
    {
        out << "Email: " << pair.first << ", Phone Number: " << pair.second << std::endl;
    }
    return out;
}

int main()
{
    Association assoc;
    assoc.add("john@example.com", "123456789");
    assoc.add("jane@example.com", "987654321");

    std::cout << "Associations:\n"
              << assoc << std::endl;

    // Використання оператора індексації
    std::cout << "Phone number for john@example.com: " << assoc["john@example.com"] << std::endl;
    std::cout << "Phone number for unknown@example.com: " << assoc["unknown@example.com"] << std::endl;

    return 0;
}
