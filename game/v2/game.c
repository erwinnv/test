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
    
    struct map_t *map = map_new( Default_x_size, Default_y_size);
    map_dump( map);
    map_fire( map, 1, 1);
    map_dump( map);
    map_delete( map);

    map = file_to_new_map( "map.txt");
    map_fire( map, 1, 1);
    map_dump( map);
    map_fire( map, 1, 2);
    map_fire( map, 1, 3);
    map_fire( map, 1, 4);
    map_dump( map);
    map_delete( map);

    printf( "End\n");
    return 0;
}

