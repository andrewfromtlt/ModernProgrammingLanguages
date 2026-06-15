#ifndef LAB10_SLINKEDLIST_H
#define LAB10_SLINKEDLIST_H

#include <iostream>
#include <string>

// Шаблон узла односвязного списка
template <typename T>
struct Node {
    T data;
    Node* next;
    
    // Конструктор узла
    Node(const T& d) : data(d), next(nullptr) {}
};

// Шаблон класса "односвязный линейный список"
template <typename T>
class SLinkedList {
private:
    Node<T>* head; // Указатель на начало
    Node<T>* tail; // Указатель на конец (для быстрого добавления)

public:
    SLinkedList() : head(nullptr), tail(nullptr) {}
    
    ~SLinkedList() { 
        clear(); // Очистка памяти при удалении списка
    }

    // Добавление элемента в конец списка
    void push_back(const T& item) {
        Node<T>* newNode = new Node<T>(item);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Удаление элемента по ключу (возвращает true, если элемент найден и удален)
    // Извлеченные данные сохраняются в removedItem для переноса в другой список
    template <typename Key>
    bool remove(const Key& key, T& removedItem) {
        Node<T>* current = head;
        Node<T>* prev = nullptr;

        while (current) {
            if (current->data == key) { // Сравниваем данные с ключом
                removedItem = current->data; 
                
                if (prev) {
                    prev->next = current->next; // Удаление из середины/конца
                } else {
                    head = current->next;       // Удаление из начала
                }
                
                if (current == tail) {
                    tail = prev;                // Если удалили хвост, сдвигаем указатель
                }
                
                delete current; // Освобождаем динамическую память узла
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    // Вывод списка на экран
    void print(const std::string& msg) const {
        std::cout << "\n--- " << msg << " ---\n";
        if (!head) {
            std::cout << "List is empty.\n";
            return;
        }
        Node<T>* current = head;
        while (current) {
            std::cout << current->data << "\n";
            current = current->next;
        }
        std::cout << "-----------------------\n";
    }

    // Очистка списка
    void clear() {
        Node<T>* current = head;
        while (current) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
    }
};

#endif // LAB10_SLINKEDLIST_H