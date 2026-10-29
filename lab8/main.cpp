#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

class RightTriangle {
    double a, b;       // катеты
    string color;

public:
    // заполнение с клавиатуры с проверкой потока и корректности данных
    void input() {
        cout << "Катет a: ";
        cin >> a;
        if (!cin) throw string("Ошибка ввода катета a");
        if (a <= 0) throw string("Катет a должен быть положительным");

        cout << "Катет b: ";
        cin >> b;
        if (!cin) throw string("Ошибка ввода катета b");
        if (b <= 0) throw string("Катет b должен быть положительным");

        cout << "Цвет: ";
        cin >> color;
        if (!cin) throw string("Ошибка ввода цвета");
    }

    // площадь по формуле S = 0.5 * a * b
    double area() const {
        return 0.5 * a * b;
    }

    // вывод с форматированием:
    // 19 позиций, точность 5, пробел -> '}', выравнивание по правому краю
    void printArea() const {
        cout << setfill('}') << right
             << setw(19) << setprecision(5) << fixed
             << area() << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    RightTriangle t;

    try {
        t.input();
        cout << "Площадь: ";
        t.printArea();
    }
    catch (string &e) {
        cout << "Исключение: " << e << endl;
        // сброс состояния потока и очистка буфера
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // вторая попытка — корректный ввод
    try {
        cout << "\nПовторный ввод:\n";
        t.input();
        cout << "Площадь: ";
        t.printArea();
    }
    catch (string &e) {
        cout << "Исключение: " << e << endl;
    }

    cout << "Программа завершена.\n";
    return 0;
}
