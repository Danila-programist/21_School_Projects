#ifndef STACK_H
#define STACK_H
#define MAX_STACK_SIZE 100

struct stack {
    char ch;
    struct stack* next;
};

typedef struct {
    double items[MAX_STACK_SIZE];
    int top;
} Stack;

struct stack* push(struct stack* top, char ch);
struct stack* pop(struct stack* top);
void initStack(Stack* s);
int isEmpty(Stack* s);
void push_d(Stack* s, double value);
double pop_d(Stack* s);

#endif
