#include "SDL2/SDL.h"
#include "list.h"

void list_init(List *list, size_t node_size)
{
    list->node_size = node_size;
    list->head = 0;
}

void list_add(List *list, void *element)
{

}

void list_get(List *list, size_t pos)
{
}

void *list_pop(List *list, size_t pos)
{
}

void list_destroy(List *list)
{
}