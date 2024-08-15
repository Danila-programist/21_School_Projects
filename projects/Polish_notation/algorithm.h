#ifndef ALGORITHM_H
#define ALGORITHM_H
void encryption(char *infix, char *postfix);
int checkSym(char sym);
int priority(char symbol);
double operation(double num1, double num2, char op);
double decoding(char *postfix, double x);
int my_isdigit(char ch);
#endif