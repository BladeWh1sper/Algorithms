#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Структура для представления рёбер графа
struct Edge {
    int src, dest, weight;
    Edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}
};

// Структура для представления графа
class Graph {
public:
    int V, E;
    vector<Edge> edges;

    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void addEdge(int src, int dest, int weight) {
        edges.push_back(Edge(src, dest, weight));
    }

    int find(vector<int>& parent, int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent, parent[i]);
    }

    void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    void boruvkaMST() {
        vector<int> parent(V);
        vector<int> rank(V, 0);

        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }

        int numTrees = V;
        int MSTweight = 0;

        while (numTrees > 1) {
            vector<int> cheapest(V, -1);

            for (int i = 0; i < E; i++) {
                int u = edges[i].src;
                int v = edges[i].dest;
                int weight = edges[i].weight;

                int set1 = find(parent, u);
                int set2 = find(parent, v);

                if (set1 != set2) {
                    if (cheapest[set1] == -1 || edges[cheapest[set1]].weight > weight) {
                        cheapest[set1] = i;
                    }

                    if (cheapest[set2] == -1 || edges[cheapest[set2]].weight > weight) {
                        cheapest[set2] = i;
                    }
                }
            }

            for (int i = 0; i < V; i++) {
                if (cheapest[i] != -1) {
                    int u = edges[cheapest[i]].src;
                    int v = edges[cheapest[i]].dest;
                    int weight = edges[cheapest[i]].weight;

                    int set1 = find(parent, u);
                    int set2 = find(parent, v);

                    if (set1 != set2) {
                        MSTweight += weight;
                        cout << "Edge " << u << " - " << v << " included in MST" << endl;
                        unionSets(parent, rank, set1, set2);
                        numTrees--;
                    }
                }
            }
        }

        cout << "Weight of MST is " << MSTweight << endl;
    }
};

int main() {
    int V, E;
    cout << "Введите количество вершин и рёбер: ";
    cin >> V >> E;

    Graph graph(V, E);

    cout << "Введите рёбра в формате (src dest weight):" << endl;
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    graph.boruvkaMST();

    return 0;
}
