#include "lab07_shapes.h"

#ifndef delay
#include <windows.h>
#define delay(ms) Sleep(ms)
#endif

// ================= POINT =================
Point::Point(int XN, int YN, int Color) : X(XN), Y(YN), Cvet(Color) {}

void Point::Show() {
    putpixel(X, Y, Cvet);
}

void Point::Hide() {
    putpixel(X, Y, getbkcolor()); // Скрываем, закрашивая цветом фона
}

void Point::Locat(int& XL, int& YL) {
    XL = X;
    YL = Y;
}

void Point::UpdateState() {
    // Базовая точка не имеет анимации формы
}

void Point::Fly(int Cost) {
    int XX, YY;
    Show();
    
    // Аналог Repeat ... Until Keypressed
    while (!kbhit()) {
        Locat(XX, YY);
        
        // Генерация новых координат (аналог Random из Паскаля)
        do {
            XX = XX + (int)(((rand() / (double)RAND_MAX) - 0.5) * Cost);
        } while (XX <= 0 || XX >= getmaxx());

        do {
            YY = YY + (int)(((rand() / (double)RAND_MAX) - 0.5) * Cost);
        } while (YY <= 0 || YY >= getmaxy());

        Hide(); // Скрываем на старом месте
        X = XX;
        Y = YY;
        
        UpdateState(); // ЗАДАНИЕ 2: Изменяем цвет и сектор перед новой отрисовкой
        
        Show(); // Рисуем на новом месте
        delay(150); // Задержка для плавности
    }
    getch(); // Очищаем буфер после нажатия клавиши, чтобы не сработало дважды
}


// ================= KRUG =================
Krug::Krug(int XN, int YN, int R, int Color) : Point(XN, YN, Color), Radius(R) {}

void Krug::Show() {
    setcolor(Cvet);
    setfillstyle(SOLID_FILL, Cvet);
    pieslice(X, Y, 0, 360, Radius);
}

void Krug::Hide() {
    int bk = getbkcolor();
    setcolor(bk);
    setfillstyle(SOLID_FILL, bk);
    pieslice(X, Y, 0, 360, Radius);
}


// ================= RING =================
Ring::Ring(int XN, int YN, int R, int Color, int Wid) 
    : Krug(XN, YN, R, Color), Width(Wid), StartAngle(90), EndAngle(320), isWidening(true) {}

void Ring::Show() {
    setcolor(Cvet);
    // Используем штриховку или заливку
    setfillstyle(INTERLEAVE_FILL, Cvet); 
    pieslice(X, Y, StartAngle, EndAngle, Radius);

    // Хитрость кольца: рисуем внутренний круг цветом фона (стираем сердцевину)
    int bk = getbkcolor();
    setcolor(bk);
    setfillstyle(SOLID_FILL, bk);
    pieslice(X, Y, 0, 360, Radius - Width);
}

void Ring::Hide() {
    int bk = getbkcolor();
    setcolor(bk);
    setfillstyle(SOLID_FILL, bk);
    pieslice(X, Y, 0, 360, Radius);
}

// ЗАДАНИЕ 2: Расширение/сужение вырезанного сектора и смена цвета
void Ring::UpdateState() {
    // Смена цвета на любой доступный в BGI (от 1 до 15)
    Cvet = 1 + rand() % 15;

    // Анимация "дыхания" сектора
    if (isWidening) {
        StartAngle -= 5;
        EndAngle += 5;
        if (StartAngle <= 0 || EndAngle >= 360) {
            isWidening = false; // Достигли предела, начинаем сужаться
        }
    } else {
        StartAngle += 5;
        EndAngle -= 5;
        if (StartAngle >= 90 || EndAngle <= 270) {
            isWidening = true;  // Достигли минимума, начинаем расширяться
        }
    }
}