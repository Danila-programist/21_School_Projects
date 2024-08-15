#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct node* init(struct door* door) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        fprintf(stderr, "FAIL\n");
        return NULL;
    }
    newNode->door = door;
    newNode->next = NULL;
    return newNode;
}

struct node* add_door(struct node* elem, struct door* door) {
    if (elem == NULL) {
        return init(door);
    }
    struct node* newNode = init(door);
    if (newNode == NULL) {
        return NULL;
    }
    newNode->next = elem->next;
    elem->next = newNode;
    return newNode;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* current = root;
    while (current != NULL) {
        if (current->door != NULL && current->door->id == door_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct node* remove_door(struct node* elem, struct node* root) {
    if (root == NULL || elem == NULL) {
        return root;
    }
    if (root == elem) {
        struct node* next = root->next;
        free(root->door);
        free(root);
        return next;
    }
    struct node* current = root;
    while (current->next != NULL && current->next != elem) {
        current = current->next;
    }

    if (current->next == elem) {
        struct node* to_remove = current->next;
        current->next = current->next->next;
        free(to_remove->door);
        free(to_remove);
    }

    return root;
}

void destroy(struct node* root) {
    struct node* current = root;
    struct node* next;

    while (current != NULL) {
        next = current->next;
        if (current->door != NULL) {
            free(current->door);
        }
        free(current);
        current = next;
    }
}

void output_list(struct node* head) {
    struct node* current = head;
    int count = 1;
    while (current != NULL) {
        printf("Number %d: door_id - %d, door_status - %d\n", count++, current->door->id,
               current->door->status);
        current = current->next;
    }
}

int len_of_linked_list(struct node* head) {
    int cnt = 0;
    struct node* current = head;
    while (current) {
        cnt++;
        current = current->next;
    }
    return cnt;
}