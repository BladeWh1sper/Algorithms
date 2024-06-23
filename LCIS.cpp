#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> findLCIS(vector<int>& A, vector<int>& B) {
    int n = A.size();
    int m = B.size();
    vector<int> dp(m, 0); // Динамическая таблица для хранения длины LCIS
    vector<int> parent(m, -1); // Таблица для хранения предшествующих индексов LCIS

    int maxLength = 0; // Длина LCIS
    int endIndex = -1; // Конечный индекс LCIS в массиве B

    for (int i = 0; i < n; i++) {
        int current = 0;
        int lastIndex = -1;
        for (int j = 0; j < m; j++) {
            if (A[i] == B[j] && current + 1 > dp[j]) {
                dp[j] = current + 1;
                parent[j] = lastIndex;
                if (dp[j] > maxLength) {
                    maxLength = dp[j];
                    endIndex = j;
                }
            }
            if (A[i] > B[j] && dp[j] > current) {
                current = dp[j];
                lastIndex = j;
            }
        }
    }

    vector<int> LCIS;
    while (endIndex != -1) {
        LCIS.push_back(B[endIndex]);
        endIndex = parent[endIndex];
    }
    reverse(LCIS.begin(), LCIS.end());

    return LCIS;
}

int main() {
    int n, m;
    cout << "Введите размер первого массива: ";
    cin >> n;
    cout << "Введите размер второго массива: ";
    cin >> m;

    vector<int> A(n), B(m);
    cout << "Введите элементы первого массива: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    cout << "Введите элементы второго массива: ";
    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }

    vector<int> LCIS = findLCIS(A, B);

    cout << "Наибольшая общая возрастающая последовательность: ";
    for (int x : LCIS) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
