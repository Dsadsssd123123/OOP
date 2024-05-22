#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Клас для представлення банківського рахунку клієнта
class BankAccount
{
private:
    double balance; // Баланс рахунку

public:
    BankAccount() : balance(0) {}                                   // Конструктор за замовчуванням
    BankAccount(double initialBalance) : balance(initialBalance) {} // Конструктор з параметрами

    // Метод для анулювання рахунку
    void cancelAccount()
    {
        balance = 0;
    }

    // Методи для зберігання/завантаження даних з файлу
    void saveToFile(const string &filename)
    {
        ofstream file(filename);
        if (file.is_open())
        {
            file << balance << endl;
            file.close();
        }
    }

    void loadFromFile(const string &filename)
    {
        ifstream file(filename);
        if (file.is_open())
        {
            file >> balance;
            file.close();
        }
    }

    // Додаткові методи можна додавати за необхідності
};

// Клас для представлення банківської карти клієнта
class BankCard
{
private:
    string cardNumber; // Номер картки
    bool isActive;     // Статус активності картки

public:
    BankCard() : isActive(true) {}                                         // Конструктор за замовчуванням
    BankCard(const string &number) : cardNumber(number), isActive(true) {} // Конструктор з параметрами

    // Метод для блокування карти
    void blockCard()
    {
        isActive = false;
    }

    // Методи для зберігання/завантаження даних з файлу
    void saveToFile(const string &filename)
    {
        ofstream file(filename);
        if (file.is_open())
        {
            file << cardNumber << endl;
            file << isActive << endl;
            file.close();
        }
    }

    void loadFromFile(const string &filename)
    {
        ifstream file(filename);
        if (file.is_open())
        {
            file >> cardNumber >> isActive;
            file.close();
        }
    }

    // Додаткові методи можна додавати за необхідності
};

// Клас для представлення клієнта
class Client
{
private:
    BankAccount account; // Об'єкт банківського рахунку
    BankCard card;       // Об'єкт банківської карти

public:
    // Конструктори з параметрами
    Client() {}
    Client(const BankAccount &acc, const BankCard &c) : account(acc), card(c) {}

    // Метод для оплати замовлення
    void payOrder(double amount)
    {
        if (amount <= account.getBalance())
        {
            account.decreaseBalance(amount);
        }
        else
        {
            cout << "Недостатньо коштів на рахунку!" << endl;
        }
    }

    // Метод для переказу коштів на інший рахунок
    void transferToAccount(double amount, BankAccount &recipientAccount)
    {
        if (amount <= account.getBalance())
        {
            account.decreaseBalance(amount);
            recipientAccount.increaseBalance(amount);
        }
        else
        {
            cout << "Недостатньо коштів на рахунку!" << endl;
        }
    }

    // Метод для блокування банківської карти
    void blockCard()
    {
        card.blockCard();
    }

    // Метод для анулювання банківського рахунку
    void cancelAccount()
    {
        account.cancelAccount();
    }

    // Методи для зберігання/завантаження даних з файлу
    void saveToFile(const string &accountFile, const string &cardFile)
    {
        account.saveToFile(accountFile);
        card.saveToFile(cardFile);
    }

    void loadFromFile(const string &accountFile, const string &cardFile)
    {
        account.loadFromFile(accountFile);
        card.loadFromFile(cardFile);
    }

    // Додаткові методи можна додавати за необхідності
};

int main()
{
    // Основний код програми тут
    return 0;
}
