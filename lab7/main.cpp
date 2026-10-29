
#include <iostream>
#include <cstdlib>
using namespace std;

// шаблон заполнения массива
template <class T>
void fillArray(T *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << "arr[" << i << "] = ";
        cin >> arr[i];
    }
}

// шаблон вывода массива
template <class T>
void printArray(T *arr, int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// шаблон сдвига вправо на n позиций
template <class T>
void shiftRight(T *arr, int size, int n) {
    n = n % size;                     // нормализация
    if (n == 0) return;
    T *tmp = new T[size];
    for (int i = 0; i < size; i++)
        tmp[(i + n) % size] = arr[i];
    for (int i = 0; i < size; i++)
        arr[i] = tmp[i];
    delete[] tmp;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // --- int ---
    int n1 = 5, shift1;
    int a[5];
    cout << "=== int ===\n";
    fillArray(a, n1);
    cout << "Исходный: "; printArray(a, n1);
    cout << "Сдвиг вправо на: "; cin >> shift1;
    shiftRight(a, n1, shift1);
    cout << "Результат: "; printArray(a, n1);

    // --- double ---
    int n2 = 4, shift2;
    double b[4];
    cout << "\n=== double ===\n";
    fillArray(b, n2);
    cout << "Исходный: "; printArray(b, n2);
    cout << "Сдвиг вправо на: "; cin >> shift2;
    shiftRight(b, n2, shift2);
    cout << "Результат: "; printArray(b, n2);

    // --- char ---
    int n3 = 6, shift3;
    char c[6];
    cout << "\n=== char ===\n";
    fillArray(c, n3);
    cout << "Исходный: "; printArray(c, n3);
    cout << "Сдвиг вправо на: "; cin >> shift3;
    shiftRight(c, n3, shift3);
    cout << "Результат: "; printArray(c, n3);

    return 0;
}
