// Лабораторная работа №6

// Цель работы: 
// знакомство с механизмом описания классов C++; создание собственных типов данных.

// Состав работы:
//  1. Описание класса Stroka для работы со строкой (конструкторы, деструктор, перегрузка операций =, +, ==, методы ввода/вывода).
//  2. Логическое разделение кода на заголовочный файл (Stroka.h), файл реализации (Stroka.cpp) и главную функцию (main.cpp).
//  3. Замена стандартных библиотечных функций (strcpy, strlen и др.) на собственные аналоги, разработанные в ЛР №4.
//  4. Добавление конструктора, создающего экземпляр класса с использованием динамической памяти заданного размера. 
//     Обоснование: При выделении памяти через new[] в конструкторе, деструктор с вызовом delete[] строго необходим 
//     для предотвращения утечек памяти.

#include <iostream>
#include "lab06_stroka.h" // Подключаем наш заголовочный файл

int main() {
    std::cout << "--- Testing Stroka Class ---\n";
    
    Stroka s1("qwert");
    Stroka s3;
    Stroka s4(s1); // Тест конструктора копирования
    Stroka s5;

    std::cout << "Please enter a word for s3: ";
    s3.vvod();

    std::cout << "You entered s3: ";
    s3.vyvod();
    std::cout << "\n";

    // Тест присваивания
    s3 = "asdfg";
    std::cout << "After assignment s3 = \"asdfg\": ";
    s3.vyvod();
    std::cout << "\n";

    // Тест конкатенации
    s5 = s1 + s3 + s4;

    std::cout << "Length of s5 = " << s5.dlina() << "\n";
    std::cout << "String s5: ";
    s5.vyvod();
    std::cout << "\n";

    // Тесты сравнения
    if (s1 == s5) {
        std::cout << "Strings s1 and s5 are equal.\n";
    } else {
        std::cout << "Strings s1 and s5 are NOT equal.\n";
    }

    if (s1 == s4) {
        std::cout << "Strings s1 and s4 are equal.\n";
    }

    std::cout << "--- Destructors will automatically clean up memory now ---\n";
    return 0;
}