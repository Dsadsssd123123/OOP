#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <optional>

using namespace std;

class ArrayManager
{
public:
    // Функція введення масиву з консолі
    vector<int> inputArrayFromConsole()
    {
        int n;
        cout << "Введіть розмір масиву: ";
        cin >> n;
        vector<int> arr(n);
        cout << "Введіть елементи масиву: ";
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        return arr;
    }

    // Функція запису масиву в текстовий файл
    void writeArrayToTextFile(const vector<int> &arr, const string &filename)
    {
        ofstream outFile(filename);
        if (outFile.is_open())
        {
            for (int elem : arr)
            {
                outFile << elem << " ";
            }
            outFile.close();
        }
        else
        {
            cerr << "Не вдалося відкрити файл для запису." << endl;
        }
    }

    // Функція введення розміру масиву з консолі, створення масиву з випадкових чисел і запис його в бінарний файл
    void createRandomArrayAndWriteToBinaryFile(const string &filename)
    {
        int n;
        cout << "Введіть розмір масиву: ";
        cin >> n;
        vector<int> arr(n);
        srand(time(0));
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % 200 - 100; // Генерація випадкових чисел в діапазоні [-100, 99]
        }
        ofstream outFile(filename, ios::binary);
        if (outFile.is_open())
        {
            outFile.write(reinterpret_cast<const char *>(arr.data()), arr.size() * sizeof(int));
            outFile.close();
        }
        else
        {
            cerr << "Не вдалося відкрити файл для запису." << endl;
        }
    }

    // Функція зчитування масиву з бінарного файлу
    vector<int> readArrayFromBinaryFile(const string &filename)
    {
        ifstream inFile(filename, ios::binary);
        vector<int> arr;
        if (inFile.is_open())
        {
            inFile.seekg(0, ios::end);
            size_t size = inFile.tellg() / sizeof(int);
            inFile.seekg(0, ios::beg);
            arr.resize(size);
            inFile.read(reinterpret_cast<char *>(arr.data()), size * sizeof(int));
            inFile.close();
        }
        else
        {
            cerr << "Не вдалося відкрити файл для читання." << endl;
        }
        return arr;
    }

    // Функція для пошуку номера першого максимального значення серед від'ємних елементів, розташованих до першого елемента, рівного Т
    optional<int> findFirstMaxNegativeBeforeT(const vector<int> &arr, int T)
    {
        int maxNegative = INT_MIN;
        optional<int> maxIndex;
        for (size_t i = 0; i < arr.size(); i++)
        {
            if (arr[i] == T)
            {
                break;
            }
            if (arr[i] < 0 && arr[i] > maxNegative)
            {
                maxNegative = arr[i];
                maxIndex = i;
            }
        }
        return maxIndex;
    }

    // Функція виведення масиву в консоль
    void printArray(const vector<int> &arr)
    {
        for (int elem : arr)
        {
            cout << elem << " ";
        }
        cout << endl;
    }
};

int main()
{
    ArrayManager manager;

    // a. Введення масиву з консолі та запис у текстовий файл
    vector<int> arrayFromConsole = manager.inputArrayFromConsole();
    manager.writeArrayToTextFile(arrayFromConsole, "array.txt");

    // b. Створення випадкового масиву та запис у бінарний файл
    manager.createRandomArrayAndWriteToBinaryFile("randomArray.bin");

    // c. Зчитування масиву з бінарного файлу
    vector<int> arrayFromBinaryFile = manager.readArrayFromBinaryFile("randomArray.bin");

    // Введення значення Т
    int T;
    cout << "Введіть значення Т: ";
    cin >> T;

    // Пошук першого максимального значення серед від'ємних елементів до першого елемента, рівного Т
    optional<int> resultIndex = manager.findFirstMaxNegativeBeforeT(arrayFromBinaryFile, T);

    // Виведення результату
    if (resultIndex.has_value())
    {
        cout << "Номер першого максимального значення серед від'ємних елементів до першого елемента, рівного " << T << ": " << resultIndex.value() << endl;
    }
    else
    {
        cout << "Від'ємні елементи до першого елемента, рівного " << T << ", не знайдені." << endl;
    }

    return 0;
}
