#ifndef LIST_H
#define LIST_H

#include "door_struct.h"

struct node {
    struct door* door;
    struct node* next;
};

struct node* init(struct door* door);
struct node* add_door(struct node* elem, struct door* door);
struct node* find_door(int door_id, struct node* root);
struct node* remove_door(struct node* elem, struct node* root);
void destroy(struct node* root);
int test_add_door(struct door* d1, struct door* d2);
void output_list(struct node* head);
int len_of_linked_list(struct node* head);

#endif