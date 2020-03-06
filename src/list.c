#include <stdio.h>

#include "list.h"

void list_init(List *list, size_t element_size)
{
    list->element_size = element_size;
    list->size = 0;
    list->head = 0;
}

void list_free_nodes(Node *n, SDL_bool free_items)
{
    if (n == 0)
        return;
    list_free_nodes(n->next, free_items);
    n->next = 0;
    if (free_items)
        SDL_free(n->element);
    SDL_free(n);
}

void list_destroy(List *list, SDL_bool free_items)
{
    list->size = 0;
    list->element_size = 0;
    list_free_nodes(list->head, free_items);
    list->head = 0;
}

void list_clear(List *list, SDL_bool free_items)
{
    size_t el_size = list->element_size;
    list_destroy(list, free_items);
    list_init(list, el_size);
}

void list_add(List *list, void *element)
{
    Node *n = (Node *)SDL_malloc(sizeof(Node));
    n->next = 0;
    n->element = element;
    if (list->head == 0)
        list->head = n;
    else
    {
        Node *last = list->head;
        for (; last->next != 0; last = last->next)
            ;
        last->next = n;
    }
    list->size++;
}

void list_add_unique(List *list, void *element, SDL_bool (*cmpr)(void *a, void *b))
{
    Node *n = (Node *)SDL_malloc(sizeof(Node));
    n->next = 0;
    n->element = element;
    if (list->head == 0)
        list->head = n;
    else
    {
        Node *last = 0;
        for (last = list->head; last->next != 0; last = last->next)
            if ((*cmpr)(last->element, element))
                return;
        last->next = n;
    }
    list->size++;
}

void *list_pop(List *list, size_t i)
{
    if (list->size == 0 || i < 0 || i >= list->size)
        return 0;
    Node *tmp = list->head;
    if (i == 0)
        list->head = tmp->next;
    else
    {
        for (size_t e = 0; tmp->next != 0; tmp = tmp->next, e++)
        {
            if (e == (i - 1))
            {
                Node *n = tmp->next;
                tmp->next = tmp->next->next;
                tmp = n;
                break;
            }
        }
    }
    list->size--;
    return tmp->element;
}

void *list_get(List *list, size_t i)
{
    if (list->size == 0 || i < 0 || i >= list->size)
        return 0;
    Node *n = list->head;
    for (size_t e = 0; n != 0; n = n->next, e++)
        if (e == i)
            return n->element;
    return 0;
}

void list_purge(List *list, size_t i)
{
    if (list->size == 0 || i < 0 || i >= list->size)
        return;
    Node *tmp = list->head;
    if (i == 0)
        list->head = tmp->next;
    else
    {
        for (size_t e = 0; tmp->next != 0; tmp = tmp->next, e++)
        {
            if (e == (i - 1))
            {
                Node *n = tmp->next;
                tmp->next = tmp->next->next;
                tmp = n;
                break;
            }
        }
    }
    list->size--;
    SDL_free(tmp->element);
    SDL_free(tmp);
}

SDL_bool list_contains(List *list, void *element, SDL_bool (*cmpr)(void *a, void *b))
{
    if (list->size == 0 || element == 0)
        return SDL_FALSE;
    Node *n = list->head;
    for (size_t e = 0; n != 0; n = n->next, e++)
    {
        if ((*cmpr)(n->element, element))
            return SDL_TRUE;
    }
    return SDL_FALSE;
}

// Callbacks for list_contains function:
SDL_bool list_compare_points(void *a, void *b)
{
    SDL_Point *p1 = (SDL_Point *)a;
    SDL_Point *p2 = (SDL_Point *)b;
    return (p1->x == p2->x && p1->y == p2->y) ? SDL_TRUE : SDL_FALSE;
}

void list_print(List *list)
{
    Node *n = list->head;
    for (size_t i = 0; n != 0; n = n->next, i++)
    {
        printf("%zu\n", i);
        printf("node:       %p\n", n);
        printf("next node:  %p\n", n->next);
        printf("elmt addr:  %p\n", n->element);
        printf("\n");
    }
    printf("element size: %zu\n", list->element_size);
    printf("size: %zu\n", list->size);
}

void list_print_elements(List *list, void (*prnt)(void *e))
{
    Node *n = list->head;
    for (size_t i = 0; n != 0; n = n->next, i++)
    {
        printf("%zu\n", i);
        printf("node:       %p\n", n);
        printf("next node:  %p\n", n->next);
        printf("elmt addr:  %p\n", n->element);
        printf("content:\n");
        (*prnt)(n->element);
        printf("\n");
    }
    printf("element size: %zu\n", list->element_size);
    printf("size: %zu\n", list->size);
}

void list_print_point(void *e)
{
    SDL_Point *p = (SDL_Point *)e;
    printf("(%d, %d)\n", p->x, p->y);
}