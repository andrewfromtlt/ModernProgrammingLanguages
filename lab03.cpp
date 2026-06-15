// Лабораторная работа №3

// Цель работы: 
// освоение основных методов упорядочения числовых данных; 
// знакомство с реализацией различных алгоритмов сортировки средствами языка С++.

// Состав работы:
//	1. Изучение алгоритма сортировки массива методом «мини-макса».
//	2. Написание программ, сортирующих одномерный массив методами «пузырька» и «быстрой сортировки». 
//     Анализ возможности применения для многомерных массивов.
//	3. Для массива целых значений выполнение сортировки по возрастанию четных и по убыванию нечетных значений.
//	4. Сортировка массива по возрастанию на интервале индексов от N1 до N2.
//	5. Сортировка массива по убыванию на интервале индексов от N1 до N2.

#include <iostream>
#include <vector>
#include <algorithm> // Подключаем для std::swap и std::sort

// Вспомогательная функция для вывода массива в консоль
void printArray(const std::vector<int>& arr, const std::string& message) {
    std::cout << message << ":\n[ ";
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << "]\n";
}

// --- ЗАДАНИЕ 1: Сортировка методом "мини-макса" (Selection Sort) ---
void minimaxSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int imin = i; // Предполагаем, что текущий элемент - минимальный
        
        // Ищем индекс действительного минимального элемента в оставшейся части массива
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[imin]) {
                imin = j; 
            }
        }
        
        // Если минимальный элемент не на своем месте, используем современный std::swap
        if (imin != i) {
            std::swap(arr[i], arr[imin]);
        }
    }
}

// --- ЗАДАНИЕ 2: Пузырьковая сортировка ---
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    // Оптимизированный пузырек: останавливается, если проход завершился без обменов
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; 
    }
}

// --- ЗАДАНИЕ 2: Быстрая сортировка (Quick Sort) ---
// Функция разделения массива на две части относительно опорного элемента
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; 
    int i = (low - 1);
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Основная рекурсивная функция быстрой сортировки
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// --- ЗАДАНИЕ 3: Возрастание четных, убывание нечетных ---
void sortEvenOdd(std::vector<int>& arr) {
    // Используем современную лямбда-функцию для задания кастомных правил сортировки
    std::sort(arr.begin(), arr.end(), [](int a, int b) {
        bool isAEven = (a % 2 == 0);
        bool isBEven = (b % 2 == 0);
        
        if (isAEven && !isBEven) return true;  // Четные элементы ставим перед нечетными
        if (!isAEven && isBEven) return false; // Нечетные элементы уходят в конец
        if (isAEven && isBEven) return a < b;  // Если оба четные - сортируем по возрастанию
        return a > b;                          // Если оба нечетные - сортируем по убыванию
    });
}

// --- ЗАДАНИЕ 4 и 5: Сортировка подмассива (от N1 до N2) ---
void sortSubarray(std::vector<int>& arr, int n1, int n2, bool ascending) {
    // Проверка границ для предотвращения выхода за пределы памяти
    if (n1 < 0) n1 = 0;
    if (n2 >= static_cast<int>(arr.size())) n2 = arr.size() - 1;
    if (n1 >= n2) return;

    // Итераторы в C++ указывают на [начало, конец), поэтому к n2 прибавляем 1
    auto startIt = arr.begin() + n1;
    auto endIt = arr.begin() + n2 + 1;

    if (ascending) {
        std::sort(startIt, endIt); // Задание 4: По возрастанию
    } else {
        std::sort(startIt, endIt, std::greater<int>()); // Задание 5: По убыванию
    }
}

int main() {
    // Исходный массив для всех экспериментов
    std::vector<int> original = {15, 2, 8, 1, 4, 6, 3, 11, 5, 9, 12, 7, -2, 0};
    
    printArray(original, "Original array");

    std::cout << "\n--- Task 1: Minimax (Selection) Sort ---\n";
    std::vector<int> arrMinimax = original;
    minimaxSort(arrMinimax);
    printArray(arrMinimax, "After Minimax (Selection) Sort");

    std::cout << "\n--- Task 2: Sorting Algorithms ---\n";
    
    std::vector<int> arrBubble = original;
    bubbleSort(arrBubble);
    printArray(arrBubble, "After Bubble Sort");

    std::vector<int> arrQuick = original;
    quickSort(arrQuick, 0, arrQuick.size() - 1);
    printArray(arrQuick, "After Quick Sort");

    /*  Ответ на теоретический вопрос: Можно ли эти функции применять к многомерным массивам?
    
        Напрямую передать многомерный массив (например, int arr[3][3]) в функцию, 
        принимающую одномерный указатель (int*), нельзя из-за несовпадения типов указателей. 
        Однако, поскольку в C++ многомерные массивы располагаются в памяти единым 
        непрерывным блоком, можно выполнить явное приведение типов (flattening) 
        к одномерному указателю и отсортировать память как единый сплошной массив.
    */

    std::cout << "\n--- Task 3: Custom Sort (Evens Ascending, Odds Descending) ---\n";
    std::vector<int> arrEvenOdd = original;
    sortEvenOdd(arrEvenOdd);
    printArray(arrEvenOdd, "After Custom Even/Odd Sort");

    std::cout << "\n--- Task 4 & 5: Subarray Sorting [N1, N2] ---\n";
    std::vector<int> arrSub = original;
    int n1 = 3, n2 = 8; // Интервал индексов для сортировки
    
    std::cout << "Target interval indices: [" << n1 << " to " << n2 << "]\n";
    
    sortSubarray(arrSub, n1, n2, true);
    printArray(arrSub, "Task 4: Subarray sorted Ascending");

    arrSub = original; // Сбрасываем массив в исходное состояние
    sortSubarray(arrSub, n1, n2, false);
    printArray(arrSub, "Task 5: Subarray sorted Descending");

    return 0;
}