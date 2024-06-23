#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

const int INF = INT_MAX;

bool bellmanFord(int V, vector<vector<pii> >& adj, vector<int>& h) {
    h.assign(V, INF);
    h[0] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (int u = 0; u < V; ++u) {
            if (h[u] == INF) continue;
            for (size_t j = 0; j < adj[u].size(); ++j) {
                int v = adj[u][j].first;
                int weight = adj[u][j].second;
                if (h[u] + weight < h[v]) {
                    h[v] = h[u] + weight;
                }
            }
        }
    }

    for (int u = 0; u < V; ++u) {
        if (h[u] == INF) continue;
        for (size_t j = 0; j < adj[u].size(); ++j) {
            int v = adj[u][j].first;
            int weight = adj[u][j].second;
            if (h[u] + weight < h[v]) {
                return false; // Обнаружен цикл отрицательного веса
            }
        }
    }

    return true;
}

vector<int> dijkstra(int V, vector<vector<pii> >& adj, int src, vector<int>& h) {
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    vector<int> dist(V, INF);
    dist[src] = 0;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (size_t j = 0; j < adj[u].size(); ++j) {
            int v = adj[u][j].first;
            int weight = adj[u][j].second + h[u] - h[v];
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    for (int i = 0; i < V; ++i) {
        if (dist[i] != INF) {
            dist[i] += h[i] - h[src];
        }
    }

    return dist;
}

void johnson(int V, vector<vector<pii> >& adj) {
    vector<vector<int> > allPairsDist(V, vector<int>(V, INF));
    vector<int> h;

    vector<vector<pii> > newAdj = adj;
    newAdj.push_back(vector<pii>());
    for (int i = 0; i < V; ++i) {
        newAdj[V].push_back(make_pair(i, 0));
    }

    if (!bellmanFord(V + 1, newAdj, h)) {
        cout << "Граф содержит цикл отрицательного веса." << endl;
        return;
    }

    for (int u = 0; u < V; ++u) {
        vector<int> dist = dijkstra(V, adj, u, h);
        for (int v = 0; v < V; ++v) {
            allPairsDist[u][v] = dist[v];
        }
    }

    cout << "Кратчайшие расстояния между всеми парами вершин:" << endl;
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (allPairsDist[u][v] == INF) {
                cout << "INF ";
            } else {
                cout << allPairsDist[u][v] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    int V, E;
    cout << "Введите количество вершин и рёбер: ";
    cin >> V >> E;

    vector<vector<pii> > adj(V);
    cout << "Введите рёбра в формате (u v вес):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        adj[u].push_back(make_pair(v, weight));
    }

    johnson(V, adj);

    return 0;
}
