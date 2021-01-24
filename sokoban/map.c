#include <stdlib.h>
#include "map.h"

#include "mm.h"

void init_map(struct sokoban_map *sm)
{
    if (heap_init())
        return;
        
    if (!sm->map) {
        sm->map = (int **)my_malloc(sizeof(*sm->map) * sm->length);

        for (int i = 0; i < sm->length; i++)
            sm->map[i] = (int *)my_malloc(sizeof(*sm->map[i]) * sm->width);
    }

    for (int x = 0; x < sm->length; x++) {
        for (int y = 0; y < sm->width; y++) {
            if (x == 0 || y == 0 || x == sm->length - 1 || y == sm->width - 1) {
                sm->map[x][y] = 1;
                continue;
            }
            sm->map[x][y] = 0;
            
        }
    } //
}

void free_map(struct sokoban_map *sm) 
{
    for (int i = 0; i < sm->length; i++)
        my_free(sm->map[i]);

    my_free(sm->map);
}
