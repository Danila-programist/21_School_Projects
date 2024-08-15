/*
***== Получен Quest 2. Разработать программу src/list.c, в которой содержатся реализации функций по работе 
с односвязным списком дверей (`struct node* init(struct door* door)` - инициализация структуры односвязного списка на базе переданной `struct door`, `struct node* add_door(struct node* elem, struct door* door)` - вставка нового элемента `struct door` в односвязный список после переданного узла `elem`, `struct node* find_door(int door_id, struct node* root)` - поиск двери в списке по её id, `struct node* remove_door(struct node* elem, struct node* root)` - удаление элемента списка, `void destroy(struct node* root)` - освобождение памяти, занимаемой структурой списка). Объявления этих функций и структуру односвязного списка вынести в файл src/list.h. Написать модульные тесты для проверки работы функций add_door 
и remove_door односвязного списка в src/list_test.c. Функции методов должны возвращать SUCCESS в случае успешного прохождения 
теста и FAIL - в случае ошибки. Тесты должны собираться при помощи Makefile. Имя стадии - list_test. 
Исполняемый файл должен располагаться в корне репозитория в папке build и иметь имя Quest_2 
Обратите внимание: этот квест будет тестироваться утилитой `cppcheck`==***
*/

#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#include "door_struct.h"

#define SUCCESS 1
#define FAIL 0

int test_add_door(struct door *d1, struct door *d2);
int test_remove_door(struct node *elem, struct node *root);

int main() {
    printf("TEST ADD FUNCTION\n");
    struct door *d1 = (struct door *)malloc(sizeof(struct door));
    struct door *d2 = (struct door *)malloc(sizeof(struct door));

    d1->id = 1;
    d1->status = 0;
    d2->id = 2;
    d2->status = 1;

    (test_add_door(d1, d2)) ? printf("SUCCESS\n") : printf("FAIL\n");

    struct door *d1_ = (struct door *)malloc(sizeof(struct door));
    d1_->id = 1;
    d1_->status = 0;

    struct door *d2_ = (struct door *)malloc(sizeof(struct door));
    d2_->id = 2;
    d2_->status = 1;

    (test_add_door(d1_, d2_)) ? printf("SUCCESS\n") : printf("FAIL\n");

    struct door *_d1 = NULL;
    struct door *_d2 = (struct door *)malloc(sizeof(struct door));
    _d2->id = 1;
    _d2->status = 1;
    (test_add_door(_d1, _d2)) ? printf("SUCCESS\n") : printf("FAIL\n");

    printf("\nTEST REMOVE FUNCTION\n");

    struct door *dd1 = (struct door *)malloc(sizeof(struct door));
    dd1->id = 1;
    dd1->status = 1;
    struct door *dd2 = (struct door *)malloc(sizeof(struct door));
    dd2->id = 2;
    dd2->status = 2;
    struct node *node_1 = init(dd1);
    struct node *door_1 = node_1;
    add_door(node_1, dd2);
    (test_remove_door(door_1, node_1)) ? printf("SUCCESS\n") : printf("FAIL\n");

    struct door *dd1_ = (struct door *)malloc(sizeof(struct door));
    dd1_->id = 1;
    dd1_->status = 1;
    struct door *dd2_ = (struct door *)malloc(sizeof(struct door));
    dd2_->id = 2;
    dd2_->status = 2;
    struct door *dd3_ = (struct door *)malloc(sizeof(struct door));
    dd3_->id = 3;
    dd3_->status = 3;
    struct node *node_1_ = init(dd1_);
    add_door(node_1_, dd2_);
    add_door(node_1_->next, dd3_);
    struct node *door_2_ = node_1_->next;
    (test_remove_door(door_2_, node_1_)) ? printf("SUCCESS\n") : printf("FAIL\n");

    struct door *_dd1 = (struct door *)malloc(sizeof(struct door));
    _dd1->id = 1;
    _dd1->status = 1;
    struct door *_dd2 = (struct door *)malloc(sizeof(struct door));
    _dd2->id = 2;
    _dd2->status = 2;
    struct door *_dd3 = (struct door *)malloc(sizeof(struct door));
    _dd3->id = 3;
    _dd3->status = 3;
    struct door *_dd4 = (struct door *)malloc(sizeof(struct door));
    _dd4->id = 4;
    _dd4->status = 4;
    struct node *_node_1 = init(_dd1);
    add_door(_node_1, _dd2);
    add_door(_node_1->next, _dd3);
    add_door(_node_1->next->next, _dd4);
    struct node *_door_2 = _node_1->next;
    (test_remove_door(_door_2, _node_1)) ? printf("SUCCESS\n") : printf("FAIL\n");

    return 0;
}

int test_add_door(struct door *d1, struct door *d2) {
    if (d1 == NULL) {
        printf("first door: NULL; ");
    } else {
        printf("first door: door_id - %d, door_status - %d; ", d1->id, d1->status);
    }
    if (d2 == NULL) {
        printf("second door: NULL\n");
    } else {
        printf("second door: door_id - %d, door_status - %d\n", d2->id, d2->status);
    }
    struct node *list = init(d1);
    if (add_door(list, d2) == NULL) {
        printf("result of function: NULL\n");
    } else {
        printf("result of function: door_id - %d, door_status - %d\n", d2->id, d2->status);
    }
    int flag = 0;
    struct node *fnd = find_door(d2->id, list);
    if (fnd && (fnd->door->id == d2->id)) {
        flag = SUCCESS;
    }
    destroy(list);
    return (flag == 1) ? SUCCESS : FAIL;
}

int test_remove_door(struct node *elem, struct node *root) {
    printf("Node: \n");
    output_list(root);
    printf("Elem: \n");
    int first_cnt = len_of_linked_list(root);
    printf("door_id - %d, door_status - %d\n", elem->door->id, elem->door->status);
    struct node *head = remove_door(elem, root);
    int second_cnt = len_of_linked_list(head);
    printf("result of function:\n");
    output_list(head);
    if (first_cnt - second_cnt == 1) {
        destroy(head);
        return SUCCESS;
    }
    destroy(head);
    return FAIL;
}