#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Функция для поиска всех максимальных кликов
void bronKerbosch(set<int> R, set<int> P, set<int> X, const vector<vector<int> >& graph, vector<set<int> >& cliques) {
    if (P.empty() && X.empty()) {
        cliques.push_back(R);
        return;
    }

    set<int> P_copy = P;
    for (int v : P_copy) {
        set<int> R_new = R;
        R_new.insert(v);
        set<int> P_new, X_new;
        for (int w : P) {
            if (graph[v][w] == 1) {
                P_new.insert(w);
            }
        }
        for (int w : X) {
            if (graph[v][w] == 1) {
                X_new.insert(w);
            }
        }
        bronKerbosch(R_new, P_new, X_new, graph, cliques);
        P.erase(v);
        X.insert(v);
    }
}

int main() {
    int n, m;
    cout << "Введите количество вершин и рёбер: ";
    cin >> n >> m;

    vector<vector<int> > graph(n, vector<int>(n, 0));

    cout << "Введите рёбра в формате (u v):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    set<int> R, P, X;
    for (int i = 0; i < n; i++) {
        P.insert(i);
    }

    vector<set<int> > cliques;
    bronKerbosch(R, P, X, graph, cliques);

    cout << "Максимальные клики:" << endl;
    for (const auto& clique : cliques) {
        for (int v : clique) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}
