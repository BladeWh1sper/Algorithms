#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Edge {
public:
    int src, dest;
    Edge(int src, int dest) : src(src), dest(dest) {}
};

class Graph {
public:
    int V, E;
    vector<Edge> edges;

    Graph(int V, int E) : V(V), E(E) {}

    void addEdge(int src, int dest) {
        edges.push_back(Edge(src, dest));
    }

    int find(vector<int>& parent, int i) {
        if (parent[i] == i)
            return i;
        else
            return find(parent, parent[i]);
    }

    void Union(vector<int>& parent, vector<int>& rank, int x, int y) {
        int xroot = find(parent, x);
        int yroot = find(parent, y);

        if (rank[xroot] < rank[yroot]) {
            parent[xroot] = yroot;
        } else if (rank[xroot] > rank[yroot]) {
            parent[yroot] = xroot;
        } else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

    int kargerMinCut() {
        vector<int> parent(V);
        vector<int> rank(V, 0);

        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }

        int vertices = V;
        while (vertices > 2) {
            int i = rand() % E;
            int subset1 = find(parent, edges[i].src);
            int subset2 = find(parent, edges[i].dest);

            if (subset1 != subset2) {
                cout << "Contracting edge (" << edges[i].src << ", " << edges[i].dest << ")\n";
                Union(parent, rank, subset1, subset2);
                vertices--;
            }
        }

        int cutedges = 0;
        for (int i = 0; i < E; i++) {
            int subset1 = find(parent, edges[i].src);
            int subset2 = find(parent, edges[i].dest);
            if (subset1 != subset2) {
                cutedges++;
            }
        }

        return cutedges;
    }
};

int main() {
    srand(time(0));

    int V, E;
    cout << "Введите количество вершин и рёбер: ";
    cin >> V >> E;

    Graph graph(V, E);

    cout << "Введите рёбра в формате (u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    int minCut = graph.kargerMinCut();
    cout << "Минимальный разрез графа: " << minCut << endl;

    return 0;
}
