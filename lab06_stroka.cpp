#include "lab06_stroka.h"
#include <iostream>

// --- Вспомогательные функции для работы со строками (из ЛР №4) ---
// Прячем их внутри файла реализации, чтобы они не конфликтовали с другими файлами
namespace {
    int custom_strlen(const char* s) {
        int len = 0;
        while (s && s[len]) len++;
        return len;
    }

    void custom_strcpy(char* dest, const char* src) {
        if (!dest || !src) return;
        while ((*dest++ = *src++));
    }

    void custom_strcat(char* dest, const char* src) {
        if (!dest || !src) return;
        while (*dest) dest++;
        while ((*dest++ = *src++));
    }

    int custom_strcmp(const char* s1, const char* s2) {
        if (!s1 || !s2) return -1;
        while (*s1 && (*s1 == *s2)) {
            s1++;
            s2++;
        }
        return *(const unsigned char*)s1 - *(const unsigned char*)s2;
    }
}

// --- Определение методов класса Stroka ---

Stroka::Stroka() {
    str = new char[1];
    str[0] = '\0';
}

Stroka::Stroka(const char* string) {
    if (string) {
        str = new char[custom_strlen(string) + 1];
        custom_strcpy(str, string);
    } else {
        str = new char[1];
        str[0] = '\0';
    }
}

Stroka::Stroka(const Stroka& s) {
    str = new char[custom_strlen(s.str) + 1];
    custom_strcpy(str, s.str);
}

// Задание 4: Конструктор с выделением памяти заданного размера
Stroka::Stroka(int size) {
    if (size > 0) {
        str = new char[size];
        str[0] = '\0';
    } else {
        str = new char[1];
        str[0] = '\0';
    }
}

Stroka::~Stroka() {
    delete[] str; // Безопасное освобождение динамической памяти массива
}

Stroka& Stroka::operator=(const Stroka& s) {
    if (this != &s) { // Защита от самоприсваивания
        delete[] str; 
        str = new char[custom_strlen(s.str) + 1];
        custom_strcpy(str, s.str);
    }
    return *this;
}

Stroka Stroka::operator+(const Stroka& s) const {
    int newLength = custom_strlen(this->str) + custom_strlen(s.str) + 1;
    Stroka result(newLength); 
    
    custom_strcpy(result.str, this->str);
    custom_strcat(result.str, s.str);
    
    return result;
}

bool Stroka::operator==(const Stroka& s) const {
    return custom_strcmp(this->str, s.str) == 0;
}

int Stroka::dlina() const {
    return custom_strlen(str);
}

void Stroka::vvod() {
    char buffer[1024]; 
    std::cin >> buffer;
    
    delete[] str;
    str = new char[custom_strlen(buffer) + 1];
    custom_strcpy(str, buffer);
}

void Stroka::vyvod() const {
    std::cout << str;
}