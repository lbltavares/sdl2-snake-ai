#include <stdio.h>
#include <stdlib.h>

#include "define.h"
#include "wavemap.h"
#include "list.h"

#include "apple.h"
#include "snake.h"

// Cria o estado inicial do mapa:
void wm_prepare_map(int (*map)[MAP_HEIGHT])
{
    // Zera o mapa:
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < MAP_WIDTH; x++)
            map[x][y] = 0;

    // Preenche o mapa a partir da posicao dos objetos:
    SnakePart *p = snake.head;
    while (p != 0)
    {
        map[p->point.x][p->point.y] = SOLID;
        p = p->next;
    }
    map[apple.pos.x][apple.pos.y] = SOURCE;
}

static void wm_add_point_to_set(int x, int y, int (*map)[MAP_HEIGHT], List *list)
{
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
    {
        SDL_Point *p = (SDL_Point *)SDL_malloc(sizeof(SDL_Point));
        p->x = x;
        p->y = y;
        list_add_unique(list, p, list_compare_points);
    }
}

// Propaga a wave atraves do mapa:
void wm_propagate(int (*map)[MAP_HEIGHT])
{
    List A, B;
    list_init(&A, sizeof(SDL_Point));
    list_init(&B, sizeof(SDL_Point));
    SDL_Point *src = (SDL_Point *)SDL_malloc(sizeof(SDL_Point));
    SDL_memcpy(src, &apple.pos, sizeof(SDL_Point));
    list_add(&A, src);

    /*
     * FAZER O ALGORITMO DE PROPAGAÇÃO AQUI
     */
    list_print_elements(&A, list_print_point);

    SDL_free(src);
    list_destroy(&A, SDL_TRUE);
    list_destroy(&B, SDL_TRUE);
}

void wm_print_map(int (*map)[MAP_HEIGHT])
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            printf("%2d ", map[x][y]);
        }
        printf("\n");
    }
    printf("\n\n");
}