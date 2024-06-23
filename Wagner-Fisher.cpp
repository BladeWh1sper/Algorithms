#include <iostream>
#include <string>
#include <vector>

using namespace std;

size_t WagnerFisherAlgorithm(string firstString, string secondString){
    if(firstString == secondString){
        return 0;
    } // Если строки равны, то по определению у них расстояние 0

    size_t firstStringLength = firstString.length(), // переменная длинны первой строки
    secondStringLength = secondString.length(); // переменная длинны второй строки

    vector<size_t> row1(secondStringLength+ 1); // Массив предыдущей строки
    vector<size_t> row2(secondStringLength+ 1); // Массив нынешней строки

    row1[0] = 0;
    for(size_t i = 1; i < firstStringLength + 1; i++){
        row1[i] = row1[i-1] + 1;
    } // Первоначальное заполнение первой строки

    // int ins = 0, del = 0, sub = 0;

    for(size_t i = 1; i < firstStringLength + 1; i++){
        row2[0] = i; // первый элемент строки всегда равен i
        for(size_t j = 1; j < secondStringLength + 1; j++){
            if(firstString[i - 1] == secondString[j - 1]){
                row2[j] = min(min(row1[j-1], row1[j]), row2[j-1]); // Вычисление значения для одинаковых символов
            } else {
                row2[j] = min(min(row1[j-1], row1[j]), row2[j-1]) + 1; // Вычисление значения для двух символов и прибавление 1, как стоимость изменения(вставки, удаления или замены)
            }
        }
        row1 = row2; // Сохраняем вторую строку в массив первой строки
    }
    
    return row2[secondStringLength]; // Выводит результат, последний элемент массива(любого из двух)
}

// size_t WagnerFisherAlgorithm(string firstString, string secondString){
//     if(firstString == secondString){
//         return 0;
//     } // Если строки равны, то по определению у них расстояние 0
//     size_t firstStringLength = firstString.length(), // переменная длинны первой строки
//     secondStringLength = secondString.length(); // переменная длинны второй строки

//     size_t distanceMatrix[firstStringLength + 1][secondStringLength+ 1]; // создаем матрицу для расчета разсстояния Левенштейна

//     distanceMatrix[0][0] = 0; // первый элемент матрицы всегда равняется 0

//     for(size_t i = 1; i < firstStringLength + 1; i++){
//         distanceMatrix[0][i] = distanceMatrix[0][i - 1] + 1;
//     } // заполнение 1 строки матрицы, она одинакова для всех разных строк и всегда заполняется числами от 1 до длинны строки 2

//     for(size_t i = 1; i < firstStringLength + 1; i++){
//         distanceMatrix[i][0] = distanceMatrix[i - 1][0] + 1;
//     } // заполнение 1 столбца матрицы, она одинакова для всех разных строк и всегда заполняется числами от 1 до длинны строки 1

//     for(size_t i = 1; i < firstStringLength + 1; i++){
//         for(size_t j = 1; j < secondStringLength + 1; j++){
//             if(firstString[i - 1] == secondString[j - 1]){
//                 distanceMatrix[i][j] = min(min(distanceMatrix[i-1][j], distanceMatrix[i][j-1]), distanceMatrix[i-1][j-1]); // Вычисление значения для одинаковых символов
//             } else {
//                 distanceMatrix[i][j] = min(min(distanceMatrix[i-1][j], distanceMatrix[i][j-1]), distanceMatrix[i-1][j-1]) + 1; // Вычисление значения для двух символов и прибавление 1, как стоимость изменения(вставки, удаления или замены)
//             }
//             cout << distanceMatrix[i][j] << " ";
//         }
//         cout << endl;
//     }

//     return distanceMatrix[firstStringLength][secondStringLength]; // Возвращение последнего элемента матрицы, как результат
// }


int main() {
    string x;
    string y;
    cin >> x;
    cin >> y;
    cout << WagnerFisherAlgorithm(x, y);
    return 0;
}
