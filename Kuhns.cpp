#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class BipartiteGraph {
public:
    BipartiteGraph(int n, int m) : n(n), m(m) {
        adj.resize(n);
        visited.resize(n);
        matchLeft.resize(n, -1);
        matchRight.resize(m, -1);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    int maxMatching() {
        int matching = 0;
        for (int u = 0; u < n; u++) {
            fill(visited.begin(), visited.end(), false);
            if (kuhnDFS(u)) {
                matching++;
            }
        }
        return matching;
    }

private:
    int n, m;
    vector<vector<int> > adj;
    vector<bool> visited;
    vector<int> matchLeft, matchRight;

    bool kuhnDFS(int u) {
        if (visited[u]) return false;
        visited[u] = true;

        for (int v : adj[u]) {
            if (matchRight[v] == -1 || kuhnDFS(matchRight[v])) {
                matchRight[v] = u;
                matchLeft[u] = v;
                return true;
            }
        }
        return false;
    }
};

int main() {
    int n, m, e;
    cout << "Введите количество вершин в первой и второй доле и количество рёбер: ";
    cin >> n >> m >> e;

    BipartiteGraph graph(n, m);

    cout << "Введите рёбра в формате (u v):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    int maxMatching = graph.maxMatching();
    cout << "Максимальное паросочетание: " << maxMatching << endl;

    return 0;
}
