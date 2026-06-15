// Лабораторная работа №10

// Цель работы: 
// знакомство со средствами создания линейных списков в С++; 
// использование шаблонов для работы с динамическими структурами.

// Состав работы:
//  1. Создание шаблона класса «односвязный линейный список».
//  2. Реализация программы учета автобусов в парке и на маршруте 
//     (перемещение данных между двумя динамическими списками).

#include "lab10_SLinkedList.h"
#include "lab10_Bus.h"
#include <iostream>

// Функция вывода меню
void showMenu() {
    std::cout << "\n--- Bus Depot Control System ---\n";
    std::cout << "1. Bus leaves the depot (Move to Route)\n";
    std::cout << "2. Bus enters the depot (Return from Route)\n";
    std::cout << "3. Show all buses in the Depot\n";
    std::cout << "4. Show all buses on the Route\n";
    std::cout << "0. Exit\n";
    std::cout << "Select action: ";
}

int main() {
    // Создаем два списка на основе нашего шаблона
    SLinkedList<Bus> depot;
    SLinkedList<Bus> route;

    // Начальное формирование списка автобусов в парке
    depot.push_back({101, "Ivanov I.I.", 15});
    depot.push_back({102, "Petrov P.P.", 15});
    depot.push_back({205, "Sidorov S.S.", 24});
    depot.push_back({310, "Smirnov A.A.", 40});

    int choice;
    do {
        showMenu();
        std::cin >> choice;

        if (choice == 1) { 
            // Выезд из парка
            int bNum;
            std::cout << "Enter the number of the bus leaving the depot: ";
            std::cin >> bNum;
            
            Bus tempBus; // Буфер для перемещаемого автобуса
            // Пытаемся удалить автобус из парка и сохранить его данные в tempBus
            if (depot.remove(bNum, tempBus)) {
                route.push_back(tempBus); // Добавляем извлеченный автобус на маршрут
                std::cout << "[SUCCESS] Bus #" << bNum << " has departed to the route.\n";
            } else {
                std::cout << "[ERROR] Bus #" << bNum << " not found in the depot.\n";
            }
            
        } else if (choice == 2) { 
            // Въезд в парк
            int bNum;
            std::cout << "Enter the number of the bus entering the depot: ";
            std::cin >> bNum;
            
            Bus tempBus;
            if (route.remove(bNum, tempBus)) {
                depot.push_back(tempBus); // Возвращаем автобус обратно в парк
                std::cout << "[SUCCESS] Bus #" << bNum << " has returned to the depot.\n";
            } else {
                std::cout << "[ERROR] Bus #" << bNum << " not found on the route.\n";
            }
            
        } else if (choice == 3) {
            // Вывод автобусов в парке
            depot.print("Buses currently in the Depot");
            
        } else if (choice == 4) {
            // Вывод автобусов на маршруте
            route.print("Buses currently on the Route");
        }
        
    } while (choice != 0);

    std::cout << "System shutting down...\n";
    return 0;
}