#include <stdio.h>

// Макрос с корректным форматированием и подстановкой имени переменной
#define PR(var) printf(#var "=%p, *" #var "=%d, &" #var "=%p\n", \
                      (void*)(var), *(var), (void*)&(var))


int main(void) {
    int mas[] = {100, 200, 300};
    int *ptr1, *ptr2;
    
    ptr1 = mas;
    ptr2 = &mas[2];
    
    PR(ptr1);
    ptr1++;
    PR(ptr1);
    PR(ptr2);
    ++ptr2;

    // Для разности указателей используется тип long int
    printf("ptr2-ptr1=%li\n", ptr2 - ptr1);
    
    return 0;
}

