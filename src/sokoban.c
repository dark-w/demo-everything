#include <stdio.h>
#include <stdlib.h>

#include "types.h"

#include "sokoban.h"
#include "hsv_rgb.h"

static void sokoban_test(void)
{
    struct sokoban_map base_map = { .length = LENTH,
                                    .width = WIDTH,
                                    .map = NULL };
    struct human player = {
        .x = HUMAN_INIT_X,
        .y = HUMAN_INIT_Y,
    };
    struct sokoban_box box_a = { .x = box_x, .y = box_y };

    init_map(&base_map);

    while (1) {
        __UNUSED__ int r = system("clear");

        base_map.map[player.x][player.y] = 2;
        base_map.map[box_a.x][box_a.y] = 3;
        for (int x = 0; x < base_map.length; x++) {
            for (int y = 0; y < base_map.width; y++) {
                switch (base_map.map[x][y]) {
                case 0:
                    printf("  ");

                    break;

                case 1:
                    printf(" ▣");

                    break;

                case 2:
                    printf(" ♀");

                    break;

                case 3:
                    printf(" ▤");

                    break;
                }
            }
            printf("\n");
        }

        // FIXME
        int move = getchar();
        int ret = human_move(&base_map, &player, move);
        if (ret == 1) {
            goto end;
        }
    }

end:
    free_map(&base_map);
}

LIBRGB_SUPPORTED(12)

static void hsv_rgb_test(void)
{
}

int main(void)
{
    sokoban_test();
    hsv_rgb_test();

    return 0;
}
