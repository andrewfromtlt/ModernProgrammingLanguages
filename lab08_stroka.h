#ifndef LAB08_STROKA_H
#define LAB08_STROKA_H

#include <iostream>

class Stroka {
private:
    char* str; 
    
    // Вспомогательные закрытые методы
    int custom_strlen(const char* s) const;
    void custom_strcpy(char* dest, const char* src);

public:
    Stroka();
    Stroka(const char* string);
    ~Stroka();

    // ЗАДАНИЕ 1: Перегрузка операций помещения (<<) и извлечения (>>)
    // Объявляем их дружественными (friend), чтобы они имели доступ к приватному полю str
    friend std::ostream& operator<<(std::ostream& os, const Stroka& s);
    friend std::istream& operator>>(std::istream& is, Stroka& s);
};

#endif // LAB08_STROKA_H