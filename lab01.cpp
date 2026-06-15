// Лабораторная работа №1

// Цель работы: 
// Практическое знакомство с базовой структурой программы на С++, 
// освоение арифметических операций над указателями и изучение различных правил передачи параметров в функции.

// Состав работы:
//	1. Реализация и модификация алгоритма возведения числа в степень с произвольным основанием.
//	2. Исследование работы с указателями, включая инкремент указателя и вычисление разности 
//     между указателями для различных типов данных.
//	3. Написание и сравнение трех вариантов функции обмена значениями (swap) двух переменных:
//     с передачей параметров по значению (int), по указателю (int*) и по ссылке (int&).

#include <iostream>

// --- ЗАДАНИЕ 1: Функция возведения в степень ---
int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

// --- ЗАДАНИЕ 3: Функции обмена значениями ---
// Вариант 1: Передача по значению (оригиналы вне функции не изменятся)
void obmen1(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

// Вариант 2: Передача по указателю (изменяет оригиналы через адреса памяти)
void obmen2(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Вариант 3: Передача по ссылке (самый безопасный метод C++ для изменения оригиналов)
void obmen3(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    // --- Task 1 ---
    std::cout << "--- Task 1: Power calculation ---\n";
    int base = 3;
    int exp = 4;
    int res = power(base, exp);
    std::cout << base << " ^ " << exp << " = " << res << "\n\n";

    // --- Task 2 ---
    std::cout << "--- Task 2: Pointers ---\n";
    int mas[] = {100, 200, 300};
    
    int* ptr1 = mas;     // Указывает на начало массива (mas[0])
    int* ptr2 = &mas[2]; // Указывает на третий элемент (mas[2])

    std::cout << "ptr1 points to: " << ptr1 << ", value = " << *ptr1 << "\n";
    
    ptr1++; // Сдвиг указателя на один элемент типа int (на 4 байта вперед)
    std::cout << "ptr1 after increment points to: " << ptr1 << ", value = " << *ptr1 << "\n";

    std::cout << "ptr2 points to: " << ptr2 << ", value = " << *ptr2 << "\n";
    
    ++ptr2; 
    // Разница между указателями возвращает количество элементов, а не байт
    std::cout << "Pointer difference (ptr2 - ptr1) = " << (ptr2 - ptr1) << " elements\n\n";

    // --- Task 3 ---
    std::cout << "--- Task 3: Value swapping ---\n";
    int val1 = 5;
    int val2 = 10;
    
    std::cout << "Initial values: val1 = " << val1 << ", val2 = " << val2 << "\n";
    
    obmen1(val1, val2);
    std::cout << "After obmen1 (by value): val1 = " << val1 << ", val2 = " << val2 << "\n";
    
    obmen2(&val1, &val2);
    std::cout << "After obmen2 (by pointer): val1 = " << val1 << ", val2 = " << val2 << "\n";
    
    obmen3(val1, val2);
    std::cout << "After obmen3 (by reference): val1 = " << val1 << ", val2 = " << val2 << "\n";

    return 0;
}