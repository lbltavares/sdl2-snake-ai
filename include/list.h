#ifndef LIST_H
#define LIST_H

#include "SDL2/SDL.h"

typedef struct _Node
{
    void *element;
    struct _Node *next;
} Node;

typedef struct _List
{
    Node *head;
    size_t size;
    size_t node_size;
} List;

void list_init(List *list, size_t node_size);
void list_add(List *list, void *element);
void list_get(List *list, size_t pos);
void *list_pop(List *list, size_t pos);
void list_destroy(List *list);

#endif