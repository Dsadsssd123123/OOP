#include <iostream>
#include <string>

// Клас кнопки
class Button {
public:
    void press() const {
        std::cout << "Button pressed!" << std::endl;
    }
};

// Клас заголовка
class Title {
private:
    std::string text;

public:
    Title(const std::string& t) : text(t) {}

    void display() const {
        std::cout << "Title: " << text << std::endl;
    }
};

// Клас вікна
class Window {
private:
    Title title;
    Button button;

public:
    Window(const std::string& t) : title(t) {}

    void addButtonCallback(void (*callback)()) {
        // Метод, який навішує функцію зворотного виклику на кнопку
        // В даному випадку ми передаємо вказівник на функцію void, яка не має аргументів
        // Це дозволяє нам викликати будь-яку функцію, яка має такий самий сигнатур
        // Ви можете також використовувати функціональні об'єкти або методи класу Window з відповідними параметрами
        // Ця функція буде викликатися при натисканні кнопки
        buttonCallback = callback;
    }

    void display() const {
        title.display();
    }

    void pressButton() const {
        button.press();
        if (buttonCallback != nullptr) {
            // Виклик функції зворотного виклику при натисканні кнопки
            buttonCallback();
        }
    }

private:
    void (*buttonCallback)(); // Вказівник на функцію зворотного виклику
};

// Функція зворотного виклику
void buttonCallbackFunction() {
    std::cout << "Callback function called!" << std::endl;
}

int main() {
    Window window("My Window");
    window.addButtonCallback(buttonCallbackFunction);

    std::cout << "Displaying window:" << std::endl;
    window.display();

    std::cout << "Pressing button:" << std::endl;
    window.pressButton();

    return 0;
}
