// Лабораторная работа №8

// Цель работы: 
// знакомство с классами потоков языка С++; 
// организация работы с файлами с помощью объектов-потоков; 
// изучение свойств потоков, применение методов, позволяющих вмешиваться в состояние потока.

// Состав работы:
//  1. Для класса Stroka предусмотреть возможность ввода-вывода его объектов при помощи операций помещения и извлечения.
//  2. Выполнить программы-примеры работы с потоками.
//  3. Программу-шифратор переписать с использованием классов потоков.
//  4. Изучить методы, позволяющие изменять состояние потоков, и написать программу, иллюстрирующую эти возможности.

#include <iostream>
#include <fstream>
#include <iomanip>
#include "lab08_stroka.h"

// --- ЗАДАНИЕ 3: Шифратор на файловых потоках ---
void encryptFileStreams(const std::string& inFile, const std::string& outFile, const std::string& key) {
    // Открываем потоки в бинарном режиме
    std::ifstream in(inFile, std::ios::binary);
    std::ofstream out(outFile, std::ios::binary);

    if (!in.is_open() || !out.is_open()) {
        std::cout << "[ERROR] Could not open files for encryption.\n";
        return;
    }

    size_t keyLen = key.length();
    if (keyLen == 0) return;

    size_t i = 0;
    char ch;
    // in.get(ch) - потоковый аналог fgetc
    while (in.get(ch)) {
        char encryptedChar = ch ^ key[i % keyLen];
        out.put(encryptedChar); // Потоковый аналог fputc
        i++;
    }

    std::cout << "[INFO] Encryption/Decryption completed via streams.\n";
} // Потоки in и out закроются автоматически благодаря деструкторам классов ifstream/ofstream

// --- ЗАДАНИЕ 4: Работа с состояниями потока ---
void demonstrateStreamStates() {
    std::cout << "\n--- Task 4: Stream States Demonstration ---\n";

    std::ifstream testStream("non_existent_file_123.txt");

    // Проверяем флаг ошибки failbit
    if (testStream.fail()) {
        std::cout << "[STATE] fail() is TRUE. File does not exist.\n";
    }

    // Вмешиваемся в состояние: сбрасываем флаги ошибок
    testStream.clear();
    std::cout << "[ACTION] Called clear().\n";
    std::cout << "[STATE] fail() is now " << (testStream.fail() ? "TRUE" : "FALSE") << ".\n";

    // Устанавливаем флаг ошибки вручную
    testStream.setstate(std::ios::failbit);
    std::cout << "[ACTION] Called setstate(ios::failbit).\n";
    
    // Проверка текущего состояния (rdstate)
    if (testStream.rdstate() & std::ios::failbit) {
        std::cout << "[STATE] rdstate() confirms failbit is set.\n";
    }

    // Создаем реальный файл и читаем его до EOF
    std::ofstream tempOut("temp_state_test.txt");
    tempOut << "Hello";
    tempOut.close();

    std::ifstream tempIn("temp_state_test.txt");
    char c;
    while (tempIn.get(c)) {
        // Читаем пока не упремся в конец
    }
    
    // Проверяем достижение конца файла
    if (tempIn.eof()) {
        std::cout << "[STATE] eof() is TRUE. Reached end of file successfully.\n";
    }
}

int main() {
    // --- Демонстрация Задания 1 ---
    std::cout << "--- Task 1: Stream Overloading for Stroka ---\n";
    Stroka myStr;
    std::cout << "Enter a word for custom Stroka class: ";
    std::cin >> myStr; // Работает оператор >>
    std::cout << "You entered using std::cout << myStr: " << myStr << "\n\n"; // Работает оператор <<

    // --- Демонстрация Задания 3 ---
    std::cout << "--- Task 3: Stream-based XOR Cipher ---\n";
    
    std::ofstream createDummy("lab8_plain.txt");
    createDummy << "This text is encrypted using C++ fstreams!";
    createDummy.close();

    std::string key = "SECRET";
    
    encryptFileStreams("lab8_plain.txt", "lab8_cipher.bin", key);
    encryptFileStreams("lab8_cipher.bin", "lab8_decrypted.txt", key);
    
    std::cout << "Check 'lab8_decrypted.txt' to see the restored text.\n";

    // --- Демонстрация Задания 4 ---
    demonstrateStreamStates();

    return 0;
}