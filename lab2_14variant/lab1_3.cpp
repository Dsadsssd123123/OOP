#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Структура для представлення шифрованого символу
struct EncryptedChar
{
    // Поля бітів для рядка, верхньої та нижньої частин ASCII, позиції та бітів парності
    unsigned row : 4;
    unsigned upperAscii : 4;
    unsigned parity1 : 1;
    unsigned lowerAscii : 4;
    unsigned position : 2;
    unsigned parity2 : 1;
};

class Encryptor
{
public:
    void encrypt(const std::string &inputFileName, const std::string &outputFileName)
    {
        std::ifstream inputFile(inputFileName);
        if (!inputFile.is_open())
        {
            std::cerr << "Помилка відкриття файлу: " << inputFileName << std::endl;
            return;
        }

        std::ofstream outputFile(outputFileName, std::ios::binary);
        if (!outputFile.is_open())
        {
            std::cerr << "Помилка відкриття файлу: " << outputFileName << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inputFile, line))
        {
            line = padLine(line);
            for (char ch : line)
            {
                EncryptedChar encryptedChar;
                encryptedChar.row = (ch / 16) & 0b1111;
                encryptedChar.upperAscii = (ch / 16) >> 4;
                encryptedChar.lowerAscii = ch & 0b1111;
                encryptedChar.position = (line.find(ch) % 16) & 0b11;

                // Розрахунок та встановлення бітів парності
                encryptedChar.parity1 = calculateParity(encryptedChar.upperAscii, encryptedChar.row);
                encryptedChar.parity2 = calculateParity(encryptedChar.lowerAscii, encryptedChar.position);

                // Запис шифрованого символу у вихідний файл
                outputFile.write(reinterpret_cast<char *>(&encryptedChar), sizeof(EncryptedChar));
            }
        }

        inputFile.close();
        outputFile.close();
    }

private:
    std::string padLine(const std::string &line)
    {
        std::string paddedLine = line;
        while (paddedLine.size() < 16)
        {
            paddedLine += ' ';
        }
        return paddedLine;
    }

    // Функція для обчислення біту парності
    unsigned calculateParity(unsigned value1, unsigned value2)
    {
        return (value1 + value2) % 2;
    }
};

class Decryptor
{
public:
    void decrypt(const std::string &inputFileName, const std::string &outputFileName)
    {
        std::ifstream inputFile(inputFileName, std::ios::binary);
        if (!inputFile.is_open())
        {
            std::cerr << "Помилка відкриття файлу: " << inputFileName << std::endl;
            return;
        }

        std::ofstream outputFile(outputFileName);
        if (!outputFile.is_open())
        {
            std::cerr << "Помилка відкриття файлу: " << outputFileName << std::endl;
            return;
        }

        EncryptedChar encryptedChar;
        while (inputFile.read(reinterpret_cast<char *>(&encryptedChar), sizeof(EncryptedChar)))
        {
            char ch = (encryptedChar.upperAscii << 4) | encryptedChar.lowerAscii;
            outputFile.put(ch);
        }

        inputFile.close();
        outputFile.close();
    }
};

int main()
{
    Encryptor encryptor;
    Decryptor decryptor;

    encryptor.encrypt("input.txt", "encrypted.bin");
    decryptor.decrypt("encrypted.bin", "decrypted.txt");

    std::cout << "Інформація була успішно зашифрована та розшифрована." << std::endl;

    return 0;
}
