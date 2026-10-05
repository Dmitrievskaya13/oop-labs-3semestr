#define NOMINMAX
#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <iostream>
#include <string>
#include <limits>
#include <clocale>

using namespace std;


class Route {
private:
    int number;          // номер маршрута
    string startPoint;   // начальный пункт
    string endPoint;     // конечный пункт
    double cost;         // стоимость проезда
    double travelTime;   // время в пути

public:
    // Конструктор по умолчанию
    Route() : number(0), startPoint(""), endPoint(""), cost(0), travelTime(0) {}

    // Конструктор с параметрами
    Route(int n, const string& sp, const string& ep, double c, double t)
        : number(n), startPoint(sp), endPoint(ep), cost(c), travelTime(t) {}

    // Деструктор
    ~Route() {}

    // Метод ввода данных
    void input() {
        cout << "Введите номер маршрута: ";
        cin >> number;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Введите начальный пункт: ";
        getline(cin, startPoint);

        cout << "Введите конечный пункт: ";
        getline(cin, endPoint);

        cout << "Введите стоимость проезда: ";
        cin >> cost;

        cout << "Введите время в пути: ";
        cin >> travelTime;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Метод вывода данных
    void print() const {
        cout << "Номер маршрута: " << number << endl;
        cout << "Начальный пункт: " << startPoint << endl;
        cout << "Конечный пункт: " << endPoint << endl;
        cout << "Стоимость проезда: " << cost << endl;
        cout << "Время в пути: " << travelTime << endl;
    }

    // Метод обработки данных
    void process(const string& targetEnd) const {
        if (endPoint == targetEnd) {
            cout << "Найден маршрут № " << number << endl;
        }
        else {
            cout << "Маршрут, прибывающий в пункт \"" << targetEnd
                << "\", не найден." << endl;
        }
    }
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

   
    Route r1, r2;

    bool hasData1 = false;
    bool hasData2 = false;

    int choice;

    do {
        cout << "\n===== МЕНЮ =====\n";
        cout << "1. Ввод маршрута №1\n";
        cout << "2. Ввод маршрута №2\n";
        cout << "3. Вывод обоих маршрутов\n";
        cout << "4. Обработка данных\n";
        cout << "5. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "\n=== Ввод маршрута №1 ===\n";
            r1.input();
            hasData1 = true;
            break;

        case 2:
            cout << "\n=== Ввод маршрута №2 ===\n";
            r2.input();
            hasData2 = true;
            break;

        case 3:
            if (hasData1) {
                cout << "\n--- Маршрут №1 ---\n";
                r1.print();
            }
            else {
                cout << "Маршрут №1 не введён!\n";
            }
            if (hasData2) {
                cout << "\n--- Маршрут №2 ---\n";
                r2.print();
            }
            else {
                cout << "Маршрут №2 не введён!\n";
            }
            break;

        case 4: {
            if (!hasData1 && !hasData2) {
                cout << "Данные не введены!\n";
                break;
            }
            string target;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите название конечного пункта: ";
            getline(cin, target);

            if (hasData1) {
                cout << "\n--- Результат для маршрута №1 ---\n";
                r1.process(target);
            }
            if (hasData2) {
                cout << "\n--- Результат для маршрута №2 ---\n";
                r2.process(target);
            }
            break;
        }

        case 5:
            cout << "Выход из программы.\n";
            break;

        default:
            cout << "Неверный пункт меню!\n";
        }

    } while (choice != 5);

    return 0;
}
