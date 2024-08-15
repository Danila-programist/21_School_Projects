/*
***== Получен Quest 3. Разработать программу src/stack.c, в которой содержатся реализации функций по работе 
с динамическим стеком (init, push, pop, destroy). Объявления функций и структуры динамического стека, 
хранящего целые числа, вынести в src/stack.h. Написать модульные тесты для проверки работы функций push 
и pop стека в src/stack_test.c. Функции методов должны возвращать SUCCESS в случае успешного прохождения 
теста и FAIL - в случае ошибки. Тесты должны собираться при помощи Makefile. Имя стадии - stack_test. 
Исполняемый файл должен располагаться в корне репозитория в папке build и иметь имя Quest_3. 
Обратите внимание: этот квест будет тестироваться утилитой `cppcheck` ==***
*/ 

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

struct stack *push(struct stack *top, int data) {
    struct stack *ptr = malloc(sizeof(struct stack));
    ptr->data = data;
    ptr->next = top;
    return ptr;
}

struct stack *pop(struct stack *top) {
    if (top == NULL) {
        return NULL;
    }
    struct stack *ptr_next = top->next;
    free(top);
    return ptr_next;
}

void show(struct stack *top) {
    struct stack *current = top;
    while (current != NULL) {
        printf("%d - ", current->data);
        current = current->next;
    }
    printf("SUCCESS");
}

void destroy(struct stack **top) {
    while ((*top)->next) {
        printf("1 ");
        struct stack *prev = *top;
        *top = (*top)->next;
        free(prev);
    }
    free(*top);
    *top = NULL;
}

struct stack *init(struct stack *top) {
    if (top == NULL) {
        return NULL;
    }
    struct stack *init_stack = (struct stack *)malloc(sizeof(struct stack));
    return init_stack;
}