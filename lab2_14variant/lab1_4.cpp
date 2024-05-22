#include <iostream>
#include <vector>

// Клас для представлення слова (пари байтів) з контрольною сумою
class Word {
private:
    unsigned char byte1; // Перший байт
    unsigned char byte2; // Другий байт

public:
    // Конструктор класу, приймає значення першого та другого байта
    Word(unsigned char byte1, unsigned char byte2) : byte1(byte1), byte2(byte2) {}

    // Метод для перевірки контрольної суми (CRC) слова
    bool checkCRC() const {
        // Розрахунок контрольної суми для непарних та парних бітів
        bool oddSum = (getBit(byte1, 7) + getBit(byte1, 5) + getBit(byte1, 3) + getBit(byte1, 1) +
                       getBit(byte2, 7) + getBit(byte2, 5) + getBit(byte2, 3) + getBit(byte2, 1)) % 2 == 0;
        bool evenSum = (getBit(byte1, 6) + getBit(byte1, 4) + getBit(byte1, 2) + getBit(byte1, 0) +
                        getBit(byte2, 6) + getBit(byte2, 4) + getBit(byte2, 2) + getBit(byte2, 0)) % 2 == 0;

        // Порівняння отриманих контрольних сум з переданими
        return (oddSum == getBit(byte1, 6)) && (evenSum == getBit(byte1, 7));
    }

private:
    // Метод для отримання значення біта за його позицією у байті
    bool getBit(unsigned char byte, int position) const {
        return (byte >> position) & 1;
    }
};

int main() {
    // Передана послідовність слів (пар байтів)
    std::vector<Word> transmittedWords = {
        Word(0b10101010, 0b11001100),
        Word(0b11110000, 0b00001111),
        Word(0b01010101, 0b10101010)
    };

    // Перевірка контрольних сум для кожного слова
    for (int i = 0; i < transmittedWords.size(); ++i) {
        if (transmittedWords[i].checkCRC()) {
            std::cout << "Слово " << i + 1 << " передано без помилок." << std::endl;
        } else {
            std::cout << "Слово " << i + 1 << " містить помилки." << std::endl;
        }
    }

    return 0;
}
