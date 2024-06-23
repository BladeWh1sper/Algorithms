#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Функция для поиска наибольшей общей подстроки
string longestCommonSubstring(const string& s1, const string& s2) {
    int m = s1.size();
    int n = s2.size();

    // Матрица для хранения длин наибольших общих подстрок
    vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));
    int maxLength = 0; // Длина наибольшей общей подстроки
    int endIndex = 0; // Конечный индекс наибольшей общей подстроки в s1

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    // Извлечение наибольшей общей подстроки из строки s1
    if (maxLength == 0) {
        return "";
    }
    return s1.substr(endIndex - maxLength, maxLength);
}

int main() {
    string s1, s2;
    cout << "Введите первую строку: ";
    getline(cin, s1);
    cout << "Введите вторую строку: ";
    getline(cin, s2);

    string result = longestCommonSubstring(s1, s2);
    if (result.empty()) {
        cout << "Общих подстрок не найдено" << endl;
    } else {
        cout << "Наибольшая общая подстрока: " << result << endl;
    }

    return 0;
}
