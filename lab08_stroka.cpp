#include "lab08_stroka.h"

// --- Вспомогательные методы ---
int Stroka::custom_strlen(const char* s) const {
    int len = 0;
    while (s && s[len]) len++;
    return len;
}

void Stroka::custom_strcpy(char* dest, const char* src) {
    if (!dest || !src) return;
    while ((*dest++ = *src++));
}

// --- Базовые конструкторы и деструктор ---
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

Stroka::~Stroka() {
    delete[] str;
}

// --- ЗАДАНИЕ 1: Реализация потоковых операторов ---

// Оператор вывода (помещения в поток)
std::ostream& operator<<(std::ostream& os, const Stroka& s) {
    if (s.str) {
        os << s.str; // Просто направляем внутренний C-массив в стандартный поток
    }
    return os;
}

// Оператор ввода (извлечения из потока)
std::istream& operator>>(std::istream& is, Stroka& s) {
    char buffer[1024];
    // Читаем слово из потока. Оператор >> автоматически игнорирует начальные пробелы
    if (is >> buffer) {
        delete[] s.str; // Очищаем старую память
        s.str = new char[s.custom_strlen(buffer) + 1];
        s.custom_strcpy(s.str, buffer);
    }
    return is;
}