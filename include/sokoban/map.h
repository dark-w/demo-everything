#pragma once

struct sokoban_map {
    const int length;
    const int width;
    int **map;
};

void init_map(struct sokoban_map *sm);
void free_map(struct sokoban_map *sm);