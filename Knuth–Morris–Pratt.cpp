#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Функция для построения массива частичных совпадений (массив "π")
vector<int> computeLPSArray(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0; // длина предыдущего наибольшего префикса, который также является суффиксом
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// Функция для поиска всех вхождений подстроки в строке
void KMPSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    vector<int> lps = computeLPSArray(pattern);

    int i = 0; // индекс для text[]
    int j = 0; // индекс для pattern[]
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Найдено совпадение по индексу " << i - j << endl;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text, pattern;
    cout << "Введите текст: ";
    getline(cin, text);
    cout << "Введите образец: ";
    getline(cin, pattern);

    KMPSearch(text, pattern);

    return 0;
}
