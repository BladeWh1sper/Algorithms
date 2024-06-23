#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <climits>

using namespace std;

class PushRelabel {
    int V; // Количество вершин
    vector<vector<int> > capacity; // Ёмкости рёбер
    vector<vector<int> > flow; // Потоки рёбер
    vector<int> height; // Высоты вершин
    vector<int> excess; // Избыточные потоки вершин
    vector<int> seen; // Количество просмотров для вершин

public:
    PushRelabel(int V) : V(V), capacity(V, vector<int>(V, 0)), flow(V, vector<int>(V, 0)), 
                         height(V, 0), excess(V, 0), seen(V, 0) {}

    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
    }

    void push(int u, int v) {
        int send = min(excess[u], capacity[u][v] - flow[u][v]);
        flow[u][v] += send;
        flow[v][u] -= send;
        excess[u] -= send;
        excess[v] += send;
    }

    void relabel(int u) {
        int min_height = INT_MAX;
        for (int v = 0; v < V; ++v) {
            if (capacity[u][v] - flow[u][v] > 0) {
                min_height = min(min_height, height[v]);
            }
        }
        if (min_height < INT_MAX) {
            height[u] = min_height + 1;
        }
    }

    void discharge(int u) {
        while (excess[u] > 0) {
            if (seen[u] < V) {
                int v = seen[u];
                if (capacity[u][v] - flow[u][v] > 0 && height[u] == height[v] + 1) {
                    push(u, v);
                } else {
                    seen[u]++;
                }
            } else {
                relabel(u);
                seen[u] = 0;
            }
        }
    }

    int getMaxFlow(int s, int t) {
        height[s] = V;
        excess[s] = INT_MAX;
        for (int v = 0; v < V; ++v) {
            if (v != s) {
                push(s, v);
            }
        }

        deque<int> Q;
        for (int i = 0; i < V; ++i) {
            if (i != s && i != t && excess[i] > 0) {
                Q.push_back(i);
            }
        }

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop_front();
            discharge(u);
            for (int i = 0; i < V; ++i) {
                if (i != s && i != t && excess[i] > 0 && find(Q.begin(), Q.end(), i) == Q.end()) {
                    Q.push_back(i);
                }
            }
        }

        int maxFlow = 0;
        for (int v = 0; v < V; ++v) {
            maxFlow += flow[s][v];
        }
        return maxFlow;
    }
};

int main() {
    int V, E;
    cout << "Введите количество вершин и рёбер: ";
    cin >> V >> E;

    PushRelabel pr(V);

    cout << "Введите рёбра в формате (источник, назначение, ёмкость):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, cap;
        cin >> u >> v >> cap;
        pr.addEdge(u, v, cap);
    }

    int s, t;
    cout << "Введите исходную вершину и сток: ";
    cin >> s >> t;

    cout << "Максимальный поток: " << pr.getMaxFlow(s, t) << endl;

    return 0;
}
