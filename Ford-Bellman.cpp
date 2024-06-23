#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int src, dest, weight;
};

void BellmanFord(vector<Edge>& edges, int V, int E, int src) {
    // Инициализация расстояний от источника до всех вершин как бесконечность
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Расслабляем все ребра |V| - 1 раз
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Проверяем на наличие циклов отрицательного веса
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Граф содержит цикл отрицательного веса" << endl;
            return;
        }
    }

    // Печать расстояний от источника до всех вершин
    cout << "Вершина   Расстояние от источника" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "\t\t" << dist[i] << endl;
    }
}

int main() {
    int V, E, src;
    cout << "Введите количество вершин и рёбер: ";
    cin >> V >> E;
    
    vector<Edge> edges(E);
    cout << "Введите рёбра в формате (источник, назначение, вес):" << endl;
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    cout << "Введите исходную вершину: ";
    cin >> src;

    BellmanFord(edges, V, E, src);

    return 0;
}
