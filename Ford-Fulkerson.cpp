#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

bool bfs(vector<vector<int> >& rGraph, int s, int t, vector<int>& parent) {
    int V = rGraph.size();
    vector<bool> visited(V, false);

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}

int fordFulkerson(vector<vector<int> >& graph, int s, int t) {
    int u, v;
    int V = graph.size();
    vector<vector<int> > rGraph = graph;

    vector<int> parent(V);
    int maxFlow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int pathFlow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    int V, E, U, V1;
    cout << "Введите количество вершин в первой доле, второй доле и количество рёбер: ";
    cin >> U >> V1 >> E;

    V = U + V1 + 2; // общее количество вершин в графе (включая источники и стоки)
    vector<vector<int> > graph(V, vector<int>(V, 0));

    int source = 0;
    int sink = V - 1;

    cout << "Введите рёбра в формате (u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph[u + 1][v + 1 + U] = 1; // соединяем вершины из первой и второй доли
    }

    for (int u = 1; u <= U; u++) {
        graph[source][u] = 1; // соединяем источник с вершинами первой доли
    }

    for (int v = 1; v <= V1; v++) {
        graph[v + U][sink] = 1; // соединяем вершины второй доли со стоком
    }

    int maxMatching = fordFulkerson(graph, source, sink);
    cout << "Максимальное паросочетание: " << maxMatching << endl;

    return 0;
}