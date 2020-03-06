#include <limits.h>
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
    List nodes;
    list_init(&nodes, sizeof(SDL_Point));

    // Adiciona o primeiro no-descoberto (pos. da apple)
    SDL_Point *p = (SDL_Point *)SDL_malloc(sizeof(SDL_Point));
    SDL_memcpy(p, &apple.pos, sizeof(SDL_Point));
    list_add(&nodes, p);

    while (nodes.size != 0)
    {
        List new_nodes;
        list_init(&new_nodes, sizeof(SDL_Point));

        for (int i = 0; i < nodes.size; i++)
        {
            SDL_Point *el = (SDL_Point *)list_get(&nodes, i);
            int x = el->x;
            int y = el->y;
            int d = map[x][y];

            // Check East
            if ((x + 1) < MAP_WIDTH && map[x + 1][y] == 0)
            {
                SDL_Point *p = (SDL_Point *)SDL_malloc(sizeof(SDL_Point));
                p->x = x + 1;
                p->y = y;
                list_add_unique(&new_nodes, p, list_compare_points);
                map[p->x][p->y] = d + 1;
            }

            // Check West
            if ((x - 1) >= 0 && map[x - 1][y] == 0)
            {
                SDL_Point *p = (SDL_Point *)SDL_malloc(sizeof(SDL_Point));
                p->x = x - 1;
                p->y = y;
                list_add_unique(&new_nodes, p, list_compare_points);
                map[p->x][p->y] = d + 1;
            }

            // Check South
            if ((y + 1) < MAP_HEIGHT && map[x][y + 1] == 0)
            {
                SDL_Point *p = (SDL_Point *)SDL_malloc(sizeof(SDL_Point));
                p->x = x;
                p->y = y + 1;
                list_add_unique(&new_nodes, p, list_compare_points);
                map[p->x][p->y] = d + 1;
            }

            // Check North
            if ((y - 1) >= 0 && map[x][y - 1] == 0)
            {
                SDL_Point *p = (SDL_Point *)SDL_malloc(sizeof(SDL_Point));
                p->x = x;
                p->y = y - 1;
                list_add_unique(&new_nodes, p, list_compare_points);
                map[p->x][p->y] = d + 1;
            }
        }

        list_clear(&nodes, SDL_FALSE);
        for (int i = 0; i < new_nodes.size; i++)
            list_add(&nodes, list_get(&new_nodes, i));

        list_destroy(&new_nodes, SDL_FALSE);
    }

    list_destroy(&nodes, SDL_TRUE);
}

void wm_pick_path(int (*map)[MAP_HEIGHT], Snake *snake)
{
    int x = snake->head->point.x;
    int y = snake->head->point.y;
    SDL_Point result = {-1, -1};

    int menor = INT_MAX;
    if ((x - 1) >= 0 && map[x - 1][y] != -1 && map[x - 1][y] < menor)
    {
        menor = map[x - 1][y];
        result.x = x - 1;
        result.y = y;
    }
    if ((x + 1) < MAP_WIDTH && map[x + 1][y] != -1 && map[x + 1][y] < menor)
    {
        menor = map[x + 1][y];
        result.x = x + 1;
        result.y = y;
    }
    if ((y - 1) >= 0 && map[x][y - 1] != -1 && map[x][y - 1] < menor)
    {
        menor = map[x][y - 1];
        result.x = x;
        result.y = y - 1;
    }

    if ((y + 1) < MAP_HEIGHT && map[x][y + 1] != -1 && map[x][y + 1] < menor)
    {
        menor = map[x][y + 1];
        result.x = x;
        result.y = y + 1;
    }

    if (result.x != -1 && result.y != -1)
    {
        SDL_Point dir = {result.x - snake->head->point.x, result.y - snake->head->point.y};
        snake_set_direction(dir.x, dir.y);
    }
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
    printf("\n.\n");
}