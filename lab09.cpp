// Лабораторная работа №9

// Цель работы: 
// знакомство с механизмом шаблонов C++; 
// создание и использование шаблонов функций и шаблонов классов в С++.

// Состав работы:
//  1. Отладить программу, иллюстрирующую применение шаблона Sort к типу, 
//     определенному пользователем (класс Money).
//  2. Выполнить примеры из пунктов 9.1.2 (перегрузка шаблонов) 
//     и 9.1.3 (специализация шаблонов) на примере функции getmax.
//  3. Написать программу, выполняющую сортировку железнодорожного состава 
//     с использованием тупика (рис. 1). 
//     Работу выполнить с использованием шаблона класса TStack.

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>

// ==============================================================================
// ЗАДАНИЕ 1: Шаблоны функций и их применение к пользовательским типам
// ==============================================================================

// Пользовательский класс Деньги
class Money {
private:
    long dollars;
    int cents;
public:
    Money(long d = 0, int c = 0) : dollars(d), cents(c) {}

    // Перегрузка оператора > для использования внутри шаблона Sort
    // В современном C++ операторы сравнения помечаются как const, так как они не меняют объект
    bool operator>(const Money& amt) const {
        return (dollars > amt.dollars) || ((dollars == amt.dollars) && (cents > amt.cents));
    }

    // Перегрузка вывода для удобства
    friend std::ostream& operator<<(std::ostream& os, const Money& amt) {
        os << "$" << amt.dollars << "." << std::setfill('0') << std::setw(2) << amt.cents;
        return os;
    }
};

// Шаблонная функция сортировки (Осовремененный пузырек, работающий с std::vector)
template <class T>
void Sort(std::vector<T>& array) {
    size_t size = array.size();
    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = size - 1; j > i; --j) {
            // Вот здесь неявно вызывается перегруженный operator> для типа Money
            if (array[i] > array[j]) {
                std::swap(array[i], array[j]);
            }
        }
    }
}


// ==============================================================================
// ЗАДАНИЕ 2: Перегрузка и специализация шаблонов (на примере getmax)
// ==============================================================================

// 1. Базовый шаблон для двух аргументов
template <class T>
T getmax(T t1, T t2) {
    return (t1 > t2) ? t1 : t2;
}

// 2. Перегрузка шаблона: вариант для вектора (массива)
template <class T>
T getmax(const std::vector<T>& t) {
    T retval = t[0];
    for (size_t i = 1; i < t.size(); ++i) {
        if (t[i] > retval) retval = t[i];
    }
    return retval;
}

// 3. Специализация шаблона для строк (C-строк)
// Если мы передадим "string", компилятор выберет эту версию, используя strcmp
template <>
const char* getmax<const char*>(const char* s1, const char* s2) {
    return std::strcmp(s1, s2) > 0 ? s1 : s2;
}


// ==============================================================================
// ЗАДАНИЕ 3: Шаблоны классов (Стек) и сортировка поездов
// ==============================================================================

// Осовремененный шаблон класса Стек. Вместо ручного new/delete используем std::vector внутри.
template <class T>
class TStack {
private:
    std::vector<T> items;
public:
    void push(const T& item) {
        items.push_back(item);
    }

    T pop() {
        if (items.empty()) throw std::out_of_range("Stack is empty");
        T val = items.back();
        items.pop_back();
        return val;
    }

    T top() const {
        if (items.empty()) throw std::out_of_range("Stack is empty");
        return items.back();
    }

    bool isEmpty() const {
        return items.empty();
    }
};

// Функция, решающая задачу сортировки вагонов с помощью тупика (стека)
void sortTrain() {
    std::cout << "\n--- Task 3: Train Sorting using Siding (TStack) ---\n";
    
    // Входящий состав (номера вагонов вперемешку)
    std::vector<int> incoming = {3, 1, 2, 5, 4}; 
    std::vector<int> outgoing;   // Отсортированный состав
    TStack<int> siding;          // Тупик (действует как стек)
    
    int expectedCar = 1;         // Вагон, который мы ожидаем отправить на выход первым

    std::cout << "Incoming train sequence: [ ";
    for (int car : incoming) std::cout << car << " ";
    std::cout << "]\n\n";

    for (int car : incoming) {
        std::cout << "[ACTION] Moving car " << car << " from main track to siding.\n";
        siding.push(car);
        
        // Пока в тупике есть вагоны и крайний вагон совпадает с тем, что нам нужен на выходе
        while (!siding.isEmpty() && siding.top() == expectedCar) {
            int sortedCar = siding.pop();
            std::cout << "[ACTION] Moving car " << sortedCar << " from siding to output track.\n";
            outgoing.push_back(sortedCar);
            expectedCar++; // Теперь ожидаем следующий по порядку вагон
        }
    }

    // Если тупик опустел, значит все вагоны успешно выехали по порядку
    if (siding.isEmpty()) {
        std::cout << "\n[RESULT] Train sorted successfully!\n";
        std::cout << "Outgoing train sequence: [ ";
        for (int car : outgoing) std::cout << car << " ";
        std::cout << "]\n";
    } else {
        // Некоторые последовательности невозможно отсортировать одним стеком
        std::cout << "\n[RESULT] Error: Sorting impossible for this sequence with only one siding.\n";
    }
}


// ==============================================================================
// ГЛАВНАЯ ФУНКЦИЯ
// ==============================================================================

int main() {
    // --- Демонстрация Задания 1 ---
    std::cout << "--- Task 1: Template Sorting with Custom Class (Money) ---\n";
    std::vector<Money> wallets = { Money(19, 10), Money(99, 99), Money(99, 95), Money(19, 95) };
    
    Sort(wallets); // Компилятор генерирует Sort<Money>

    for (size_t i = 0; i < wallets.size(); ++i) {
        std::cout << "Wallet [" << i << "] = " << wallets[i] << "\n";
    }

    // --- Демонстрация Задания 2 ---
    std::cout << "\n--- Task 2: Template Overloading & Specialization (getmax) ---\n";
    
    int i1 = 3, i2 = 5;
    std::vector<int> numbers = {3, 9, 5, 8};
    const char* s1 = "apple";
    const char* s2 = "banana";

    // Вызов базового шаблона
    std::cout << "Max int (3 vs 5): " << getmax(i1, i2) << "\n";
    
    // Вызов перегруженного шаблона для вектора
    std::cout << "Max in array [3, 9, 5, 8]: " << getmax(numbers) << "\n";
    
    // Вызов специализированного шаблона для строк
    std::cout << "Max string ('apple' vs 'banana'): " << getmax(s1, s2) << "\n";

    // --- Демонстрация Задания 3 ---
    sortTrain();

    return 0;
}