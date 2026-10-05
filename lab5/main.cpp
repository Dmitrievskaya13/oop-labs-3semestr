#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <windows.h>
using namespace std;

// ================= ЦВЕТА =================
#define RESET   "\033[0m"
#define BLUE    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"

// ================= БАЗОВЫЙ КЛАСС 1: ДУХ =================
class Spirit {
private:
    string color;   // уникальное поле: цвет духа
protected:
    int power;      // защищённое поле: сила духа
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

    void showEssence() {
        cout << "  Цвет духа: " << color
            << ", сила: " << power << endl;
    }

    virtual void info() {
        cout << "[Spirit::info] Информация о духе, цвет = " << color << endl;
    }


    //опять геттеры сеттеры, а я так и не знаю зачем они нужны
    void setEssence(string e) { color = e; }
    void setPower(int p) { power = p; }
    string getEssence() { return color; }
    int getPower() { return power; }

    // Дружественная функция получает доступ к приватному color
    friend void showAllPrivate(const class Genie& g);
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

    void showHuman() {
        cout << "  Человеческое имя: " << name
            << ", возраст: " << age << endl;
    }

    virtual void info() {
        cout << "[Human::info] Информация о человеке, имя = " << name << endl;
    }

    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    string getName() { return name; }
    int getAge() { return age; }

    // Дружественная функция получает доступ к приватному name
    friend void showAllPrivate(const class Genie& g);
};

// ================= ПРОИЗВОДНЫЙ КЛАСС: ДЖИН =================
class Genie : public Spirit, public Human {
    //почему приват а не протектед я хз
private:
    string lampOwner;   // уникальное поле 1: хозяин лампы
    string home;        // уникальное поле 2: место обитания
public:
    Genie() : Spirit(), Human() {
        lampOwner = "нет хозяина";
        home = "старая лампа";
        cout << "конструктор по умолчанию 3 - constr_Genie()" << endl;
    }

    Genie(string e, int p, string n, int a,
        string owner, string h)
        : Spirit(e, p), Human(n, a) {
        lampOwner = owner;
        home = h;
        cout << "конструктор с параметром 3 - constr_Genie(p)" << endl;
    }

    ~Genie() { cout << "деструктор 3 - destr_Genie" << endl; }

    void showGenie() {
        cout << "  Хозяин лампы: " << lampOwner
            << ", место обитания: " << home << endl;
    }

    void info() override {
        cout << "[Genie::info] Информация о джине."
            << " Хозяин: " << lampOwner
            << ", дом: " << home << endl;
    }

    void setLampOwner(string o) { lampOwner = o; }
    void setHome(string h) { home = h; }
    string getLampOwner() { return lampOwner; }
    string getHome() { return home; }

    // Объявление дружественной функции
    friend void showAllPrivate(const Genie& g);
};

// !!!!!!!!!!!!   ДРУЖЕСТВЕННАЯ ФУНКЦИЯ   !!!!!!!!!!!!!!!

// Получает доступ к ЗАКРЫТЫМ полям классов Spirit, Human и Genie
void showAllPrivate(const Genie& g) {
    cout << GREEN << "\n=== Дружественная функция: доступ к закрытым полям ===" << RESET << endl;

    // Доступ к приватному полю Spirit::color
    cout << "Spirit::color (приватное)    = " << g.Spirit::color << endl;

    // Доступ к защищённому полю Spirit::power
    cout << "Spirit::power (защищённое)   = " << g.Spirit::power << endl;

    // Доступ к приватному полю Human::name
    cout << "Human::name (приватное)      = " << g.Human::name << endl;

    // Доступ к защищённому полю Human::age
    cout << "Human::age (защищённое)      = " << g.Human::age << endl;

    // Доступ к приватным полям Genie
    cout << "Genie::lampOwner (приватное) = " << g.lampOwner << endl;
    cout << "Genie::home (приватное)      = " << g.home << endl;

    cout << GREEN << "=======================================================" << RESET << endl;
}

// Проверка на ввод числа, чтоб никто текст не ввел
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(10000, '\n');
            return value;
        }
        //я отчислюсь и стану менеджером по продажам
        //что такое клир и почему в игнор 100000 я хз
        cin.clear();
        cin.ignore(10000, '\n');
        cout << RED << "Ошибка! Нужно ввести число. Попробуйте снова, только нормально теперь пж."
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
    g.showEssence();
    g.showHuman();
    g.showGenie();
    g.info();
    g.Spirit::info();
    g.Human::info();
    cout << "--------------------------" << endl;
}

// ================= ОЧИСТКА ЭКРАНА чтоб всё красиво было =================
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Опять рамка
// Кривая и голубая к тому же, вообще бедолага

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
    Genie g1;
    Genie g2;
    bool isFilled = false;
    int choice;

    do {
        cout << "\n" << BLUE
            << "========== МЕНЮ ==========" << RESET << endl;
        cout << "1. Показать объект 1 (по умолчанию)" << endl;
        cout << "2. Показать объект 2" << endl;
        cout << "3. Ввести данные для объекта 2" << endl;
        cout << "4. Сравнить через указатель на Spirit" << endl;
        cout << "5. Сравнить через указатель на Human" << endl;
        cout << "6. Дружественная функция: показать закрытые поля" << endl;  // НОВЫЙ ПУНКТ
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

        case 6: {
            printBlueFrame();
            // Вызов дружественной функции
            showAllPrivate(g1);
            if (isFilled) {
                cout << "\n--- Для объекта 2 ---" << endl;
                showAllPrivate(g2);
            }
            break;
        }

        case 0:
            cout << YELLOW << "Выход из программы." << RESET << endl;
            break;

        default:
            cout << RED << "Неверный выбор! Введите 0-6." << RESET << endl;
        }
    } while (choice != 0);
}

// ================= MAIN =================
int main() {
    //почему 1215 если ютф8 я хз, но иначе не работает
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
