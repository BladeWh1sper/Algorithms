#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Функция для нахождения ближайшего города
int findNearestNeighbor(int currentCity, const vector<vector<double> >& distanceMatrix, vector<bool>& visited) {
    int n = distanceMatrix.size();
    int nearestNeighbor = -1;
    double shortestDistance = numeric_limits<double>::max();

    for (int i = 0; i < n; ++i) {
        if (!visited[i] && distanceMatrix[currentCity][i] < shortestDistance) {
            shortestDistance = distanceMatrix[currentCity][i];
            nearestNeighbor = i;
        }
    }
    return nearestNeighbor;
}

// Функция для выполнения алгоритма ближайшего соседа
vector<int> nearestNeighborTSP(const vector<vector<double> >& distanceMatrix, int startCity) {
    int n = distanceMatrix.size();
    vector<int> tour;
    vector<bool> visited(n, false);

    int currentCity = startCity;
    tour.push_back(currentCity);
    visited[currentCity] = true;

    for (int i = 1; i < n; ++i) {
        int nextCity = findNearestNeighbor(currentCity, distanceMatrix, visited);
        if (nextCity != -1) {
            tour.push_back(nextCity);
            visited[nextCity] = true;
            currentCity = nextCity;
        }
    }

    // Возвращаемся в стартовый город, чтобы завершить тур
    tour.push_back(startCity);
    return tour;
}

int main() {
    int n;
    cout << "Введите количество городов: ";
    cin >> n;

    vector<vector<double> > distanceMatrix(n, vector<double>(n));
    cout << "Введите матрицу расстояний между городами:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> distanceMatrix[i][j];
        }
    }

    int startCity;
    cout << "Введите начальный город: ";
    cin >> startCity;

    vector<int> tour = nearestNeighborTSP(distanceMatrix, startCity);

    cout << "Тур коммивояжера, найденный алгоритмом ближайшего соседа:" << endl;
    for (int city : tour) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}
