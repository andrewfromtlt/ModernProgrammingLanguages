// Лабораторная работа №2

// Цель работы: 
// Приобретение навыков работы с двумерными массивами (матрицами), реализация алгоритмов поиска элементов 
// по заданным критериям и освоение инструментов форматирования вывода данных.

// Состав работы:
//	1. Создание матрицы и её автоматическое заполнение случайными вещественными числами.
//	2. Написание функций поиска глобального минимума и максимума матрицы, а также экстремумов 
//     на её главной и второстепенной диагоналях.
//	3. Поиск минимальных и максимальных значений в нижнетреугольной и верхнетреугольной частях матрицы.
//	4. Вычисление сумм, экстремумов и средних арифметических значений отдельно для каждой строки 
//     и каждого столбца матрицы.
//	5. Реализация алгоритма поиска элемента матрицы, чьё значение наиболее близко к общему среднему 
//     арифметическому всей матрицы.
//	6. Форматирование табличного вывода матрицы в стандартный поток с помощью функций управления шириной поля 
//     и точностью отображения долей (setw и setprecision).

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

const int N = 5; // Размерность квадратной матрицы

// Функция для вывода матрицы на экран
void printMatrix(const float m[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << std::setw(8) << std::fixed << std::setprecision(2) << m[i][j];
        }
        std::cout << "\n";
    }
}

// --- Функции поиска минимума и максимума ---

float getMatrixMin(const float m[N][N]) {
    float minVal = m[0][0];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (m[i][j] < minVal) minVal = m[i][j];
    return minVal;
}

float getMatrixMax(const float m[N][N]) {
    float maxVal = m[0][0];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (m[i][j] > maxVal) maxVal = m[i][j];
    return maxVal;
}

// --- Обработка треугольных частей матрицы ---

// Для нижнетреугольной части условие: индекс строки >= индексу столбца (i >= j)
float getMaxLowerTriangle(const float m[N][N]) {
    float maxVal = m[0][0];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= i; ++j)
            if (m[i][j] > maxVal) maxVal = m[i][j];
    return maxVal;
}

// Для верхнетреугольной части условие: индекс строки <= индексу столбца (i <= j)
float getMinUpperTriangle(const float m[N][N]) {
    float minVal = m[0][0];
    for (int i = 0; i < N; ++i)
        for (int j = i; j < N; ++j)
            if (m[i][j] < minVal) minVal = m[i][j];
    return minVal;
}

// --- Обработка диагоналей ---

// Главная диагональ: индексы равны (i == j)
float getMaxMainDiag(const float m[N][N]) {
    float maxVal = m[0][0];
    for (int i = 0; i < N; ++i)
        if (m[i][i] > maxVal) maxVal = m[i][i];
    return maxVal;
}

// Второстепенная диагональ: сумма индексов равна N - 1 (i + j == N - 1)
float getMinSecDiag(const float m[N][N]) {
    float minVal = m[0][N - 1];
    for (int i = 0; i < N; ++i)
        if (m[i][N - 1 - i] < minVal) minVal = m[i][N - 1 - i];
    return minVal;
}

// --- Расчет средних арифметических ---

float getMatrixMean(const float m[N][N]) {
    float sum = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            sum += m[i][j];
    return sum / (N * N);
}

// Элемент, наиболее близкий к среднему арифметическому
float getClosestToMean(const float m[N][N]) {
    float mean = getMatrixMean(m);
    float closest = m[0][0];
    float minDiff = std::abs(m[0][0] - mean); // Используем модуль разности

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            float diff = std::abs(m[i][j] - mean);
            if (diff < minDiff) {
                minDiff = diff;
                closest = m[i][j];
            }
        }
    }
    return closest;
}

// --- Обработка строк и столбцов ---

void processRowsAndCols(const float m[N][N]) {
    std::cout << "\n--- Row and Column Stats ---\n";
    for (int i = 0; i < N; ++i) {
        float rowSum = 0, colSum = 0;
        float rowMax = m[i][0], colMax = m[0][i];
        
        for (int j = 0; j < N; ++j) {
            rowSum += m[i][j]; // Фиксируем строку i, бежим по столбцам j
            colSum += m[j][i]; // Фиксируем столбец i, бежим по строкам j
            
            if (m[i][j] > rowMax) rowMax = m[i][j];
            if (m[j][i] > colMax) colMax = m[j][i];
        }
        
        std::cout << "Row " << i << ": Sum = " << std::setw(6) << rowSum 
                  << ", Max = " << std::setw(5) << rowMax 
                  << ", Mean = " << std::setw(5) << (rowSum / N) << "\n";
        
        std::cout << "Col " << i << ": Sum = " << std::setw(6) << colSum 
                  << ", Max = " << std::setw(5) << colMax 
                  << ", Mean = " << std::setw(5) << (colSum / N) << "\n";
    }
}

int main() {
    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    float m[N][N];
    
    // Заполнение матрицы случайными числами
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            m[i][j] = (std::rand() % 1000) / 10.0f; // Числа от 0.0 до 99.9
        }
    }

    std::cout << "--- Generated Matrix ---\n";
    printMatrix(m);

    std::cout << "\n--- Matrix Analysis ---\n";
    std::cout << "Global Min: " << getMatrixMin(m) << "\n";
    std::cout << "Global Max: " << getMatrixMax(m) << "\n";
    std::cout << "Global Mean: " << getMatrixMean(m) << "\n";
    
    std::cout << "Closest to Mean: " << getClosestToMean(m) << "\n";

    std::cout << "\n--- Triangles and Diagonals ---\n";
    std::cout << "Max in Lower Triangle: " << getMaxLowerTriangle(m) << "\n";
    std::cout << "Min in Upper Triangle: " << getMinUpperTriangle(m) << "\n";
    std::cout << "Max on Main Diagonal: " << getMaxMainDiag(m) << "\n";
    std::cout << "Min on Secondary Diagonal: " << getMinSecDiag(m) << "\n";

    processRowsAndCols(m);

    return 0;
}