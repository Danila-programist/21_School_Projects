#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

struct stack* push(struct stack* top, char ch) {
    struct stack* ptr = malloc(sizeof(struct stack));
    ptr->ch = ch;
    ptr->next = top;
    return ptr;
}

struct stack* pop(struct stack* top) {
    if (top == NULL) {
        return top;
    }
    struct stack* ptr_next = top->next;
    free(top);
    return ptr_next;
}
// Функция для инициализации стека
void initStack(Stack* s) { s->top = -1; }

// Функция для проверки, пуст ли стек
int isEmpty(Stack* s) { return s->top == -1; }

// Функция для добавления элемента в стек
void push_d(Stack* s, double value) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->items[++(s->top)] = value;
    } else {
        fprintf(stderr, "Ошибка: стек переполнен\n");
        exit(EXIT_FAILURE);
    }
}

// Функция для извлечения элемента из стека
double pop_d(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    } else {
        fprintf(stderr, "Ошибка: стек пуст\n");
        exit(EXIT_FAILURE);
    }
}
