#include <iostream>
#include <vector>

using namespace std;

// Функция для выполнения троичного поиска
int ternarySearch(const vector<int>& arr, int left, int right, int x) {
    if (right >= left) {
        // Разделяем на три части
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        // Проверка средних элементов
        if (arr[mid1] == x) return mid1;
        if (arr[mid2] == x) return mid2;

        // Определение, в какой из частей следует искать
        if (x < arr[mid1]) {
            return ternarySearch(arr, left, mid1 - 1, x);
        } else if (x > arr[mid2]) {
            return ternarySearch(arr, mid2 + 1, right, x);
        } else {
            return ternarySearch(arr, mid1 + 1, mid2 - 1, x);
        }
    }
    // Если элемент не найден
    return -1;
}

int main() {
    int n, x;
    cout << "Введите количество элементов в массиве: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Введите элементы массива в отсортированном порядке: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Введите элемент для поиска: ";
    cin >> x;

    int index = ternarySearch(arr, 0, n - 1, x);

    if (index != -1)
        cout << "Элемент найден на позиции: " << index << endl;
    else
        cout << "Элемент не найден" << endl;

    return 0;
}
