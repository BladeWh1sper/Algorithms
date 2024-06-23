#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void generatePermutations(vector<int>& elements, int k, vector<int>& current, vector<bool>& used) {
    if (current.size() == k) {
        for (int i : current) {
            cout << i << " ";
        }
        cout << endl;
        return;
    }

    for (int i = 0; i < elements.size(); ++i) {
        if (!used[i]) {
            used[i] = true;
            current.push_back(elements[i]);
            generatePermutations(elements, k, current, used);
            current.pop_back();
            used[i] = false;
        }
    }
}

void generateArrangements(int n, int k) {
    vector<int> elements(n);
    for (int i = 0; i < n; ++i) {
        elements[i] = i + 1;
    }

    vector<int> current;
    vector<bool> used(n, false);

    generatePermutations(elements, k, current, used);
}

int main() {
    int n, k;
    cout << "Введите значения n и k: ";
    cin >> n >> k;

    cout << "Все размещения A(" << n << ", " << k << "):" << endl;
    generateArrangements(n, k);

    return 0;
}
