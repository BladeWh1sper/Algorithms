#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
    int V; // Количество вершин
    vector<vector<int> > adj; // Список смежности

    void fillOrder(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;

        for (int i : adj[v])
            if (!visited[i])
                fillOrder(i, visited, Stack);

        Stack.push(v);
    }

    void DFSUtil(int v, vector<bool>& visited, vector<int>& component) {
        visited[v] = true;
        component.push_back(v);

        for (int i : adj[v])
            if (!visited[i])
                DFSUtil(i, visited, component);
    }

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    Graph getTranspose() {
        Graph g(V);
        for (int v = 0; v < V; v++) {
            for (int i : adj[v]) {
                g.adj[i].push_back(v);
            }
        }
        return g;
    }

    void printSCCs() {
        stack<int> Stack;

        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                fillOrder(i, visited, Stack);

        Graph gr = getTranspose();

        fill(visited.begin(), visited.end(), false);

        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();

            if (!visited[v]) {
                vector<int> component;
                gr.DFSUtil(v, visited, component);
                cout << "Сильная компонента связности: ";
                for (int i : component)
                    cout << i << " ";
                cout << endl;
            }
        }
    }
};

int main() {
    int V, E;
    cout << "Введите количество вершин и рёбер: ";
    cin >> V >> E;

    Graph g(V);

    cout << "Введите рёбра в формате (источник, назначение):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "Сильные компоненты связности в графе:" << endl;
    g.printSCCs();

    return 0;
}
