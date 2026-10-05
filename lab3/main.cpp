#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

const double PI = 3.14159265358979;

// ============================================================
// УРОВЕНЬ 1: абстрактный класс Tara
// ============================================================
class Tara {
protected:
    double volume;
    string material;

public:
    Tara() : volume(0.0), material("не указан") {
        cout << "[Тара] конструктор по умолчанию" << endl;
    }

    Tara(double v, const string& m) : volume(v), material(m) {
        cout << "[Тара] конструктор с параметрами" << endl;
    }

    virtual ~Tara() {
        cout << "[Тара] деструктор" << endl;
    }

    virtual void info() const = 0;

    virtual void input() {
        cout << "  Введите объём тары (л): ";
        while (!(cin >> volume) || volume < 0) {
            cout << "  Ошибка! Введите неотрицательное число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "  Введите материал тары: ";
        getline(cin, material);
        if (material.empty()) material = "не указан";
    }

    virtual void output() const {
        cout << "  Объём: " << volume << " л" << endl;
        cout << "  Материал: " << material << endl;
    }

    double getVolume() const { return volume; }
    string getMaterial() const { return material; }
};

// ============================================================
// УРОВЕНЬ 2: Box
// ============================================================
class Box : public Tara {
protected:
    double length;
    double width;
    double height;
    bool hasLid;

public:
    Box() : Tara(), length(0), width(0), height(0), hasLid(false) {
        cout << "[Ящик] конструктор по умолчанию" << endl;
    }

    Box(double v, const string& m, double l, double w, double h, bool lid)
        : Tara(v, m), length(l), width(w), height(h), hasLid(lid) {
        cout << "[Ящик] конструктор с параметрами" << endl;
    }

    ~Box() {
        cout << "[Ящик] деструктор" << endl;
    }

    void input() override {
        Tara::input();

        cout << "  Введите длину ящика (см): ";
        while (!(cin >> length) || length < 0) {
            cout << "  Ошибка! Введите неотрицательное число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "  Введите ширину ящика (см): ";
        while (!(cin >> width) || width < 0) {
            cout << "  Ошибка! Введите неотрицательное число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "  Введите высоту ящика (см): ";
        while (!(cin >> height) || height < 0) {
            cout << "  Ошибка! Введите неотрицательное число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "  Есть крышка? (1 - да, 0 - нет): ";
        int lid;
        while (!(cin >> lid) || (lid != 0 && lid != 1)) {
            cout << "  Ошибка! Введите 0 или 1: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        hasLid = (lid == 1);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void output() const override {
        Tara::output();
        cout << "  Габариты (Д x Ш x В): "
            << length << " x " << width << " x " << height << " см" << endl;
        cout << "  Крышка: " << (hasLid ? "есть" : "нет") << endl;
    }

    void info() const override {
        cout << "=== ЯЩИК ===" << endl;
        Tara::output();
        cout << "  Габариты (Д x Ш x В): "
            << length << " x " << width << " x " << height << " см" << endl;
        cout << "  Крышка: " << (hasLid ? "есть" : "нет") << endl;
    }
};

// ============================================================
// УРОВЕНЬ 3: BottleBox
// ============================================================
class BottleBox : public Box {
private:
    int bottleCount;
    double bottleDiameter;

public:
    BottleBox() : Box(), bottleCount(0), bottleDiameter(0.0) {
        cout << "[Ящик для бутылок] конструктор по умолчанию" << endl;
    }

    BottleBox(double v, const string& m,
        double l, double w, double h, bool lid,
        int count, double diam)
        : Box(v, m, l, w, h, lid),
        bottleCount(count), bottleDiameter(diam) {
        cout << "[Ящик для бутылок] конструктор с параметрами" << endl;
    }

    ~BottleBox() {
        cout << "[Ящик для бутылок] деструктор" << endl;
    }

    void input() override {
        Box::input();

        cout << "  Введите количество бутылок: ";
        while (!(cin >> bottleCount) || bottleCount < 0) {
            cout << "  Ошибка! Введите неотрицательное целое: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "  Введите диаметр бутылки (см): ";
        while (!(cin >> bottleDiameter) || bottleDiameter < 0) {
            cout << "  Ошибка! Введите неотрицательное число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void output() const override {
        Box::output();
        cout << "  Количество бутылок: " << bottleCount << endl;
        cout << "  Диаметр бутылки: " << bottleDiameter << " см" << endl;
    }

    void info() const override {
        cout << "=== ЯЩИК ДЛЯ БУТЫЛОК ===" << endl;
        Box::output();
        cout << "  Количество бутылок: " << bottleCount << endl;
        cout << "  Диаметр бутылки: " << bottleDiameter << " см" << endl;

        if (bottleCount > 0 && bottleDiameter > 0) {
            double r = bottleDiameter / 2.0;
            double useful = PI * r * r * height * bottleCount;
            cout << "  Полезный объём под бутылки: "
                << fixed << setprecision(2) << useful << " см^3" << endl;
        }
    }
};

// ============================================================
// Второй наследник Tara: Cistern
// ============================================================
class Cistern : public Tara {
private:
    double radius;
    double lengthC;

public:
    Cistern() : Tara(), radius(0.0), lengthC(0.0) {
        cout << "[Цистерна] конструктор по умолчанию" << endl;
    }

    Cistern(double v, const string& m, double r, double l)
        : Tara(v, m), radius(r), lengthC(l) {
        cout << "[Цистерна] конструктор с параметрами" << endl;
    }

    ~Cistern() {
        cout << "[Цистерна] деструктор" << endl;
    }

    void input() override {
        Tara::input();

        cout << "  Введите радиус цистерны (см): ";
        while (!(cin >> radius) || radius < 0) {
            cout << "  Ошибка! Введите неотрицательное число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "  Введите длину цистерны (см): ";
        while (!(cin >> lengthC) || lengthC < 0) {
            cout << "  Ошибка! Введите неотрицательное число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void output() const override {
        Tara::output();
        cout << "  Радиус: " << radius << " см" << endl;
        cout << "  Длина: " << lengthC << " см" << endl;
    }

    void info() const override {
        cout << "=== ЦИСТЕРНА ===" << endl;
        Tara::output();
        cout << "  Радиус: " << radius << " см" << endl;
        cout << "  Длина: " << lengthC << " см" << endl;

        if (radius > 0 && lengthC > 0) {
            double v = PI * radius * radius * lengthC;
            cout << "  Геометрический объём: "
                << fixed << setprecision(2) << v << " см^3" << endl;
        }
    }
};

// ============================================================
// Демонстрация полиморфизма
// ============================================================
void demonstratePolymorphism() {
    cout << "\n========== ДЕМОНСТРАЦИЯ ПОЛИМОРФИЗМА ==========" << endl;

    Tara* ptr = nullptr;

    cout << "\n--- BottleBox через Tara* ---" << endl;
    ptr = new BottleBox(20.0, "пластик", 40.0, 30.0, 25.0, true, 12, 7.5);
    ptr->info();
    delete ptr;
    ptr = nullptr;

    cout << "\n--- Cistern через тот же Tara* ---" << endl;
    ptr = new Cistern(1000.0, "сталь", 50.0, 200.0);
    ptr->info();
    delete ptr;
    ptr = nullptr;

    cout << "\n--- Box через Tara* ---" << endl;
    ptr = new Box(30.0, "дерево", 60.0, 40.0, 35.0, false);
    ptr->info();
    delete ptr;

    cout << "\n===============================================" << endl;
}

// ============================================================
// Меню
// ============================================================
void printMenu() {
    cout << "\n============= МЕНЮ =============" << endl;
    cout << "1. Создать BottleBox (по умолчанию)" << endl;
    cout << "2. Создать BottleBox (с параметрами)" << endl;
    cout << "3. Создать Cistern (с параметрами)" << endl;
    cout << "4. Демонстрация полиморфизма" << endl;
    cout << "5. Вывести output() текущего объекта" << endl;
    cout << "6. Вызвать info() текущего объекта" << endl;
    cout << "0. Выход" << endl;
    cout << "=================================" << endl;
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    Tara* current = nullptr;
    int choice = -1;

    do {
        printMenu();

        if (!(cin >> choice)) {
            cout << "Ошибка ввода! Введите число." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            cout << "\n--- Создание BottleBox (по умолчанию) ---" << endl;
            delete current;
            current = new BottleBox();
            current->input();
            cout << "Объект создан." << endl;
            break;

        case 2:
            cout << "\n--- Создание BottleBox (с параметрами) ---" << endl;
            delete current;
            current = new BottleBox(20.0, "пластик",
                40.0, 30.0, 25.0, true, 12, 7.5);
            current->output();
            break;

        case 3:
            cout << "\n--- Создание Cistern (с параметрами) ---" << endl;
            delete current;
            current = new Cistern(1000.0, "сталь", 50.0, 200.0);
            current->output();
            break;

        case 4:
            demonstratePolymorphism();
            break;

        case 5:
            if (current == nullptr) {
                cout << "Объект не создан!" << endl;
            }
            else {
                cout << "\n--- output() текущего объекта ---" << endl;
                current->output();
            }
            break;

        case 6:
            if (current == nullptr) {
                cout << "Объект не создан!" << endl;
            }
            else {
                cout << "\n--- info() текущего объекта ---" << endl;
                current->info();
            }
            break;

        case 0:
            cout << "\nЗавершение работы..." << endl;
            break;

        default:
            cout << "Неверный пункт меню!" << endl;
        }
    } while (choice != 0);

    if (current != nullptr) {
        cout << "\nУдаление текущего объекта:" << endl;
        delete current;
        current = nullptr;
    }

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
