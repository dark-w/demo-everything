#include "human.h"

int human_move(struct sokoban_map *base_map, struct human *player, int move)
{
    switch (move) {
    case 'w':
    case 'W':
        if (base_map->map[player->x - 1][player->y] != 1) {
            base_map->map[player->x][player->y] = 0;
            player->x--;
        }
        break;

    case 's':
    case 'S':
        if (base_map->map[player->x + 1][player->y] != 1) {
            base_map->map[player->x][player->y] = 0;
            player->x++;
        }
        break;

    case 'a':
    case 'A':
        if (base_map->map[player->x][player->y - 1] != 1) {
            base_map->map[player->x][player->y] = 0;
            player->y--;
        }
        break;

    case 'd':
    case 'D':
        if (base_map->map[player->x][player->y + 1] != 1) {
            base_map->map[player->x][player->y] = 0;
            player->y++;
        }
        break;

    case 'q':
    case 'Q':
        return 1;
    }
    return 0;
}