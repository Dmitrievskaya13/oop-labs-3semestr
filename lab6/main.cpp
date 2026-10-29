#define NOMINMAX
#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <iostream>
#include <string>
#include <limits>
#include <clocale>
#include <stdexcept>

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

    // Геттеры 
    // я не шарю если честно зачем они нужны и что это такое, но они тут есть и хорошо, значит так надо
    int getNumber() const { return number; }
    string getStartPoint() const { return startPoint; }
    string getEndPoint() const { return endPoint; }
    double getCost() const { return cost; }
    double getTravelTime() const { return travelTime; }

    // Метод ввода данных с проверкой ошибок, чтоб кринжово не вводили, а нормальные данные только
    void input() {
        cout << "Введите номер маршрута: ";
        if (!(cin >> number)) {
            cin.clear(); //сбрасывает ошибку которая там получилась
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //очистка буфера
            throw runtime_error("Ошибка ввода номера маршрута!"); //вот это кринж какой-то тхроу типа делает ошибку, чтоб потом её в мейне было видно
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //убираем окончание строки потому что дальше гетлайны

        cout << "Введите начальный пункт: ";
        getline(cin, startPoint);

        cout << "Введите конечный пункт: ";
        getline(cin, endPoint);

        cout << "Введите стоимость проезда: ";
        if (!(cin >> cost) || cost < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Ошибка ввода стоимости проезда (должна быть >= 0)!"); //опять этот тхроу
        }

        cout << "Введите время в пути: ";
        if (!(cin >> travelTime) || travelTime < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Ошибка ввода времени в пути (должно быть >= 0)!"); //и тут тоже
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Метод вывода данных
    void print() const {
        cout << "Номер маршрута:     " << number << endl;
        cout << "Начальный пункт:    " << startPoint << endl;
        cout << "Конечный пункт:     " << endPoint << endl;
        cout << "Стоимость проезда:  " << cost << endl;
        cout << "Время в пути:       " << travelTime << endl;
    }

    // ================= ПЕРЕГРУЖЕННЫЕ ОПЕРАТОРЫ НАКОНЕЦ-ТО!!!!!!!!!! =================

    // 1) Унарный оператор ! — метод класса.
    //    Изменяет конечный пункт.

    Route& operator!() {
        endPoint = "Изменённый пункт";
        return *this; //возвращаем сам объект (*this — это текущий объект) че я не понимаю ничего блин
    }

    // 3) Бинарный оператор - — метод класса.
    //    Разность стоимости проезда двух маршрутов.

    double operator-(const Route& other) const { //Один параметр — потому что левый операнд — сам объект (*this), а правый — other
        return cost - other.cost;
    }

    // 2) Префиксный -- — дружественная функция (уменьшение цены на 3%)
    friend Route& operator--(Route& r);

    // 4) == — дружественная функция (совпадение начального и конечного пунктов)
    friend bool operator==(const Route& a, const Route& b);

    // Операторы ввода/вывода
    friend ostream& operator<<(ostream& os, const Route& r);
    friend istream& operator>>(istream& is, Route& r);
};


// ====== Реализация дружественных функций ======

// 2) Префиксный -- : уменьшение стоимости на 3%
Route& operator--(Route& r) {
    r.cost -= r.cost * 0.03;
    return r;
}

// 4) == : сравнение начального и конечного пунктов
bool operator==(const Route& a, const Route& b) {
    return (a.startPoint == b.startPoint) && (a.endPoint == b.endPoint);
}

// Оператор вывода <<
ostream& operator<<(ostream& os, const Route& r) {
    os << "Маршрут №" << r.number
        << " | " << r.startPoint << " -> " << r.endPoint
        << " | Стоимость: " << r.cost << " руб."
        << " | Время: " << r.travelTime << " ч";
    return os;
}

// Оператор ввода >> (использует input() с обработкой ошибок)
istream& operator>>(istream& is, Route& r) {
    r.input();
    return is;
}


// ==================== Главная функция ====================
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Route r1, r2;

    bool hasData1 = false;
    bool hasData2 = false;

    int choice = 0;

    do {
        cout << "\n===== МЕНЮ =====\n";
        cout << "1. Ввод маршрута №1\n";
        cout << "2. Ввод маршрута №2\n";
        cout << "3. Вывод обоих маршрутов (оператор <<)\n";
        cout << "4. Оператор ! (изменить конечный пункт маршрута №1)\n";
        cout << "5. Оператор -- (уменьшить стоимость маршрута №2 на 3%)\n";
        cout << "6. Оператор - (разность стоимости маршрутов)\n";
        cout << "7. Оператор == (сравнить начальный и конечный пункты)\n";
        cout << "8. Выход\n";
        cout << "Выберите пункт: ";

        // === ЗАЩИТА ОТ ЗАЦИКЛИВАНИЯ МЕНЮ ===
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Введите число от 1 до 8.\n";
            continue;
        }

        try {

            //можно я отчислюсь пожалуйста

            switch (choice) {

            case 1:
                cout << "\n=== Ввод маршрута №1 ===\n";
                cin >> r1;   // перегруженный operator>>
                hasData1 = true;
                break;

            case 2:
                cout << "\n=== Ввод маршрута №2 ===\n";
                cin >> r2;
                hasData2 = true;
                break;

            case 3:
                if (hasData1) {
                    cout << "\n--- Маршрут №1 ---\n";
                    cout << r1 << endl;   // перегруженный operator<<
                }
                else {
                    cout << "Маршрут №1 не введён!\n";
                }
                if (hasData2) {
                    cout << "\n--- Маршрут №2 ---\n";
                    cout << r2 << endl;
                }
                else {
                    cout << "Маршрут №2 не введён!\n";
                }
                break;

            case 4:
                if (!hasData1) {
                    cout << "Сначала введите маршрут №1!\n";
                    break;
                }
                !r1;   // унарный оператор ! (метод класса)
                cout << "Конечный пункт маршрута №1 изменён.\n";
                cout << r1 << endl;
                break;

            case 5:
                if (!hasData2) {
                    cout << "Сначала введите маршрут №2!\n";
                    break;
                }
                --r2;  // префиксный -- (дружественная функция)
                cout << "Стоимость маршрута №2 уменьшена на 3%.\n";
                cout << r2 << endl;
                break;

            case 6:
                if (!hasData1 || !hasData2) {
                    cout << "Нужно ввести оба маршрута!\n";
                    break;
                }
                cout << "Разность стоимости (Маршрут №1 - Маршрут №2) = "
                    << (r1 - r2) << " руб.\n";   // бинарный - (метод класса)
                break;

            case 7:
                if (!hasData1 || !hasData2) {
                    cout << "Нужно ввести оба маршрута!\n";
                    break;
                }
                if (r1 == r2)   // дружественная функция ==
                    cout << "Начальные и конечные пункты СОВПАДАЮТ.\n";
                else
                    cout << "Начальные и/или конечные пункты НЕ совпадают.\n";
                break;

            case 8:
                cout << "Выход из программы.\n";
                break;

            default:
                cout << "Неверный пункт меню! Введите число от 1 до 8.\n";
            }
        }
        catch (const exception& e) {
            cerr << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
            // После исключения в input() поток уже очищен внутри метода,
            // поэтому продолжаем работу с меню.
        }

    } while (choice != 8);

    return 0;
}
