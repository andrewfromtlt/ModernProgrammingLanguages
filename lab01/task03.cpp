#include <iostream>

// Подключение стандартного пространства имён
using namespace std;

// Прототипы функций
void obmen1(int, int);
void obmen2(int*, int*);
void obmen3(int&, int&);

int main()
{
    int a = 2, b = 5;

    cout << "до обмена: a=" << a << " b=" << b << endl;

    // 1. Передача по значению (копия)
    obmen1(a, b);
    cout << "после обмена 1: a=" << a << " b=" << b << endl;

    // 2. Передача по адресу (указатели)
    obmen2(&a, &b);
    cout << "после обмена 2: a=" << a << " b=" << b << endl;

    // 3. Передача по ссылке
    obmen3(a, b);
    cout << "после обмена 3: a=" << a << " b=" << b << endl;

    return 0;
}

// Реализация функций
void obmen1(int x, int y) {
    int temp = x;
    x = y;
    y = temp;
}

void obmen2(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void obmen3(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}
