// Лабораторная работа №5

// Цель работы: 
// организация ввода-вывода; освоение навыков работы с файлами средствами библиотеки функций ввода-вывода; 
// использование аргументов функции main.

// Состав работы:
//	1. Разбор и оптимизация примера программы, выводящей содержимое текстового файла на экран.
//	2. Добавление функции подсчета «пустых» (управляющих, пробельных) и «непустых» символов в файле.
//	3. Реализация функции поиска заданной подстроки с сохранением результатов в отдельный файл.
//	4. Обработка текстового файла: перенос номеров страниц из первой строки в последнюю с удалением дефисов 
//     (учет символа перехода страницы '\f').
//	5. Написание программы-шифратора файлов с помощью циклического применения операции XOR по заданному ключу.
//	6. Дополнение шифратора возможностью получать имена файлов и ключ из аргументов командной строки (argc, argv).

#include <iostream>
#include <cstdio>   // Для FILE, fopen, fgets, fgetc, fputc (согласно тематике ЛР)
#include <cstring>  // Для strstr, strchr
#include <cctype>   // Для isspace, iscntrl, isdigit

// Вспомогательная функция: создает тестовый файл, чтобы программу можно было сразу запустить и проверить
void createDummyFile(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (f) {
        fprintf(f, "- 34 -\n"); // Номер первой страницы
        fprintf(f, "Hello! This is a test file for Lab 5.\n");
        fprintf(f, "We will search for the word 'test' here.\f"); // '\f' - символ разрыва страницы
        fprintf(f, "- 35 -\n"); // Номер второй страницы
        fprintf(f, "Second page begins.\n");
        fprintf(f, "End of dummy file.\n");
        fclose(f);
    }
}

// --- ЗАДАНИЕ 1 и 2: Оптимизированный вывод файла и подсчет символов ---
/* * ОТВЕТ НА ВОПРОС ИЗ ПУНКТА 1 ("Как можно сократить текст программы?"):
 * 1. Вместо конструкции while(!feof(in)) { ch=getc(in); putchar(ch); } используется 
 * оптимизированная запись while ((ch = fgetc(in)) != EOF). Это безопаснее и короче.
 * 2. Переменная ch объявлена как int, а не char, так как константа EOF равна -1 и 
 * может некорректно обрабатываться в типе char.
 */
void task1_2(const char* filename) {
    FILE* in = fopen(filename, "r");
    if (!in) return;

    int ch; // Переменная для хранения текущего считанного символа (тип int для EOF)
    int emptyCount = 0;    // Счетчик "пустых" символов
    int nonEmptyCount = 0; // Счетчик "непустых" символов

    std::cout << "\n[INFO] Using variable 'ch' (int) to safely read characters and check for EOF.\n";
    std::cout << "--- File Content (" << filename << ") ---\n";
    
    // Считываем до конца файла
    while ((ch = fgetc(in)) != EOF) {
        putchar(ch);
        
        // Задание 2: Подсчет пустых и непустых символов
        if (std::isspace(ch) || std::iscntrl(ch)) {
            emptyCount++;
        } else {
            nonEmptyCount++;
        }
    }
    
    std::cout << "\n----------------------------------\n";
    std::cout << "[INFO] Variable 'emptyCount' = " << emptyCount << " (tracks spaces, newlines, control chars).\n";
    std::cout << "[INFO] Variable 'nonEmptyCount' = " << nonEmptyCount << " (tracks visible text chars).\n";
    
    fclose(in);
}

// --- ЗАДАНИЕ 3: Поиск подстроки и запись результата в файл ---
void task3(const char* inFilename, const char* outFilename, const char* searchStr) {
    FILE* in = fopen(inFilename, "r");
    FILE* out = fopen(outFilename, "w");
    if (!in || !out) return;

    char line[512]; // Буфер для чтения строки
    int lineNum = 1; // Счетчик номеров строк
    int matchCount = 0; // Счетчик совпадений

    std::cout << "\n[INFO] Using variable 'searchStr' = '" << searchStr << "' to find matches.\n";

    fprintf(out, "Search results for: '%s'\n", searchStr);
    
    // Читаем файл построчно
    while (fgets(line, sizeof(line), in)) {
        if (strstr(line, searchStr)) { // Если подстрока найдена в строке
            fprintf(out, "Line %d: %s", lineNum, line);
            matchCount++;
        }
        lineNum++;
    }
    
    fprintf(out, "\nTotal matches found: %d\n", matchCount);
    std::cout << "[INFO] Variable 'matchCount' = " << matchCount << ". Results saved to '" << outFilename << "'.\n";

    fclose(in);
    fclose(out);
}

// --- ЗАДАНИЕ 4: Перенос номеров страниц ---
void task4(const char* inFile, const char* outFile) {
    FILE* in = fopen(inFile, "r");
    FILE* out = fopen(outFile, "w");
    if (!in || !out) return;

    char buffer[1024]; // Буфер строки
    bool firstLine = true; // Флаг: находимся ли мы на первой строке страницы
    int pageNum = -1; // Переменная для сохранения извлеченного номера страницы

    std::cout << "\n[INFO] Processing pages. Variable 'pageNum' temporarily holds the page number until '\\f' is reached.\n";

    while (fgets(buffer, sizeof(buffer), in)) {
        if (firstLine) {
            // Извлекаем цифры из первой строки
            pageNum = -1;
            for (int i = 0; buffer[i]; ++i) {
                if (std::isdigit(buffer[i])) {
                    sscanf(&buffer[i], "%d", &pageNum);
                    break;
                }
            }
            firstLine = false;
            continue; // Пропускаем печать этой строки (номер ушел в память)
        }

        // Ищем управляющий символ перехода страницы '\f'
        char* ffPos = strchr(buffer, '\f');
        if (ffPos) {
            *ffPos = '\0'; // Обрезаем строку до '\f'
            fprintf(out, "%s", buffer); // Печатаем текст
            
            if (pageNum != -1) {
                fprintf(out, "%d\n", pageNum); // Печатаем номер страницы ВНИЗУ
            }
            fprintf(out, "\f\n"); // Возвращаем разрыв страницы
            firstLine = true; // Следующая строка будет первой на новой странице
        } else {
            fprintf(out, "%s", buffer); // Обычная печать строки
        }
    }
    
    // Если файл кончился, но мы всё ещё на странице, печатаем номер в самом конце
    if (!firstLine && pageNum != -1) {
        fprintf(out, "%d\n", pageNum);
    }

    std::cout << "[INFO] Page numbers moved successfully to '" << outFile << "'.\n";

    fclose(in);
    fclose(out);
}

// --- ЗАДАНИЕ 5 и 6: Шифратор XOR ---
// Функция читает файл байт за байтом и применяет XOR с ключом. 
// Повторное применение к зашифрованному файлу восстановит исходник.
void task5_6_encryptor(const char* inFile, const char* outFile, const char* key) {
    FILE* in = fopen(inFile, "rb");  // Режим 'rb' - бинарное чтение для безопасной работы с искаженными шифром символами
    FILE* out = fopen(outFile, "wb"); // Режим 'wb' - бинарная запись
    if (!in || !out) return;

    size_t keyLen = strlen(key);
    if (keyLen == 0) return;

    size_t i = 0; // Индекс символа в ключе
    int ch;       // Считанный байт
    
    while ((ch = fgetc(in)) != EOF) {
        // Применяем XOR: с ^ key[i]
        int encryptedChar = ch ^ key[i % keyLen]; 
        fputc(encryptedChar, out);
        i++;
    }

    fclose(in);
    fclose(out);
}

// --- ГЛАВНАЯ ФУНКЦИЯ: Работа с аргументами командной строки (argc, argv) ---
int main(int argc, char* argv[]) {
    
    std::cout << "--- Command Line Arguments Check ---\n";
    std::cout << "[INFO] Variable 'argc' = " << argc << ". It tracks the number of arguments passed.\n";
    std::cout << "[INFO] Variable 'argv' holds the argument strings.\n";

    // Задание 6: Если передано достаточно аргументов, запускаем режим шифратора из консоли
    // Ожидается формат: ./program input.txt output.bin secretkey
    if (argc >= 4) {
        const char* inFile = argv[1];
        const char* outFile = argv[2];
        const char* key = argv[3];
        
        std::cout << "\n--- Task 6: CLI File Encryptor Mode ---\n";
        std::cout << "[INFO] Variable 'inFile' = " << inFile << "\n";
        std::cout << "[INFO] Variable 'outFile' = " << outFile << "\n";
        std::cout << "[INFO] Variable 'key' = " << key << "\n";
        
        task5_6_encryptor(inFile, outFile, key);
        std::cout << "Encryption/Decryption complete!\n";
        return 0; // Завершаем программу
    }

    // Если аргументов нет, демонстрируем работу всех заданий (1-5) автоматически
    std::cout << "\n[INFO] No CLI arguments provided. Running automatic demo for Tasks 1-5...\n";
    
    const char* dummyFile = "lab5_test_input.txt";
    createDummyFile(dummyFile); // Создаем файл для тестов
    
    // Демонстрация заданий 1 и 2
    task1_2(dummyFile);
    
    // Демонстрация задания 3
    const char* searchOut = "lab5_task3_out.txt";
    task3(dummyFile, searchOut, "test");
    
    // Демонстрация задания 4
    const char* pagedOut = "lab5_task4_out.txt";
    task4(dummyFile, pagedOut);
    
    // Демонстрация задания 5
    const char* encryptedFile = "lab5_encrypted.bin";
    const char* decryptedFile = "lab5_decrypted.txt";
    const char* secretKey = "XOR_KEY";
    
    std::cout << "\n--- Task 5: XOR Cipher Demonstration ---\n";
    std::cout << "[INFO] Key used for Task 5: '" << secretKey << "'\n";
    
    task5_6_encryptor(dummyFile, encryptedFile, secretKey);
    std::cout << "[INFO] File encrypted to '" << encryptedFile << "'.\n";
    
    task5_6_encryptor(encryptedFile, decryptedFile, secretKey); // Расшифровка (двойной XOR возвращает оригинал)
    std::cout << "[INFO] File decrypted back to '" << decryptedFile << "'.\n";
    
    std::cout << "\n[HINT] To test Task 6, run this program from terminal:\n";
    std::cout << "Usage: ./your_program_name <input_file> <output_file> <secret_key>\n";

    return 0;
}