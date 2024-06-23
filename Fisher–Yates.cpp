#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Функция для генерации случайной перестановки массива
void fisherYatesShuffle(vector<int>& arr) {
    int n = arr.size();
    for (int i = n - 1; i > 0; i--) {
        // Выбираем случайный индекс от 0 до i
        int j = rand() % (i + 1);
        // Меняем местами arr[i] и arr[j]
        swap(arr[i], arr[j]);
    }
}

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    cout << "Исходный массив: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    fisherYatesShuffle(arr);

    cout << "Случайная перестановка: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
