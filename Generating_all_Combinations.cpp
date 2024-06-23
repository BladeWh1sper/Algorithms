#include <iostream>
#include <vector>

using namespace std;

void generateCombinations(vector<int>& current, int n, int k, int start, vector<vector<int> >& result) {
    if (current.size() == k) {
        result.push_back(current);
        return;
    }

    for (int i = start; i <= n; ++i) {
        current.push_back(i);
        generateCombinations(current, n, k, i + 1, result);
        current.pop_back();
    }
}

vector<vector<int> > combinations(int n, int k) {
    vector<vector<int> > result;
    vector<int> current;
    generateCombinations(current, n, k, 1, result);
    return result;
}

int main() {
    int n, k;
    cout << "Введите значение n: ";
    cin >> n;
    cout << "Введите значение k: ";
    cin >> k;

    vector<vector<int> > result = combinations(n, k);

    cout << "Все сочетания C(" << n << ", " << k << "):" << endl;
    for (const auto& comb : result) {
        for (int x : comb) {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}
