#pragma once

#include "map.h"

struct human {
    int x;
    int y;
};

int human_move(struct sokoban_map *base_map, struct human *player, int move);