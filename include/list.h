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
    size_t element_size;
    size_t size;

} List;

void list_init(List *list, size_t element_size);
void list_destroy(List *list, SDL_bool free_items);
void free_nodes(Node *n, SDL_bool free_items);

void list_add(List *list, void *element);
void *list_pop(List *list, size_t i);
void *list_get(List *list, size_t i);

SDL_bool list_contains(List *list, void *element, SDL_bool (*cmpr)(void *a, void *b));

// Callbacks para list_contains function:
SDL_bool compare_points(void *a, void *b);

// Utilitarios
void list_print(List *list);
void list_print_elements(List *list, void (*prnt)(void *e));

// Callbacks para list_print_elements:
void print_point(void *e);

#endif