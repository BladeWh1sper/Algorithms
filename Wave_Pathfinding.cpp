#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

// Направления движения: вверх, вниз, влево, вправо
const int dRow[] = {-1, 1, 0, 0};
const int dCol[] = {0, 0, -1, 1};

// Функция для проверки, находится ли ячейка внутри границ и проходима ли она
bool isValid(int row, int col, int numRows, int numCols, const vector< vector<int> >& grid) {
    return (row >= 0 && row < numRows && col >= 0 && col < numCols && grid[row][col] == 0);
}

// Функция для выполнения волнового алгоритма поиска пути
vector< pair<int, int> > waveAlgorithm(const vector< vector<int> >& grid, pair<int, int> start, pair<int, int> end) {
    int numRows = grid.size();
    int numCols = grid[0].size();
    vector< vector<int> > distance(numRows, vector<int>(numCols, -1));
    queue< pair<int, int> > q;

    // Инициализация
    q.push(make_pair(start.first, start.second));
    distance[start.first][start.second] = 0;

    // Выполнение обхода в ширину
    while (!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        // Проверка всех четырёх направлений
        for (int i = 0; i < 4; ++i) {
            int newRow = row + dRow[i];
            int newCol = col + dCol[i];

            if (isValid(newRow, newCol, numRows, numCols, grid) && distance[newRow][newCol] == -1) {
                distance[newRow][newCol] = distance[row][col] + 1;
                q.push(make_pair(newRow, newCol));
                if (newRow == end.first && newCol == end.second) {
                    break;
                }
            }
        }
    }

    // Построение пути от конца к началу
    vector< pair<int, int> > path;
    if (distance[end.first][end.second] != -1) {
        int row = end.first;
        int col = end.second;
        while (!(row == start.first && col == start.second)) {
            path.push_back(make_pair(row, col));
            for (int i = 0; i < 4; ++i) {
                int newRow = row + dRow[i];
                int newCol = col + dCol[i];
                if (isValid(newRow, newCol, numRows, numCols, grid) && distance[newRow][newCol] == distance[row][col] - 1) {
                    row = newRow;
                    col = newCol;
                    break;
                }
            }
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
    }

    return path;
}

int main() {
    int numRows, numCols;
    cout << "Введите количество строк и столбцов: ";
    cin >> numRows >> numCols;

    vector< vector<int> > grid(numRows, vector<int>(numCols));
    cout << "Введите сетку (0 - проходимая клетка, 1 - препятствие):" << endl;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            cin >> grid[i][j];
        }
    }

    pair<int, int> start, end;
    cout << "Введите начальную точку (row col): ";
    cin >> start.first >> start.second;
    cout << "Введите конечную точку (row col): ";
    cin >> end.first >> end.second;

    vector< pair<int, int> > path = waveAlgorithm(grid, start, end);

    if (!path.empty()) {
        cout << "Кратчайший путь:" << endl;
        for (size_t i = 0; i < path.size(); ++i) {
            cout << "(" << path[i].first << ", " << path[i].second << ") ";
        }
        cout << endl;
    } else {
        cout << "Путь не найден." << endl;
    }

    return 0;
}

