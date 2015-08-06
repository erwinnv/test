#include "map_generator.h"

#include <stdio.h>

#include "map.h"
#include "tools.h"

extern scalar map_set( struct map_t *map, scalar x, scalar y, scalar val);

scalar counter = 0;

enum
{
    Not_ship,
    Horizontal = 7,
    Vertical = 1,
};

struct map_t *place_all_ships( struct map_t *map,
                           struct map_t *mask_map,
                           scalar *ships,
                           scalar biggest_ship_size,
                           scalar rank);
struct map_t *place_ship( struct map_t *map, 
                          struct map_t *mask_map,
                          scalar ship_size,
                          scalar ship_orientation,
                          scalar x, scalar y,
                          scalar rank);
struct map_t *remove_ship( struct map_t *map, 
                          struct map_t *mask_map,
                          scalar ship_size,
                          scalar ship_orientation,
                          scalar x, scalar y,
                          scalar rank);
scalar update_rank( struct map_t *map, scalar x, scalar y, scalar rank);
scalar remove_rank( struct map_t *map, scalar x, scalar y, scalar rank);

scalar update_rank( struct map_t *map, scalar x, scalar y, scalar rank)
{
    if( map_get( map, x, y) == 1)
    {
        map_set( map, x, y, rank);
        return rank;
    }
    return 0;
}

scalar remove_rank( struct map_t *map, scalar x, scalar y, scalar rank)
{
    if( map_get( map, x, y) == rank)
    {
        map_set( map, x, y, 1);
        return rank;
    }
    return 0;
}

struct map_t *remove_ship( struct map_t *map, 
                          struct map_t *mask_map,
                          scalar ship_size,
                          scalar ship_orientation,
                          scalar x, scalar y,
                          scalar rank)
{
    if( ship_orientation == Vertical)
    {
        remove_rank( mask_map, x-1, y-1, rank);
        remove_rank( mask_map, x,   y-1, rank);
        remove_rank( mask_map, x+1, y-1, rank);
        for( int j = 0; j < ship_size; j++)
        {
            map_set( map, x, y+j, Empty);
            
            remove_rank( mask_map, x+1, y+j, rank);
            remove_rank( mask_map, x,   y+j, rank);
            remove_rank( mask_map, x-1, y+j, rank);
        }
        remove_rank( mask_map, x-1, y+ship_size, rank);
        remove_rank( mask_map, x,   y+ship_size, rank);
        remove_rank( mask_map, x+1, y+ship_size, rank);
        return map;
    }
    if( ship_orientation == Horizontal)
    {
        remove_rank( mask_map, x-1, y-1, rank);
        remove_rank( mask_map, x-1, y,   rank);
        remove_rank( mask_map, x-1, y+1, rank);
        for( int i = 0; i < ship_size; i++)
        {
            map_set( map, x+i, y, Empty);
            
            remove_rank( mask_map, x+i, y-1, rank);
            remove_rank( mask_map, x+i, y,   rank);
            remove_rank( mask_map, x+i, y+1, rank);
        }
        remove_rank( mask_map, x+ship_size, y-1, rank);
        remove_rank( mask_map, x+ship_size, y,   rank);
        remove_rank( mask_map, x+ship_size, y+1, rank);
        return map;
    }
 
    return NULL;
}


struct map_t *place_ship( struct map_t *map, 
                          struct map_t *mask_map,
                          scalar ship_size,
                          scalar ship_orientation,
                          scalar x, scalar y,
                          scalar rank)
{
    if( ship_orientation == Vertical)
    {
        for( int j = 0; j < ship_size; j++)
        {
            scalar current = map_get( mask_map, x, y+j);
            if( current == 0 || ( current < rank && current != 1))
            {
                return NULL;
            }
        }

        update_rank( mask_map, x-1, y-1, rank);
        update_rank( mask_map, x,   y-1, rank);
        update_rank( mask_map, x+1, y-1, rank);
        for( int j = 0; j < ship_size; j++)
        {
            map_set( map, x, y+j, Ship_any+ship_size);
            
            update_rank( mask_map, x+1, y+j, rank);
            update_rank( mask_map, x,   y+j, rank);
            update_rank( mask_map, x-1, y+j, rank);
        }
        update_rank( mask_map, x-1, y+ship_size, rank);
        update_rank( mask_map, x,   y+ship_size, rank);
        update_rank( mask_map, x+1, y+ship_size, rank);
        return map;
    }
    if( ship_orientation == Horizontal)
    {
        for( int i = 0; i < ship_size; i++)
        {
            scalar current = map_get( mask_map, x+i, y);
            if( current == 0 || ( current < rank && current != 1))
            {
                return NULL;
            }
        }

        update_rank( mask_map, x-1, y-1, rank);
        update_rank( mask_map, x-1, y,   rank);
        update_rank( mask_map, x-1, y+1, rank);
        for( int i = 0; i < ship_size; i++)
        {
            map_set( map, x+i, y, Ship_any+ship_size);
            
            update_rank( mask_map, x+i, y-1, rank);
            update_rank( mask_map, x+i, y,   rank);
            update_rank( mask_map, x+i, y+1, rank);
        }
        update_rank( mask_map, x+ship_size, y-1, rank);
        update_rank( mask_map, x+ship_size, y,   rank);
        update_rank( mask_map, x+ship_size, y+1, rank);
        return map;
    }
 
    return NULL;
}


struct map_t *place_all_ships( struct map_t *map,
                           struct map_t *mask_map,
                           scalar *ships,
                           scalar biggest_ship_size,
                           scalar rank)
{
    if( biggest_ship_size == 0)
    {
        counter++;
        if( counter % 10000000 == 0)
        {
            printf( "%u\n", counter);
            if( counter % 100000000 == 0)
            {
                map_dump( map);
                exit( 0);
            }
        }
        //map_dump( map);
        //map_dump_scalar( mask_map);
        //TODO
        return NULL;
    }
    if( ships[ biggest_ship_size] == 0)
    {
        biggest_ship_size--;
        place_all_ships( map, mask_map, ships, biggest_ship_size, rank+1);
        return NULL;
    }
    ships[ biggest_ship_size]--;
    scalar placed = 0;
    for( int i = 0; i < map->x_size; i++)
    {
        for( int j = 0; j < map->y_size; j++)
        {
            if( map_get( mask_map, i, j) != 1)
            {
                continue;
            }
            if( place_ship( map, mask_map, biggest_ship_size, 
                Vertical, i, j, rank+1) != NULL)
            {
                placed++;
                place_all_ships( map, mask_map, ships, 
                                 biggest_ship_size, rank+1);
                remove_ship( map, mask_map, biggest_ship_size,
                Vertical, i, j, rank+1);
            }
            if( biggest_ship_size == 1)
            {
                continue;
            }
            if( place_ship( map, mask_map, biggest_ship_size, 
                Horizontal, i, j, rank+1) != NULL)
            {
                placed++;
                place_all_ships( map, mask_map, ships, 
                                 biggest_ship_size, rank+1);
                remove_ship( map, mask_map, biggest_ship_size,
                Horizontal, i, j, rank+1);
            }
        }
    }
    ships[ biggest_ship_size]++;
    if( placed == 0)
    {
        return NULL;
    }
    return map;
}


// Not usable, because I didn't found a way to generate the seed :-(
// but ut works!
scalar get_expected_ship_parts_count();
struct map_t *new_map_from_seed( scalar *seed, scalar size);
scalar get_bit_summ_in_scalar( scalar num);
scalar get_bit_summ_in_array( scalar *array, scalar bit_size);
scalar get_bit_from_scalar( scalar num, scalar pos);

struct map_t *new_correct_map_from_scalar_array( scalar *seed, scalar size)
{
    if( X_size * Y_size > sizeof( scalar)*size*8)
    {
        printf( "Error: array is to short: can not generate a map\n");
        return NULL;
    }
    scalar requaired_array_size = get_requaired_array_size( X_size, Y_size);
    if( X_size * Y_size < requaired_array_size)
    {
        printf( "Warning: array is to big: only the beginnig will be used\n");
    }
    scalar expected_ship_parts_count = get_expected_ship_parts_count();
    
    scalar ships_parts_count = get_bit_summ_in_array( seed, 100);

    if( expected_ship_parts_count != ships_parts_count)
    {
        printf( "Error: wrong ship parts count\n");
        printf( "       expected: %d, got: %d\n",
                expected_ship_parts_count, ships_parts_count);
        return NULL;
    }

    struct map_t *map = new_map_from_seed( seed, 100);

    if( map_is_correct( map))
    {
        return map;
    }
    else
    {
        map_delete( map);
        return NULL;
    }
}

scalar get_bit_summ_in_array( scalar *array, scalar bit_size)
{
    scalar bit_sum = 0;
    for( int i = 0; i < bit_size/( sizeof( scalar)*8) - 1; i++)
    {
        bit_sum += get_bit_summ_in_scalar( array[ i]);
    }
    for( int i = 0; i < bit_size%( sizeof( scalar)*8); i++)
    {
        bit_sum += get_bit_from_scalar( array[ bit_size/( sizeof( scalar)*8)], i);
    }
    return bit_sum;
}

scalar get_requaired_array_size( scalar x, scalar y)
{
    return x*y/( sizeof( scalar)*8) + 1;
}

scalar get_expected_ship_parts_count()
{
    scalar expected_ship_parts_count = 0; 
    for( int i = 0; i <= Max_ship_size; i++)
    {
        expected_ship_parts_count += Ship_sizes[ i]*i;
    }
    return expected_ship_parts_count;
}

scalar get_bit_from_scalar( scalar num, scalar pos)
{
    if( num & ( 1 << pos))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

scalar get_bit_summ_in_scalar( scalar num)
{
    scalar sum = 0;
    for( int i = 0; i < sizeof( scalar) * 8; i++)
    {
        sum += get_bit_from_scalar( num, i);
    }
    return sum;
}

struct map_t *new_map_from_seed( scalar *seed, scalar size)
{
    struct map_t *map = map_new( 10, 10);

    int i = 0;
    while( i < size)
    {
        scalar offsset = i / ( sizeof( scalar)*8);
        scalar bit = i % ( sizeof( scalar)*8);
        if( get_bit_from_scalar( seed[ offsset], bit))
        {
            map->ptr[ i] = ( char) 'X';
        }
        i++;
    }
    return map;
}
