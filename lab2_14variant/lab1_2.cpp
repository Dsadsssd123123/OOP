#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Encryptor
{
public:
    // Функція для шифрування інформації та запису у бінарний файл
    void encrypt(const std::string &inputFileName, const std::string &outputFileName)
    {
        // Відкриття вхідного текстового файлу для читання
        std::ifstream inputFile(inputFileName);
        if (!inputFile.is_open())
        {
            std::cerr << "Помилка відкриття файлу: " << inputFileName << std::endl;
            return;
        }

        // Відкриття вихідного бінарного файлу для запису
        std::ofstream outputFile(outputFileName, std::ios::binary);
        if (!outputFile.is_open())
        {
            std::cerr << "Помилка відкриття файлу: " << outputFileName << std::endl;
            return;
        }

        // Зчитування рядків з вхідного файлу та їх шифрування
        std::string line;
        while (std::getline(inputFile, line))
        {
            line = padLine(line); // Доповнення рядка пробілами до 16 символів
            for (char ch : line)
            {
                // Розрахунок компонентів байтів для кожного символу
                int row = (ch / 16) & 0b1111;
                int upperAscii = (ch / 16) >> 4;
                int lowerAscii = ch & 0b1111;
                int position = (line.find(ch) % 16) & 0b11;

                // Створення байтів та запис їх у вихідний файл
                char byte1 = (row << 4) | (upperAscii & 0b1111);
                char byte2 = (upperAscii >> 4) | ((position << 2) & 0b1100) | (lowerAscii << 4);
                outputFile.put(byte1);
                outputFile.put(byte2);
            }
        }

        // Закриття файлів
        inputFile.close();
        outputFile.close();
    }

private:
    // Функція для доповнення рядка пробілами до 16 символів
    std::string padLine(const std::string &line)
    {
        std::string paddedLine = line;
        while (paddedLine.size() < 16)
        {
            paddedLine += ' ';
        }
        return paddedLine;
    }
};

class Decryptor
{
public:
    // Функція для розшифрування інформації та запису у текстовий файл
    void decrypt(const std::string &inputFileName, const std::string &outputFileName)
    {
        // Відкриття вхідного бінарного файлу для читання
        std::ifstream inputFile(inputFileName, std::ios::binary);
        if (!inputFile.is_open())
        {
            std::cerr << "Помилка відкриття файлу: " << inputFileName << std::endl;
            return;
        }

        // Відкриття вихідного текстового файлу для запису
        std::ofstream outputFile(outputFileName);
        if (!outputFile.is_open())
        {
            std::cerr << "Помилка відкриття файлу: " << outputFileName << std::endl;
            return;
        }

        // Зчитування байтів з вхідного файлу та їх розшифрування
        char byte1, byte2;
        while (inputFile.get(byte1) && inputFile.get(byte2))
        {
            // Розрахунок компонентів символу для кожного байта
            int row = (byte1 >> 4) & 0b1111;
            int upperAscii = ((byte1 & 0b1111) << 4) | ((byte2 >> 4) & 0b1111);
            int lowerAscii = byte2 & 0b1111;
            int position = (byte2 >> 2) & 0b11;

            // Створення символу та запис його у вихідний файл
            char ch = (upperAscii << 4) | lowerAscii;
            outputFile.put(ch);
        }

        // Закриття файлів
        inputFile.close();
        outputFile.close();
    }
};

int main()
{
    Encryptor encryptor;
    Decryptor decryptor;

    // Шифрування інформації та запис у бінарний файл
    encryptor.encrypt("input.txt", "encrypted.bin");
    // Розшифрування інформації та запис у текстовий файл
    decryptor.decrypt("encrypted.bin", "decrypted.txt");

    std::cout << "Інформація була успішно зашифрована та розшифрована." << std::endl;

    return 0;
}
