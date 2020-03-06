#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "define.h"
#include "list.h"
#include "snake.h"
#include "apple.h"
#include "ai.h"

void ai_create_map(int (*map)[MAP_HEIGHT])
{
    // Zera o mapa:
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < MAP_WIDTH; x++)
            map[x][y] = 0;

    // Preenche a partir dos objetos:
    SnakePart *p = snake.head;
    while (p != 0)
    {
        map[p->point.x][p->point.y] = -1;
        p = p->next;
    }
    map[apple.pos.x][apple.pos.y] = 1;
}

// Propaga uma onda a partir de (x,y)
void ai_propagate_wave(int (*map)[MAP_HEIGHT], SDL_Point *p)
{
    List VISITAR, VISITADOS;
    list_init(&VISITAR, sizeof(SDL_Point *));
    list_init(&VISITADOS, sizeof(SDL_Point *));

    list_add(&VISITAR, p);
    while (VISITAR.size != 0)
    {
        SDL_Point *tmp = (SDL_Point *)list_pop(&VISITAR, 0);
        list_add(&VISITADOS, tmp);

        // Direita
        SDL_Point *right = (SDL_Point *)SDL_malloc(sizeof(SDL_Point *));
        right->x = tmp->x + 1;
        right->y = tmp->y;
        // Se pode visitar:
        if (right->x >= 0 && right->y >= 0 && right->x < MAP_WIDTH && right->y < MAP_HEIGHT && map[right->x][right->y] != -1)
        {
            // Se n existe em VISITADOS:
            if (!list_contains(&VISITADOS, right, compare_points))
            {
                map[right->x][right->y] = map[tmp->x][tmp->y] + 1;
                list_add(&VISITAR, right);
            }
            else
                SDL_free(right);
        }
        else
            SDL_free(right);

        // Esquerda
        SDL_Point *left = (SDL_Point *)SDL_malloc(sizeof(SDL_Point *));
        left->x = tmp->x - 1;
        left->y = tmp->y;
        // Se pode visitar:
        if (left->x >= 0 && left->y >= 0 && left->x < MAP_WIDTH && left->y < MAP_HEIGHT && map[left->x][left->y] != -1)
        {
            // Se n existe em VISITADOS:
            if (!list_contains(&VISITADOS, left, compare_points))
            {
                map[left->x][left->y] = map[tmp->x][tmp->y] + 1;
                list_add(&VISITAR, left);
            }
            else
                SDL_free(left);
        }
        else
            SDL_free(left);

        // Cima
        SDL_Point *up = (SDL_Point *)SDL_malloc(sizeof(SDL_Point *));
        up->x = tmp->x;
        up->y = tmp->y - 1;
        // Se pode visitar:
        if (up->x >= 0 && up->y >= 0 && up->x < MAP_WIDTH && up->y < MAP_HEIGHT && map[up->x][up->y] != -1)
        {
            // Se n existe em VISITADOS:
            if (!list_contains(&VISITADOS, up, compare_points))
            {
                map[up->x][up->y] = map[tmp->x][tmp->y] + 1;
                list_add(&VISITAR, up);
            }
            else
                SDL_free(up);
        }
        else
            SDL_free(up);

        // Baixo
        SDL_Point *down = (SDL_Point *)SDL_malloc(sizeof(SDL_Point *));
        down->x = tmp->x;
        down->y = tmp->y + 1;
        // Se pode visitar:
        if (down->x >= 0 && down->y >= 0 && down->x < MAP_WIDTH && down->y < MAP_HEIGHT && map[down->x][down->y] != -1)
        {
            // Se n existe em VISITADOS:
            if (!list_contains(&VISITADOS, down, compare_points))
            {
                map[down->x][down->y] = map[tmp->x][tmp->y] + 1;
                list_add(&VISITAR, down);
            }
            else
                SDL_free(down);
        }
        else
            SDL_free(down);
    }

    printf("apple: %d %d\n", apple.pos.x, apple.pos.y);
    printf("snake: %d %d\n\n", snake.head->point.x, snake.head->point.y);
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            printf("%4d ", map[x][y]);
        }
        printf("\n");
    }

    list_destroy(&VISITADOS, 1);
    list_destroy(&VISITAR, 1);
    exit(1);
}

// Retorna o valor do wave map, ou -1 se o local for inacessivel:
int ai_get_wave_map_xy(int (*wave_map)[MAP_HEIGHT], int x, int y)
{
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
        return -2;
    return wave_map[x][y];
}

// Verifica se uma direção é melhor do que a (atual) melhor
void ai_verify_location(int (*wave_map)[MAP_HEIGHT], int x, int y, int *menor, SDL_Point *result)
{
    int val = ai_get_wave_map_xy(wave_map, x, y);
    if (val != -1 && val != 0 && val < (*menor))
    {
        (*menor) = val;
        result->x = x;
        result->y = y;
    }
}

SDL_Point ai_get_next_move(int (*wave_map)[MAP_HEIGHT], int x, int y)
{
    SDL_Point result = {-1, -1};
    SDL_Point *p = &snake.head->point;
    int menor = INT_MAX;

    // Verifica a melhor das 4 direções:
    ai_verify_location(wave_map, p->x - 1, p->y, &menor, &result);
    ai_verify_location(wave_map, p->x - 1, p->y, &menor, &result);
    ai_verify_location(wave_map, p->x - 1, p->y, &menor, &result);
    ai_verify_location(wave_map, p->x - 1, p->y, &menor, &result);

    // Se não encontrar nenhum caminho:
    if (result.x == -1)
    {
        /*  */
    }

    return result;
}