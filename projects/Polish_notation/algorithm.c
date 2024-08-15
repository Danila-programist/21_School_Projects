#include "algorithm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "output.h"
#include "stack.h"

void encryption(char *infix, char *postfix) {  // перевод в постфиксную польскую нотацию
    struct stack *box = NULL;                  // создаем структуру - стопку
    int j = 0;  // индекс для постфиксного выражения

    for (int i = 0; infix[i] != '\0'; i++) {  //проходим посимвольно по строке ввода (исходная функция)
        char ch = infix[i];

        if (ch ==
            ' ') {  // пропускаем проверку пробелов (для корректной работы функции если ввод был с пробелами)
            continue;  // пропускаем пробелы
        }

        if (checkSym(ch)) {  // проверяем символ на то что он является цифорой или буквой - если сивол цифра
                             // или буква то
            postfix[j++] = ch;   // добавляем ее в новую строку
        } else if (ch == '(') {  // еслси сивол является открытием скобки то
            box = push(box, ch);  // добавляем эту скобку в стэк
        } else if (ch == ')') {  // если символ является закрытием скобки то
            while (box != NULL &&
                   box->ch != '(') {  //если стэк не пустой и символы в стэке не является открытой скобкой то
                postfix[j++] = box->ch;  // достаем из стэка симолвы и добавляем в новую строку
                box = pop(box);
            }
            if (box != NULL) {
                box = pop(box);
            }     // далее убираем '(' из стека
        } else {  // если входной символ не является числом и не является скобками то
            while (box != NULL &&
                   priority(box->ch) >=
                       priority(ch)) {  // если стопка не пустая и если приоритет символа в стопке больше чем
                                        // приортиет входного символа то (например если в стопке лежит
                                        // произведение а на вход подается сумма)
                postfix[j++] = box->ch;  // то мы добавляем в строку символ со стэка
                box = pop(box);
            }
            box = push(
                box, ch);  // когда условиие while отрабатывает - добавляем в стопку символ с исходной строки
        }
    }

    while (box != NULL) {        // если стэк не пустой то
        postfix[j++] = box->ch;  // добавляем в новую строку символ со стэка
        box = pop(box);
    }

    postfix[j] = '\0';  // завершаем строку
}

int checkSym(char sym) {
    int rtn = 0;
    if ((sym >= 'A' && sym <= 'Z') || (sym >= 'a' && sym <= 'z') || (sym >= '0' && sym <= '9')) {
        rtn = 1;
    }
    return rtn;
}

int priority(char ch) {
    switch (ch) {
        case 'c':  // cos
        case 's':  // sin
        case 't':  // tan
        case 'g':  // log
        case 'q':  // sqrt
        case 'l':  // ln
            return 4;
        case '*':
        case '/':
            return 3;
        case '-':
        case '+':
            return 2;
        case '(':
            return 1;
    }
    return 0;
}

// Функция для выполнения операции
double operation(double num1, double num2, char op) {
    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 == 0) {
                fprintf(stderr, "Ошибка: деление на ноль\n");
            }
            return num1 / num2;
    }
    return 10000;
}

double decoding(char *postfix, double x) {
    Stack stack;
    initStack(&stack);

    int len = strlen(postfix);
    for (int i = 0; i < len; i++) {
        if (my_isdigit(postfix[i])) {
            // Если это число, считываем все символы числа
            double number = 0;
            while (i < len && my_isdigit(postfix[i])) {
                number = number * 10 + (postfix[i] - '0');
                i++;
            }
            i--;  // Корректируем индекс для следующей итерации
            push_d(&stack, number);
        } else if (postfix[i] == 'x') {
            // Замена 'x' на значение x
            push_d(&stack, x);
        } else if (strchr("+-*/", postfix[i])) {
            // Обработка оператора
            double num2 = pop_d(&stack);
            double num1 = pop_d(&stack);
            push_d(&stack, operation(num1, num2, postfix[i]));
        }
    }

    // Результат в верхней части стека
    return pop_d(&stack);
}

int my_isdigit(char ch) { return ch >= '0' && ch <= '9'; }
