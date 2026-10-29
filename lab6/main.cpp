#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class route {
    int number;          // номер маршрута
    string start;        // начальный пункт
    string finish;       // конечный пункт
    double cost;         // стоимость проезда
    double time;         // время в пути

public:
    route() : number(0), start(""), finish(""), cost(0), time(0) {}
    route(int n, string s, string f, double c, double t)
        : number(n), start(s), finish(f), cost(c), time(t) {}

    // 1) ! как унарный метод класса — изменяет конечный пункт
    route operator!() {
        finish = finish + "_new";
        return *this;
    }

    // 2) -- (префиксный) как унарная дружественная функция — уменьшает стоимость на 3%
    friend route operator--(route &r);

    // 3) -- как бинарный метод класса — разность стоимости двух маршрутов
    double operator-(const route &r) const {
        return cost - r.cost;
    }

    // 4) -- как бинарная дружественная функция — совпадают ли начальные и конечные пункты
    friend bool operator--(const route &a, const route &b);

    // перегрузка вывода
    friend ostream& operator<<(ostream &os, const route &r) {
        os << "Маршрут #" << r.number
           << " | " << r.start << " -> " << r.finish
           << " | стоимость: " << r.cost
           << " | время: " << r.time;
        return os;
    }

    // перегрузка ввода
    friend istream& operator>>(istream &is, route &r) {
        cout << "Номер маршрута: "; is >> r.number;
        cout << "Начальный пункт: "; is >> r.start;
        cout << "Конечный пункт: "; is >> r.finish;
        cout << "Стоимость проезда: "; is >> r.cost;
        cout << "Время в пути: "; is >> r.time;
        return is;
    }
};

// унарный -- : уменьшение стоимости на 3%
route operator--(route &r) {
    r.cost -= r.cost * 0.03;
    return r;
}

// бинарный -- : проверка совпадения начального и конечного пунктов
bool operator--(const route &a, const route &b) {
    return (a.start == b.start) && (a.finish == b.finish);
}

int main() {
    setlocale(LC_ALL, "Russian");

    route r1(24, "Севастополь", "Ялта", 500, 2.5);
    route r2(25, "Симферополь", "Алушта", 350, 1.8);

    cout << "Исходные маршруты:\n" << r1 << "\n" << r2 << "\n\n";

    // 1) унарный !
    cout << "После !r1 (изменён конечный пункт):\n" << !r1 << "\n\n";

    // 2) унарный --
    cout << "После --r1 (стоимость -3%):\n" << --r1 << "\n\n";

    // 3) бинарный - (метод класса)
    cout << "Разность стоимости r1 и r2: " << (r1 - r2) << "\n\n";

    // 4) бинарный -- (дружественная)
    cout << "Начальные и конечные пункты совпадают? "
         << ((r1 -- r2) ? "да" : "нет") << "\n\n";

    // ввод через перегруженный >>
    route r3;
    cout << "Введите третий маршрут:\n";
    cin >> r3;
    cout << "\nВы ввели:\n" << r3 << "\n";

    return 0;
}
