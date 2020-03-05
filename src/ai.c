#include <stdlib.h>
#include <limits.h>

#include "define.h"
#include "snake.h"
#include "apple.h"
#include "ai.h"

void ai_create_map(int **map)
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
void ai_propagate_wave(int **map, int x, int y)
{
    // Adiciona (x,y) em VISITAR
    // Enquanto VISITAR.size != 0:
    //      Retira (x,y) de VISITAR e o adiciona em VISITADOS
    //      Se (x+1,y) não existe em VISITADOS, aumente um valor dele e adicione-o em VISITAR
    //      Se (x-1,y) não existe em VISITADOS, aumente um valor dele e adicione-o em VISITAR
    //      Se (x,y+1) não existe em VISITADOS, aumente um valor dele e adicione-o em VISITAR
    //      Se (x,y-1) não existe em VISITADOS, aumente um valor dele e adicione-o em VISITAR
}

// Retorna o valor do wave map, ou -1 se o local for inacessivel:
int ai_get_wave_map_xy(int **wave_map, int x, int y)
{
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
        return -2;
    return wave_map[x][y];
}

// Verifica se uma direção é melhor do que a (atual) melhor
void ai_verify_location(int **wave_map, int x, int y, int *menor, SDL_Point *result)
{
    int val = ai_get_wave_map_xy(wave_map, x, y);
    if (val != -1 && val != 0 && val < (*menor))
    {
        (*menor) = val;
        result->x = x;
        result->y = y;
    }
}

SDL_Point ai_get_next_move(int **wave_map, int x, int y)
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