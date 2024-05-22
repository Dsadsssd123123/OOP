#include <iostream>

// Вузол однозв'язного списку
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& newData) : data(newData), next(nullptr) {}
};

// Клас однозв'язного списку
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    // Додавання елементу в кінець списку
    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        ++size;
    }

    // Виведення елементів списку
    void display() const {
        Node<T>* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Деструктор для звільнення пам'яті
    ~LinkedList() {
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    LinkedList<int> intList;
    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);
    std::cout << "Елементи списку intList: ";
    intList.display();

    LinkedList<std::string> strList;
    strList.push_back("apple");
    strList.push_back("banana");
    strList.push_back("orange");
    std::cout << "Елементи списку strList: ";
    strList.display();

    return 0;
}
