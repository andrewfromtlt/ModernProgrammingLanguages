#ifndef LAB06_STROKA_H
#define LAB06_STROKA_H

// --- Интерфейс класса Stroka ---
class Stroka {
private:
    char* str; // Указатель на динамическую память для хранения строки

public:
    Stroka();                               // Конструктор по умолчанию
    Stroka(const char* string);             // Конструктор инициализации строкой
    Stroka(const Stroka& s);                // Конструктор копирования
    Stroka(int size);                       // Конструктор с заданным размером памяти (Задание 4)
    
    ~Stroka();                              // Деструктор (обязателен при использовании new[])

    Stroka& operator=(const Stroka& s);     // Оператор присваивания
    Stroka operator+(const Stroka& s) const;// Оператор конкатенации
    bool operator==(const Stroka& s) const; // Оператор сравнения
    
    int dlina() const;                      // Определение длины строки
    void vvod();                            // Ввод строки с клавиатуры
    void vyvod() const;                     // Вывод строки на экран
};

#endif // LAB06_STROKA_H