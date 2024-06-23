#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int NIL = 0;
const int INF = INT_MAX;

class BipartiteGraph {
    int m, n;
    vector<vector<int> > adj;

    vector<int> pairU, pairV, dist;

public:
    BipartiteGraph(int m, int n) : m(m), n(n), adj(m + 1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> Q;

        for (int u = 1; u <= m; u++) {
            if (pairU[u] == NIL) {
                dist[u] = 0;
                Q.push(u);
            } else {
                dist[u] = INF;
            }
        }

        dist[NIL] = INF;

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();

            if (dist[u] < dist[NIL]) {
                for (int v : adj[u]) {
                    if (dist[pairV[v]] == INF) {
                        dist[pairV[v]] = dist[u] + 1;
                        Q.push(pairV[v]);
                    }
                }
            }
        }

        return dist[NIL] != INF;
    }

    bool dfs(int u) {
        if (u != NIL) {
            for (int v : adj[u]) {
                if (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v])) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }

    int hopcroftKarp() {
        pairU.assign(m + 1, NIL);
        pairV.assign(n + 1, NIL);
        dist.assign(m + 1, INF);

        int matching = 0;

        while (bfs()) {
            for (int u = 1; u <= m; u++) {
                if (pairU[u] == NIL && dfs(u)) {
                    matching++;
                }
            }
        }

        return matching;
    }
};

int main() {
    int m, n, E;
    cout << "Введите количество вершин в первой и второй доле и количество рёбер: ";
    cin >> m >> n >> E;

    BipartiteGraph g(m, n);

    cout << "Введите рёбра в формате (u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "Максимальное паросочетание: " << g.hopcroftKarp() << endl;

    return 0;
}
