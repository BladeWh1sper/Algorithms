#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class TarjanSCC {
public:
    TarjanSCC(int n) : graph(n), index(n, -1), lowlink(n, 0), onStack(n, false), currentIndex(0) {}

    void addEdge(int v, int w) {
        graph[v].push_back(w);
    }

    void run() {
        for (int v = 0; v < graph.size(); ++v) {
            if (index[v] == -1) {
                strongConnect(v);
            }
        }
    }

    const vector<vector<int> >& getSCCs() const {
        return sccs;
    }

private:
    vector<vector<int> > graph;
    vector<int> index;
    vector<int> lowlink;
    vector<bool> onStack;
    stack<int> S;
    int currentIndex;
    vector<vector<int> > sccs;

    void strongConnect(int v) {
        index[v] = currentIndex;
        lowlink[v] = currentIndex;
        currentIndex++;
        S.push(v);
        onStack[v] = true;

        for (int w : graph[v]) {
            if (index[w] == -1) {
                strongConnect(w);
                lowlink[v] = min(lowlink[v], lowlink[w]);
            } else if (onStack[w]) {
                lowlink[v] = min(lowlink[v], index[w]);
            }
        }

        if (lowlink[v] == index[v]) {
            vector<int> scc;
            int w;
            do {
                w = S.top();
                S.pop();
                onStack[w] = false;
                scc.push_back(w);
            } while (w != v);
            sccs.push_back(scc);
        }
    }
};

int main() {
    int n, m;
    cout << "Введите количество вершин и рёбер: ";
    cin >> n >> m;

    TarjanSCC tarjan(n);

    cout << "Введите рёбра в формате (u v):" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        tarjan.addEdge(u, v);
    }

    tarjan.run();

    const vector<vector<int> >& sccs = tarjan.getSCCs();
    cout << "Сильно связанные компоненты:" << endl;
    for (const auto& scc : sccs) {
        for (int v : scc) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}
