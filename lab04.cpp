// Лабораторная работа №4

// Цель работы: 
// приобретение навыков обработки строковых данных (C-строк).

// Состав работы:
//	1. Использование стандартных библиотечных функций работы со строками (strlen, strcat, strcpy, strcmp).
//	2. Написание собственных (пользовательских) версий функций: определения длины (тремя разными способами), 
//     копирования, сравнения и конкатенации строк.
//	3. Переписывание программы с использованием динамического выделения памяти под строки (malloc, free).
//	4. Замена malloc на calloc и анализ их различий.
//	5. Организация массива динамических строк и применение к ним написанных функций.

#include <iostream>
#include <cstring> // Для стандартных функций (используются для проверки, если нужно)
#include <cstdlib> // Для выделения динамической памяти (malloc, calloc, free)

// --- ЗАДАНИЕ 2: Собственные функции для работы со строками ---

// Способ 1: Определение длины через индексацию массива
int dlina1(const char* str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

// Способ 2: Определение длины через арифметику указателей
int dlina2(const char* str) {
    const char* ptr = str;
    while (*ptr) { // Пока не встретим нуль-терминатор
        ptr++;
    }
    return ptr - str; // Разница адресов равна количеству символов
}

// Способ 3: Определение длины через компактный цикл for
int dlina3(const char* str) {
    int len = 0;
    for (; *str; ++str, ++len);
    return len;
}

// Собственная функция копирования строк
void kopir(char* dest, const char* src) {
    // Копируем символ за символом, пока не скопируем '\0'
    while ((*dest++ = *src++)); 
}

// Собственная функция сравнения строк (аналог strcmp)
int sravn(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    // Возвращаем разницу кодов первых несовпадающих символов
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

// Собственная функция конкатенации (сцепления) строк
void konkat(char* dest, const char* src) {
    while (*dest) {
        dest++; // Сдвигаем указатель в конец первой строки
    }
    while ((*dest++ = *src++)); // Дописываем вторую строку
}

int main() {
    // --- Демонстрация Заданий 1 и 2 ---
    std::cout << "--- Task 1 & 2: Custom String Functions ---\n";
    
    // Выделяем массивы достаточного размера, чтобы избежать переполнения при конкатенации
    char str1[100] = "qwerty"; 
    char str2[] = "1234567890";

    std::cout << "Length str1 (Method 1) = " << dlina1(str1) << "\n";
    std::cout << "Length str2 (Method 2) = " << dlina2(str2) << "\n";
    std::cout << "Length str2 (Method 3) = " << dlina3(str2) << "\n";

    char str3[100];
    kopir(str3, str1);
    std::cout << "Copy result (str3): " << str3 << "\n";

    std::cout << "Compare result (str1, str2): " << sravn(str1, str2) << "\n";

    konkat(str1, str2);
    std::cout << "Concat result (str1 + str2): " << str1 << "\n\n";

    // --- Демонстрация Заданий 3 и 4: Динамическая память ---
    std::cout << "--- Task 3 & 4: malloc and calloc ---\n";
    /*
     * ОТВЕТ НА ВОПРОС ПУНКТА 4:
     * malloc(size) - просто выделяет size байт памяти. Память содержит непредсказуемый "мусор".
     * calloc(count, size) - выделяет память и сразу заполняет её нулями (\0). 
     * Для строк calloc удобнее, так как память сразу становится валидной пустой строкой.
     */
    
    // В C++ возвращаемое значение malloc/calloc нужно явно приводить к нужному типу указателя
    char* d_str1 = (char*)std::calloc(50, sizeof(char)); 
    char* d_str2 = (char*)std::malloc(50 * sizeof(char)); 

    kopir(d_str1, "Hello, ");
    kopir(d_str2, "Dynamic World!");
    
    konkat(d_str1, d_str2);
    std::cout << "Dynamic concat result: " << d_str1 << "\n\n";

    // Обязательно освобождаем память, чтобы не было утечек
    std::free(d_str1);
    std::free(d_str2);

    // --- Демонстрация Задания 5: Массив строк ---
    std::cout << "--- Task 5: Array of Strings ---\n";
    const int numStrings = 3;
    char* strArray[numStrings]; // Массив указателей на строки

    // Выделяем память под каждую строку
    for (int i = 0; i < numStrings; ++i) {
        strArray[i] = (char*)std::calloc(50, sizeof(char));
    }

    kopir(strArray[0], "Apple");
    kopir(strArray[1], "Banana");
    
    std::cout << "Comparing array elements [0] and [1]: " << sravn(strArray[0], strArray[1]) << "\n";
    
    // Собираем элементы массива в третью строку
    kopir(strArray[2], strArray[0]);
    konkat(strArray[2], " + ");
    konkat(strArray[2], strArray[1]);
    
    std::cout << "Combined array string [2]: " << strArray[2] << "\n";

    // Освобождаем память массива
    for (int i = 0; i < numStrings; ++i) {
        std::free(strArray[i]);
    }

    return 0;
}