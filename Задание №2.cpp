#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
using namespace std;

/*
 * Программа демонстрирации работы методов базового и производного классов на примере нахождения прощади разных фигур
 */

// Базовый класс:
class Shape {
protected:
    string name;
public:
    Shape(string n) : name(n) {}
    // Метод базового класса:
    void printHeader() {
        cout << "\n--- Фигура: " << name << " ---" << endl;
    }
};

// Производный класс:
class Rectangle : public Shape {
protected:
    double width, height;
public:
    Rectangle() : Shape("Прямоугольник"), width(0), height(0) {}
    // Методы производного класса:
    void input(double w, double h) {
        width = w; height = h;
    }
    void calculate() {
        cout << "Площадь прямоугольника: " << width * height << endl;
    }
};

// Производный класс от Rectangle:
class Square : public Rectangle {
public:
    Square() : Rectangle() { name = "Квадрат"; }
    void input(double side) {
        width = side; height = side;
    }
    void calculate() {
        cout << "Площадь квадрата: " << width * width << endl;
    }
};

// Еще один производный класс:
class Triangle : public Shape {
private:
    double base, h;
public:
    Triangle() : Shape("Треугольник"), base(0), h(0) {}
    void input(double b, double heightVal) {
        base = b; h = heightVal;
    }
    void calculate() {
        cout << "Площадь треугольника: " << 0.5 * base * h << endl;
    }
};

// Обработка исключений:
double getSafeDouble(string prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ОШИБКА: Введены буквы! Введите число." << endl;
            continue;
        }
        try {
            if (value <= 0) throw invalid_argument("Число должно быть больше 0");
            return value;
        }
        catch (const invalid_argument& e) {
            cout << "ОШИБКА: " << e.what() << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    while (true) {
        cout << "\n--- КАЛЬКУЛЯТОР ПЛОЩАДИ ФИГУР --- " << endl;
        cout << "1. Прямоугольник\n2. Квадрат\n3. Треугольник\n0. Выход" << endl;
        cout << "Ваш выбор: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ОШИБКА: В меню нужно вводить цифры!" << endl;
            continue;
        }

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            Rectangle r;
            r.printHeader(); // Метод базового класса
            double w = getSafeDouble("Введите ширину: ");
            double h = getSafeDouble("Введите высоту: ");
            r.input(w, h);   // Метод производного класса
            r.calculate();
            break;
        }
        case 2: {
            Square s;
            s.printHeader();
            double side = getSafeDouble("Введите сторону: ");
            s.input(side);
            s.calculate();
            break;
        }
        case 3: {
            Triangle t;
            t.printHeader();
            double b = getSafeDouble("Введите основание: ");
            double hv = getSafeDouble("Введите высоту: ");
            t.input(b, hv);
            t.calculate();
            break;
        }
        default:
            cout << "ОШИБКА: Такого пункта нет." << endl;
        }
    }
    return 0;
}
