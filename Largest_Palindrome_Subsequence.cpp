#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Функция для нахождения наибольшей подпоследовательности-палиндрома
int longestPalindromicSubsequence(const string& s) {
    int n = s.size();
    vector<vector<int> > dp(n, vector<int>(n, 0));

    // Подпоследовательность длины 1 - всегда палиндром
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }

    // Заполняем таблицу dp
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i < n - len + 1; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j] && len == 2) {
                dp[i][j] = 2;
            } else if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    string s;
    cout << "Введите строку: ";
    cin >> s;

    int length = longestPalindromicSubsequence(s);
    cout << "Длина наибольшей подпоследовательности-палиндрома: " << length << endl;

    return 0;
}
