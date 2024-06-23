#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для генерации всех возможных сумм значений подмножеств
void generateSubsetSums(const vector<int>& arr, vector<int>& subsetSums, int start, int end) {
    int n = end - start;
    int totalSubsets = 1 << n;
    for (int i = 0; i < totalSubsets; ++i) {
        int sum = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                sum += arr[start + j];
            }
        }
        subsetSums.push_back(sum);
    }
}

// Функция для решения задачи о рюкзаке методом Meet-in-the-middle
int knapsackMeetInTheMiddle(const vector<int>& weights, int W) {
    int n = weights.size();
    vector<int> leftSums, rightSums;

    // Делим массив на две половины и генерируем все возможные суммы подмножеств
    generateSubsetSums(weights, leftSums, 0, n / 2);
    generateSubsetSums(weights, rightSums, n / 2, n);

    // Сортируем суммы правой половины для использования бинарного поиска
    sort(rightSums.begin(), rightSums.end());

    int maxWeight = 0;

    // Перебираем все суммы левой половины и ищем наибольшую возможную сумму, не превышающую W
    for (int sum : leftSums) {
        if (sum <= W) {
            // Ищем наибольшую сумму в правой половине, которая в сумме с текущей суммой левой половины не превышает W
            auto it = upper_bound(rightSums.begin(), rightSums.end(), W - sum);
            if (it != rightSums.begin()) {
                --it;
                maxWeight = max(maxWeight, sum + *it);
            }
        }
    }

    return maxWeight;
}

int main() {
    int n, W;
    cout << "Введите количество предметов и вместимость рюкзака: ";
    cin >> n >> W;

    vector<int> weights(n);
    cout << "Введите веса предметов: ";
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    int maxWeight = knapsackMeetInTheMiddle(weights, W);
    cout << "Максимальный вес, который можно унести в рюкзаке: " << maxWeight << endl;

    return 0;
}
