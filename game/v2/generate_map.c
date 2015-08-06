#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "map_generator.h"
#include "map.h"

#define MAX 0xFFFFFFFF

int main()
{
    printf( "Begin\n");
    struct map_t *map = map_new( 10, 10);
    struct map_t *mask_map = map_new( 10, 10);
    
    scalar ships[] = { 0, 4, 3, 2, 3};

    for( int i = 0; i < 100; i++)
    {
        mask_map->ptr[ i] = 1;
    }
    
    get_random_scalar_set_seed(); 
    if( fill_with_ships_random( map, mask_map, ships, 4, 2) != NULL)
    {
        map_dump( map);
    }
    else
    {
        printf( "GOOD LUCK!!!\n");
    }


// Not usable, because I didn't found a way to generate the seed :-(
#if 0
    scalar size = get_requaired_array_size( 10, 10);
    scalar *array = calloc( size, sizeof( scalar));
    array[ 1] = 0xFFFFF;

    printf( "%d\n", sizeof( scalar));
    for( array[3] = 0; array[3] <= MAX; array[3]++)
    {
        for( array[2] = 0; array[2] <= MAX; array[2]++)
        {
            for( array[1] = 0; array[1] <= MAX; array[1]++)
            {
                for( array[0] = 0; array[0] <= MAX; array[0]++)
                {
                    struct map_t *map = new_correct_map_from_scalar_array( array, size);
                    if( map != NULL)
                    {
                        printf( "map: %u %u %u %u\n", array[0], array[1], array[2], array[3]);
                        map_delete( map);
                    }
                    printf ( "%d\n", array[0]);
                }
                printf( "0\n");
            }
        }
    }
    free( array);
#endif //if 0
    printf( "End\n");
    return 0;
}
