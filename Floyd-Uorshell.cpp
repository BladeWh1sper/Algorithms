#include <iostream>
#include <vector>
#include <limits>

using namespace std;

#define INF numeric_limits<int>::max()

void printSolution(const vector<vector<int> >& dist) {
    int V = dist.size();
    cout << "Кратчайшие расстояния между каждой парой вершин:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << "   ";
        }
        cout << endl;
    }
}

void floydWarshall(vector<vector<int> >& graph) {
    int V = graph.size();
    vector<vector<int> > dist = graph;

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printSolution(dist);
}

int main() {
    int V = 4;
    vector<vector<int> > graph(V, vector<int>(V));

    graph[0][0] = 0; graph[0][1] = 3; graph[0][2] = INF; graph[0][3] = 5;
    graph[1][0] = 2; graph[1][1] = 0; graph[1][2] = INF; graph[1][3] = 4;
    graph[2][0] = INF; graph[2][1] = 1; graph[2][2] = 0; graph[2][3] = INF;
    graph[3][0] = INF; graph[3][1] = INF; graph[3][2] = 2; graph[3][3] = 0;

    cout << "Входной граф (матрица смежности):\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (graph[i][j] == INF)
                cout << "INF ";
            else
                cout << graph[i][j] << "   ";
        }
        cout << endl;
    }

    floydWarshall(graph);

    return 0;
}
