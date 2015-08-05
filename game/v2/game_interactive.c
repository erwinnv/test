#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "map.h"

enum {
    Default_x_size = 10,
    Default_y_size = 10,
};


int main( int argc, char *argv[])
{
    printf( "Begin\n");
    
    struct map_t *map = file_to_new_map( "map.txt");
    map_dump( map);

    struct map_t *enemy_map = map_get_map_for_enemy( map);
    map_dump( enemy_map);
    while( 1)
    {
        int x, y;
        scanf( "%d %d", &x, &y);
        map_fire( map, x, y);
        map_dump( map);
        map_update_enemy_map( enemy_map, map);
        map_dump( enemy_map);
    }
    map_delete( map);

    printf( "End\n");
    return 0;
}

