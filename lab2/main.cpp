/*
 * Лабораторная работа № 2
 * Вариант 24: Тара -> Ящик -> Ящик для бутылок
 * Демонстрация механизма простого наследования в C++
 */

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

// ============================================================
// УРОВЕНЬ 1: Базовый класс "Тара"
// ============================================================
class Tara {
protected:
    double volume;      // объём тары (литры)
    string material;    // материал изготовления

public:
    // Конструктор по умолчанию
    Tara() : volume(0.0), material("не указан") {
        cout << "[Тара] конструктор по умолчанию" << endl;
    }

    // Конструктор с параметрами
    Tara(double v, const string& m) : volume(v), material(m) {
        cout << "[Тара] конструктор с параметрами" << endl;
    }

    // Деструктор
    ~Tara() {
        cout << "[Тара] деструктор" << endl;
    }

    // Метод ввода данных
    void input() {
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

    // Метод вывода данных
    void output() const {
        cout << "  Объём: " << volume << " л" << endl;
        cout << "  Материал: " << material << endl;
    }

    void info() const {
        cout << "=== ТАРА ===" << endl;
        cout << "  Объём: " << volume << " л" << endl;
        cout << "  Материал: " << material << endl;
    }


    double getVolume() const { return volume; }
    string getMaterial() const { return material; }
};


// УРОВЕНЬ 2
class Box : public Tara {
protected:
    double length;      // длина
    double width;       // ширина
    double height;      // высота
    bool hasLid;        // наличие крышки

public:
    // Конструктор по умолчанию
    Box() : Tara(), length(0.0), width(0.0), height(0.0), hasLid(false) {
        cout << "[Ящик] конструктор по умолчанию" << endl;
    }

    // Конструктор с параметрами
    Box(double v, const string& m,
        double l, double w, double h, bool lid)
        : Tara(v, m), length(l), width(w), height(h), hasLid(lid) {
        cout << "[Ящик] конструктор с параметрами" << endl;
    }

    // Деструктор
    ~Box() {
        cout << "[Ящик] деструктор" << endl;
    }

    // Метод ввода данных
    void input() {
        Tara::input(); // ввод унаследованных полей

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

    // Метод вывода данных
    void output() const {
        Tara::output();
        cout << "  Габариты (Д x Ш x В): " << length << " x "
            << width << " x " << height << " см" << endl;
        cout << "  Крышка: " << (hasLid ? "есть" : "нет") << endl;
    }

    // ПЕРЕОПРЕДЕЛЯЕМЫЙ метод
    void info() const {
        cout << "=== ЯЩИК ===" << endl;
        cout << "  Объём: " << volume << " л" << endl;
        cout << "  Материал: " << material << endl;
        cout << "  Габариты (Д x Ш x В): " << length << " x "
            << width << " x " << height << " см" << endl;
        cout << "  Крышка: " << (hasLid ? "есть" : "нет") << endl;
    }
};


// УРОВЕНЬ 3: Производный класс "Ящик для бутылок" 
class BottleBox : public Box {
private:
    int bottleCount;        // количество бутылок
    double bottleDiameter;  // диаметр бутылки (см)

public:
    // Конструктор по умолчанию
    BottleBox()
        : Box(), bottleCount(0), bottleDiameter(0.0) {
        cout << "[Ящик для бутылок] конструктор по умолчанию" << endl;
    }

    // Конструктор с параметрами
    BottleBox(double v, const string& m,
        double l, double w, double h, bool lid,
        int count, double diam)
        : Box(v, m, l, w, h, lid),
        bottleCount(count), bottleDiameter(diam) {
        cout << "[Ящик для бутылок] конструктор с параметрами" << endl;
    }

    // Деструктор
    ~BottleBox() {
        cout << "[Ящик для бутылок] деструктор" << endl;
    }

    // Метод ввода данных
    void input() {
        Box::input(); // ввод унаследованных полей

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

    // Метод вывода данных
    void output() const {
        Box::output();
        cout << "  Количество бутылок: " << bottleCount << endl;
        cout << "  Диаметр бутылки: " << bottleDiameter << " см" << endl;
    }

    // ПЕРЕОПРЕДЕЛЯЕМЫЙ метод
    void info() const {
        cout << "=== ЯЩИК ДЛЯ БУТЫЛОК ===" << endl;
        cout << "  Объём: " << volume << " л" << endl;
        cout << "  Материал: " << material << endl;
        cout << "  Габариты (Д x Ш x В): " << length << " x "
            << width << " x " << height << " см" << endl;
        cout << "  Крышка: " << (hasLid ? "есть" : "нет") << endl;
        cout << "  Количество бутылок: " << bottleCount << endl;
        cout << "  Диаметр бутылки: " << bottleDiameter << " см" << endl;

        // Дополнительный расчёт — полезный объём
        if (bottleCount > 0 && bottleDiameter > 0) {
            double useful = 3.14159265358979 * (bottleDiameter / 2)
                * (bottleDiameter / 2) * height * bottleCount;
            cout << "  Полезный объём под бутылки: "
                << fixed << setprecision(2) << useful << " см^3" << endl;
        }
    }
};


// Демонстрация механизма переопределения методов

void demonstratePolymorphism() {
    cout << "\n========== ДЕМОНСТРАЦИЯ ПЕРЕОПРЕДЕЛЕНИЯ ==========" << endl;

    BottleBox obj(20.0, "пластик", 40.0, 30.0, 25.0, true, 12, 7.5);

    cout << "\n--- Вызов info() у класса 1-го уровня (Тара) ---" << endl;
    obj.Tara::info();

    cout << "\n--- Вызов info() у класса 2-го уровня (Ящик) ---" << endl;
    obj.Box::info();

    cout << "\n--- Вызов info() у класса 3-го уровня (Ящик для бутылок) ---" << endl;
    obj.BottleBox::info();

    cout << "\n--- Вызов info() без указания класса (используется метод наследника) ---" << endl;
    obj.info();

    cout << "===================================================" << endl;
}


// Меню программы

void printMenu() {
    cout << "\n============= МЕНЮ =============" << endl;
    cout << "1. Создать объект (конструктор по умолчанию) и ввести данные" << endl;
    cout << "2. Создать объект (конструктор с параметрами) и вывести данные" << endl;
    cout << "3. Демонстрация переопределения методов info()" << endl;
    cout << "4. Вывести данные текущего объекта" << endl;
    cout << "5. Вызвать info() у всех уровней иерархии" << endl;
    cout << "0. Выход" << endl;
    cout << "=================================" << endl;
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    BottleBox* current = nullptr; // текущий объект (динамический)
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
        case 1: {
            cout << "\n--- Создание объекта конструктором по умолчанию ---" << endl;
            delete current;
            current = new BottleBox();
            cout << "Введите данные объекта:" << endl;
            current->input();
            cout << "\nОбъект создан и заполнен." << endl;
            break;
        }

        case 2: {
            cout << "\n--- Создание объекта конструктором с параметрами ---" << endl;
            delete current;
            // Параметры подобраны осмысленно
            current = new BottleBox(20.0, "пластик",
                40.0, 30.0, 25.0,
                true, 12, 7.5);
            cout << "Объект создан с параметрами:" << endl;
            current->output();
            break;
        }

        case 3: {
            demonstratePolymorphism();
            break;
        }

        case 4: {
            if (current == nullptr) {
                cout << "Объект ещё не создан! Сначала выберите пункт 1 или 2." << endl;
            }
            else {
                cout << "\n--- Данные текущего объекта ---" << endl;
                current->output();
            }
            break;
        }

        case 5: {
            if (current == nullptr) {
                cout << "Объект ещё не создан! Сначала выберите пункт 1 или 2." << endl;
            }
            else {
                cout << "\n--- info() уровня 1 (Тара) ---" << endl;
                current->Tara::info();
                cout << "\n--- info() уровня 2 (Ящик) ---" << endl;
                current->Box::info();
                cout << "\n--- info() уровня 3 (Ящик для бутылок) ---" << endl;
                current->BottleBox::info();
            }
            break;
        }

        case 0: {
            cout << "\nЗавершение работы программы..." << endl;
            break;
        }

        default:
            cout << "Неверный пункт меню! Попробуйте снова." << endl;
        }
    } while (choice != 0);

    // Освобождение памяти
    if (current != nullptr) {
        cout << "\nУдаление текущего объекта:" << endl;
        delete current;
        current = nullptr;
    }

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
