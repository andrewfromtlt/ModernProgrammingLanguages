#ifndef LAB07_SHAPES_H
#define LAB07_SHAPES_H

#include <graphics.h>
#include <conio.h>    // Для kbhit() - аналог Keypressed из Паскаля
#include <cstdlib>
#include <ctime>

// --- Базовый класс Точка ---
class Point {
protected:
    int X, Y;
    int Cvet;
public:
    Point(int XN, int YN, int Color);
    virtual ~Point() {}                     // Виртуальный деструктор для полиморфизма
    
    virtual void Show();                    // Виртуальные методы отрисовки
    virtual void Hide();
    void Locat(int& XL, int& YL);
    void Fly(int Cost);
    virtual void UpdateState();             // Хук для выполнения Задания 2
};

// --- Производный класс Круг ---
class Krug : public Point {
protected:
    int Radius;
public:
    Krug(int XN, int YN, int R, int Color);
    void Show() override;
    void Hide() override;
};

// --- Производный класс Кольцо ---
class Ring : public Krug {
protected:
    int Width;
    int StartAngle;                         // Углы для отрисовки сектора (Задание 2)
    int EndAngle;
    bool isWidening;                        // Флаг расширения/сужения сектора
public:
    Ring(int XN, int YN, int R, int Color, int Wid);
    void Show() override;
    void Hide() override;
    void UpdateState() override;            // Реализация Задания 2
};

#endif // LAB07_SHAPES_H