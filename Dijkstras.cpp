#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

vector<int> dijkstra(int V, vector<vector<pii> >& adj, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    priority_queue<pii, vector<pii>, greater<pii> > pq;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

int main() {
    int V, E, src;
    cout << "Введите количество вершин и рёбер: ";
    cin >> V >> E;

    vector<vector<pii> > adj(V);
    cout << "Введите рёбра в формате (u v вес):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight)); // Удалите эту строку, если граф ориентированный
    }

    cout << "Введите исходную вершину: ";
    cin >> src;

    vector<int> distances = dijkstra(V, adj, src);

    cout << "Кратчайшие расстояния от вершины " << src << ":" << endl;
    for (int i = 0; i < V; i++) {
        cout << "До вершины " << i << " : ";
        if (distances[i] == INT_MAX)
            cout << "нет пути" << endl;
        else
            cout << distances[i] << endl;
    }

    return 0;
}
