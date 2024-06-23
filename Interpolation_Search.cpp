#include <iostream>
#include <vector>

using namespace std;

int interpolationSearch(const vector<int>& arr, int x) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high && x >= arr[low] && x <= arr[high]) {
        if (low == high) {
            if (arr[low] == x) return low;
            return -1;
        }

        // Вычисление позиции с помощью интерполяционной формулы
        int pos = low + ((double)(high - low) / (arr[high] - arr[low]) * (x - arr[low]));

        if (arr[pos] == x)
            return pos;

        if (arr[pos] < x)
            low = pos + 1;
        else
            high = pos - 1;
    }

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

    int index = interpolationSearch(arr, x);

    if (index != -1)
        cout << "Элемент найден на позиции: " << index << endl;
    else
        cout << "Элемент не найден" << endl;

    return 0;
}
