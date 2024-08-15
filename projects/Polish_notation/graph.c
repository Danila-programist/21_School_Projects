/*
***== Получен Quest. На языке программирования Си разработать программу src/graph.c для построения графиков функций, задаваемых 
произвольными выражениями. Для вычисления значений выражений использовать алгоритм Дейкстры для перевода выражения в польскую нотацию. 
Сборку программы осуществлять при помощи Makefile. Имя стадии сборки - all. Исполняемый файл должен храниться в корне 
в папке build с именем graph. ==***
*/

#include <stdio.h>
#include <stdlib.h>

#include "algorithm.h"
#include "output.h"
#include "stack.h"

void input(char *infix);
void output_postfix(char *postfix);

int main() {
    char *infix = malloc(1000 * sizeof(char));
    char *postfix = malloc(1000 * sizeof(char));
    input(infix);
    encryption(infix, postfix);
    output_postfix(postfix);
    output(postfix);
    free(postfix);
    free(infix);
    return 0;
}

void input(char *infix) {
    printf("INFIX STRING: ");
    char ch;
    int i = 0;
    do {
        scanf("%c", &ch);
        infix[i] = ch;
        i++;
    } while (ch != '\n');
}

void output_postfix(char *postfix) {
    int i = 0;
    printf("POSTFIX STRING: ");
    while (postfix[i]) {
        printf("%c", postfix[i]);
        i++;
    }
}