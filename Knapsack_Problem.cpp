#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для решения задачи о рюкзаке методом динамического программирования
int knapsack(int W, const vector<int>& weights, const vector<int>& values) {
    int n = weights.size();
    vector<vector<int> > dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main() {
    int n, W;
    cout << "Введите количество предметов: ";
    cin >> n;
    cout << "Введите вместимость рюкзака: ";
    cin >> W;

    vector<int> weights(n), values(n);
    cout << "Введите веса предметов: ";
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    cout << "Введите ценности предметов: ";
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    int max_value = knapsack(W, weights, values);
    cout << "Максимальная ценность, которую можно унести в рюкзаке: " << max_value << endl;

    return 0;
}
