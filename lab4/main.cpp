#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <windows.h>
using namespace std;

// ================= ЦВЕТА ЧТОБ КРАСИВО БЫЛО =================
#define RESET   "\033[0m"
#define BLUE    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"

// ================= БАЗОВЫЙ КЛАСС 1: ДУХ =================
class Spirit {
private:
    string color;   // уникальное поле: цвет духа
protected:
    int power;      // защищённое поле: сила духа В ХП
public:
    Spirit() {
        color = "белый";
        power = 50;
        cout << "конструктор по умолчанию 1 - constr_Spirit()" << endl;
    }
    Spirit(string e, int p) {
        color = e;
        power = p;
        cout << "конструктор с параметрами 1 - constr_Spirit(p)" << endl;
    }
    ~Spirit() { cout << "деструктор 1 - destr_Spirit" << endl; }

    // уникальный метод
    void showEssence() {
        cout << "  Цвет духа: " << color
            << ", сила: " << power << endl;
    }

    // виртуальный метод с одинаковым названием
    virtual void info() {
        cout << "[Spirit::info] Информация о духе, цвет = " << color << endl;
    }

    // сеттеры/геттеры я не знаю что это такое 
    void setEssence(string e) { color = e; }
    void setPower(int p) { power = p; }
    string getEssence() { return color; }
    int getPower() { return power; }
};

// ================= БАЗОВЫЙ КЛАСС 2: ЧЕЛОВЕК =================
class Human {
private:
    string name;      // уникальное поле: человеческое имя
protected:
    int age;          // защищённое поле: возраст
public:
    Human() {
        name = "безымянный";
        age = 25;
        cout << "конструктор по умолчанию 2 - constr_Human()" << endl;
    }
    Human(string n, int a) {
        name = n;
        age = a;
        cout << "конструктор с параметром 2 - constr_Human(p)" << endl;
    }
    ~Human() { cout << "деструктор 2 - destr_Human" << endl; }

    // уникальный метод
    void showHuman() {
        cout << "  Человеческое имя: " << name
            << ", возраст: " << age << endl;
    }

    // метод с одинаковым названием
    virtual void info() {
        cout << "[Human::info] Информация о человеке, имя = " << name << endl;
    }

    // сеттеры/геттеры опять
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    string getName() { return name; }
    int getAge() { return age; }
};

// ================= ПРОИЗВОДНЫЙ КЛАСС: ДЖИН =================
class Genie : public Spirit, public Human {
private:
    string lampOwner;   // уникальное поле 1: хозяин лампы
    string home;        // уникальное поле 2: место обитания
public:
    // Конструктор по умолчанию
    Genie() : Spirit(), Human() {
        lampOwner = "нет хозяина";
        home = "старая лампа";
        cout << "конструктор по умолчанию 3 - constr_Genie()" << endl;
    }

    // Конструктор с параметрами
    Genie(string e, int p, string n, int a,
        string owner, string h)
        : Spirit(e, p), Human(n, a) {
        lampOwner = owner;
        home = h;
        cout << "конструктор с параметром 3 - constr_Genie(p)" << endl;
    }

    ~Genie() { cout << "деструктор 3 - destr_Genie" << endl; }

    // Уникальный метод производного класса
    void showGenie() {
        cout << "  Хозяин лампы: " << lampOwner
            << ", место обитания: " << home << endl;
    }

    // Переопределение метода базовых классов
    void info() override {
        cout << "[Genie::info] Информация о джине."
            << " Хозяин: " << lampOwner
            << ", дом: " << home << endl;
    }

    // сеттеры/геттеры
    void setLampOwner(string o) { lampOwner = o; }
    void setHome(string h) { home = h; }
    string getLampOwner() { return lampOwner; }
    string getHome() { return home; }
};

// ================= УНИВЕРСАЛЬНЫЙ ВВОД ЧИСЛА =================
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(10000, '\n');
            return value;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << RED << "Ошибка! Нужно ввести число. Попробуйте снова."
            << RESET << endl;
    }
}

// ================= ВВОД ДАННЫХ ДЖИНА =================
void inputGenie(Genie& g) {
    string e, n, owner, home;
    int p, a;

    cout << "Введите цвет духа: ";
    cin >> e;
    cin.ignore(10000, '\n');

    p = readInt("Введите силу духа: ");

    cout << "Введите человеческое имя: ";
    cin >> n;
    cin.ignore(10000, '\n');

    a = readInt("Введите возраст: ");

    cout << "Введите хозяина лампы: ";
    cin >> owner;
    cin.ignore(10000, '\n');

    cout << "Введите место обитания: ";
    cin >> home;
    cin.ignore(10000, '\n');

    g.setEssence(e);
    g.setPower(p);
    g.setName(n);
    g.setAge(a);
    g.setLampOwner(owner);
    g.setHome(home);
}

// ================= ВЫВОД ВСЕЙ ИНФОРМАЦИИ =================
void outputAll(Genie& g) {
    cout << "\n--- Информация о Джине ---" << endl;
    g.showEssence();       // Spirit
    g.showHuman();         // Human
    g.showGenie();         // Genie
    g.info();              // переопределённый
    g.Spirit::info();      // базовый Spirit
    g.Human::info();       // базовый Human
    cout << "--------------------------" << endl;
}

// ================= ОЧИСТКА ЭКРАНА =================
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// табличка типа она тут по приколу
// кривая, ещё и голубая к тому же, вообще не повезло по жизни

void printBlueFrame() {
    cout << BLUE;
    cout << "+------------------------------------------------------------+\n";
    cout << "|                                                            |\n";
    cout << "|   Джин - производный класс от базовых Дух и Человек        |\n";
    cout << "|                                                            |\n";
    cout << "+------------------------------------------------------------+\n";
    cout << RESET;
}

// ================= МЕНЮ =================
void menu() {
    Genie g1;               // объект по умолчанию
    Genie g2;               // второй объект
    bool isFilled = false;  // флаг: введены ли данные для g2
    int choice;

    do {
        cout << "\n" << BLUE
            << "========== МЕНЮ ==========" << RESET << endl;
        cout << "1. Показать объект 1 (по умолчанию)" << endl;
        cout << "2. Показать объект 2" << endl;
        cout << "3. Ввести данные для объекта 2" << endl;
        cout << "4. Сравнить через указатель на Spirit" << endl;
        cout << "5. Сравнить через указатель на Human" << endl;
        cout << "0. Выход" << endl;

        choice = readInt("Ваш выбор: ");

        clearScreen();

        switch (choice) {
        case 1:
            printBlueFrame();
            outputAll(g1);
            break;

        case 2:
            printBlueFrame();
            if (!isFilled) {
                cout << RED
                    << "Данные для объекта 2 ещё не введены!\n"
                    << "Сначала выберите пункт 3." << RESET << endl;
            }
            else {
                outputAll(g2);
            }
            break;

        case 3:
            printBlueFrame();
            inputGenie(g2);
            isFilled = true;
            cout << "Данные введены!" << endl;
            break;

        case 4: {
            printBlueFrame();
            Spirit* sp = &g1;
            sp->showEssence();
            sp->info();
            break;
        }

        case 5: {
            printBlueFrame();
            Human* hm = &g1;
            hm->showHuman();
            hm->info();
            break;
        }

        case 0:
            cout << YELLOW << "Выход из программы." << RESET << endl;
            break;

        default:
            cout << RED << "Неверный выбор! Введите 0-5." << RESET << endl;
        }
    } while (choice != 0);
}

// ================= MAIN =================
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "===== Создание объектов =====" << endl;
    menu();
    cout << "\n===== Конец программы =====" << endl;

    cout << "Нажмите Enter для выхода...";
    cin.get();
    return 0;
}
