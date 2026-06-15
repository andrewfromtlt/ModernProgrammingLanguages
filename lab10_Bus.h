#ifndef LAB10_BUS_H
#define LAB10_BUS_H

#include <string>
#include <iostream>

// Структура, хранящая данные об автобусе
struct Bus {
    int busNumber;
    std::string driverName;
    int routeNumber;

    // Перегрузка оператора сравнения для поиска по номеру автобуса
    bool operator==(int num) const { 
        return busNumber == num; 
    }

    // Перегрузка оператора вывода для удобной печати
    friend std::ostream& operator<<(std::ostream& os, const Bus& b) {
        os << "Bus #" << b.busNumber 
           << " | Route: " << b.routeNumber 
           << " | Driver: " << b.driverName;
        return os;
    }
};

#endif // LAB10_BUS_H