#include <iostream>
#include <vector>

using namespace std;

// Функция для вычисления определителя матрицы
int determinant(vector<vector<int> > mat, int n) {
    int det = 0;
    if (n == 1) {
        return mat[0][0];
    }

    vector<vector<int> > temp(n, vector<int>(n));
    int sign = 1;

    for (int f = 0; f < n; f++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == f)
                    continue;
                temp[subi][subj] = mat[i][j];
                subj++;
            }
            subi++;
        }
        det += sign * mat[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }

    return det;
}

// Функция для вычисления матрицы Лапласа
vector<vector<int> > laplacianMatrix(vector<vector<int> > adj, int V) {
    vector<vector<int> > laplacian(V, vector<int>(V, 0));

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                for (int k = 0; k < V; k++) {
                    if (adj[i][k] != 0) {
                        laplacian[i][j]++;
                    }
                }
            } else if (adj[i][j] != 0) {
                laplacian[i][j] = -adj[i][j];
            }
        }
    }
    return laplacian;
}

int countSpanningTrees(vector<vector<int> > adj, int V) {
    vector<vector<int> > laplacian = laplacianMatrix(adj, V);

    vector<vector<int> > subMatrix(V - 1, vector<int>(V - 1));
    for (int i = 1; i < V; i++) {
        for (int j = 1; j < V; j++) {
            subMatrix[i - 1][j - 1] = laplacian[i][j];
        }
    }

    return determinant(subMatrix, V - 1);
}

int main() {
    int V, E;
    cout << "Введите количество вершин и рёбер: ";
    cin >> V >> E;

    vector<vector<int> > adj(V, vector<int>(V, 0));

    cout << "Введите рёбра в формате (u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    cout << "Число остовных деревьев: " << countSpanningTrees(adj, V) << endl;

    return 0;
}
