#include "map.h"

#include "tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum Const
{
    Search_mark = 's',
    Bad_map = 'B',
};

const scalar Ship_sizes[ Max_ship_size+1] = { 0, 4, 3, 2, 1};

scalar map_set( struct map_t *map, scalar x, scalar y, scalar val);
scalar map_check_ship( struct map_t *map, scalar x, scalar y);
scalar is_ship( scalar current); //0 if false
void map_destroy_ship( struct map_t *map, scalar x, scalar y);
struct map_t *map_new_clone( struct map_t * map);
scalar map_get_ship_size( struct map_t *search_map, scalar i, scalar j);
scalar bad_map_if_ship( struct map_t *search_map, scalar x, scalar y);

struct map_t *map_new( scalar x_size, scalar y_size)
{
    struct map_t * new_map = malloc( sizeof( struct map_t));
    if( new_map == NULL)
    {
        return NULL;
    }

    new_map->ptr = malloc( sizeof( scalar) * x_size*y_size);
    if( new_map->ptr == NULL)
    {
        free( new_map);
        return NULL;
    }
    for( int i = 0; i < x_size*y_size; i++)
    {
        new_map->ptr[ i] = Empty;
    }
    new_map->x_size = x_size;
    new_map->y_size = y_size;
    new_map->ships_count = 0;
    return new_map;
}

void map_delete( struct map_t *map)
{
    free( map->ptr);
    free( map);
}

scalar map_get( struct map_t *map, scalar x, scalar y)
{
    if( !( 0 <= x && x < map->x_size))
    {
        return Out_of_range;
    }
    if( !( 0 <= y && y < map->y_size))
    {
        return Out_of_range;
    }
    return map->ptr[ x + y*map->x_size];
}

scalar map_set( struct map_t *map, scalar x, scalar y, scalar val)
{
    if( !( 0 <= x && x < map->x_size))
    {
        return Out_of_range;
    }
    if( !( 0 <= y && y < map->y_size))
    {
        return Out_of_range;
    }
    return map->ptr[ x + y*map->x_size] = val;
}

int map_dump( struct map_t *map)
{
    printf( "Map dump start\n");
    printf( "x_size = %d\n", map->x_size);
    printf( "y_size = %d\n", map->y_size);
    for( int j = 0; j < map->y_size; j++)
    {
        for( int i = 0; i < map->x_size; i++)
        {
            printf( "%c ", ( char)map_get( map, i, j));
        }
        printf( "\n");
    }
    printf( "Map dump end\n");
    return 0;
}

int map_dump_scalar( struct map_t *map)
{
    printf( "Map dump start\n");
    printf( "x_size = %d\n", map->x_size);
    printf( "y_size = %d\n", map->y_size);
    for( int j = 0; j < map->y_size; j++)
    {
        for( int i = 0; i < map->x_size; i++)
        {
            printf( "%2d ", map_get( map, i, j));
        }
        printf( "\n");
    }
    printf( "Map dump end\n");
    return 0;
}

scalar map_fire( struct map_t *map, scalar x, scalar y)
{
    scalar aim = map_get( map, x, y);
    if( ! is_ship( aim))
    {
        map_set( map, x, y, Hit);
        return Hit;
    }
    if( is_ship( aim) && aim != Destroyed_ship)
    {
        map_set( map, x, y, Hit_ship);
        map_check_ship( map, x, y);
        return Hit_ship;
    }
    return 0;
}
 
struct map_t *file_to_new_map( const char * filename)
{
    FILE *in_file = fopen( filename, "r");
    if( in_file == NULL)
    {
        return NULL;
    }
    scalar x = 0, y = 0;
    fscanf( in_file, "%u\n", &x);
    fscanf( in_file, "%u\n", &y);

    struct map_t *new_map = map_new( x, y);
    for( int j = 0; j < y; j++)
    {
        for( int i = 0; i < x; i++)
        {
            char symbol = 0, space = 0;
            fscanf( in_file, "%c%c", &symbol, &space);
            map_set( new_map, i, j, symbol);
        }
    }
    fclose( in_file);
    
    return new_map;
}

scalar map_check_ship( struct map_t *map, scalar x, scalar y)
{
    scalar hit_count = 0;
    scalar count = 0; 

    scalar current = map_get( map, x, y);
    if( !is_ship( current))
    {
        return current;
    }

    int x0 = x;
    current = map_get( map, x0, y);
    while( is_ship( current))
    {
        current = map_get( map, x0, y);
        if( current == Hit_ship)
        {
            hit_count++;
        }
        if( current == Destroyed_ship)
        {
            return Destroyed_ship;
        }
        x0++;
        if( is_ship( current))
        {
            count++;
        }
    }

    x0 = x-1;
    current = map_get( map, x0, y);
    while( is_ship( current))
    {
        current = map_get( map, x0, y);
        if( current == Hit_ship)
        {
            hit_count++;
        }
        if( current == Destroyed_ship)
        {
            return Destroyed_ship;
        }
        x0--;
        if( is_ship( current))
        {
            count++;
        }
    }
    
    int y0 = y+1;
    current = map_get( map, x, y0);
    while( is_ship( current))
    {
        current = map_get( map, x, y0);
        if( current == Hit_ship)
        {
            hit_count++;
        }
        if( current == Destroyed_ship)
        {
            return Destroyed_ship;
        }
        y0++;
        if( is_ship( current))
        {
            count++;
        }
    }

    y0 = y-1;
    current = map_get( map, x, y0);
    while( is_ship( current))
    {
        current = map_get( map, x, y0);
        if( current == Hit_ship)
        {
            hit_count++;
        }
        if( current == Destroyed_ship)
        {
            return Destroyed_ship;
        }
        y0--;
        if( is_ship( current))
        {
            count++;
        }
    }

    if( count == hit_count)
    {
        map_destroy_ship( map, x, y);
        return Destroyed_ship;
    }
    if( hit_count != 0)
    {
        return Hit_ship;
    }

    return Ship_any;   
}

scalar is_ship( scalar current)
{
    if( ( Ship_any <= current && current <= Ship_biggest)
        || current == Hit_ship 
        || current == Destroyed_ship)
    {
        return current;
    }
    return 0;
}

void map_destroy_ship( struct map_t *map, scalar x, scalar y)
{
    scalar current = map_get( map, x, y);
    if( is_ship( current) && current != Destroyed_ship)
    {
        map_set( map, x, y, Destroyed_ship);
    
        map_destroy_ship( map, x+1, y);
        map_destroy_ship( map, x-1, y);
        map_destroy_ship( map, x, y+1);
        map_destroy_ship( map, x, y-1);
    }
}

struct map_t *map_get_map_for_enemy( struct map_t * map)
{
    struct map_t *enemy_map = map_new_clone( map);
    if( enemy_map == NULL)
    {
        return NULL;
    }

    for( int i = 0; i < enemy_map->x_size; i++)
    {
        for( int j = 0; j < enemy_map->y_size; j++)
        {
            scalar current = map_get( enemy_map, i, j);
            if(    current != Hit 
                && current != Destroyed_ship
                && current != Hit_ship)
            {
                map_set( enemy_map, i, j, Hidden);
            }
        }
    }
    return enemy_map;
}
struct map_t *map_update_enemy_map( struct map_t *dst, struct map_t *src)
{
    for( int i = 0; i < dst->x_size; i++)
    {
        for( int j = 0; j < dst->y_size; j++)
        {
            scalar current = map_get( src, i, j);
            if(    current != Hit 
                && current != Destroyed_ship
                && current != Hit_ship)
            {
                map_set( dst, i, j, Hidden);
            }
            else
            {
                map_set( dst, i, j, current);
            }
        }
    }
    return dst;
}


struct map_t *map_new_clone( struct map_t * map)
{
    struct map_t *new_map = map_new( map->x_size, map->y_size);
    if( new_map == NULL)
    {
        return NULL;
    }

    memcpy( new_map->ptr, map->ptr, sizeof( scalar) * map->x_size*map->y_size);
    new_map->x_size = map->x_size;
    new_map->y_size = map->y_size;

    return new_map;
}

scalar map_is_correct( struct map_t *map)
{
    scalar is_correct = 1;
    struct map_t *search_map = map_new_clone( map);
    scalar found_ships[ Max_ship_size+1] = { 0, 0, 0, 0, 0};
    for( int i = 0; i < search_map->x_size; i++)
    {
        for( int j = 0; j < search_map->y_size; j++)
        {
            scalar current = map_get( search_map, i, j);
            if( current == Search_mark )
            { 
                continue;
            }
            if( is_ship( current))
            {
                scalar size = map_get_ship_size( search_map, i, j);
                if( size == Bad_map)
                {
                    map_delete( search_map);
                    return 0;
                }
                if( 0 < size && size <= Max_ship_size)
                {
                    found_ships[ size]++;
                }
            }
            map_set( search_map, i, j, Search_mark);
        }
    }
    map_delete( search_map);
    for( int i = 0; i <= Max_ship_size; i++)
    {
        if( found_ships[ i] != Ship_sizes[ i])
        {
            printf( "Warning: ships with length %d expected %d, but found %d\n",
                    i, Ship_sizes[ i], found_ships[ i]);
            is_correct = 0;
        }
    }
    return is_correct;
}
scalar map_get_ship_size( struct map_t *search_map, scalar x, scalar y)
{

    scalar result = 0;
    scalar current = map_get( search_map, x, y);
    if( !is_ship( current))
    {
        return result = 0;
    }
    if( is_ship( map_get( search_map, x-1, y)))
    {
        if( bad_map_if_ship( search_map, x, y+1) 
            || bad_map_if_ship( search_map, x, y-1))
        {
            return Bad_map;
        }
        else
        {
            map_set( search_map, x, y+1, Search_mark);
            map_set( search_map, x, y-1, Search_mark);
        }
        return result = map_get_ship_size( search_map, x-1, y);
    }
    else if( is_ship( map_get( search_map, x, y-1)))
    {
        if( bad_map_if_ship( search_map, x+1, y)
            || bad_map_if_ship( search_map, x-1, y))
        {
            return Bad_map;
        }
        else
        {
            map_set( search_map, x+1, y, Search_mark);
            map_set( search_map, x-1, y, Search_mark);
        }
        return result = map_get_ship_size( search_map, x, y-1);
    }
    if( is_ship( map_get( search_map, x+1, y)))
    {//Horizontal
        if(    bad_map_if_ship( search_map, x-1, y-1)
            || bad_map_if_ship( search_map, x-1, y)
            || bad_map_if_ship( search_map, x-1, y+1))
        {
                return Bad_map;
        }
        scalar offset = 0;
        scalar current = map_get( search_map, x, y);
        while( is_ship( current))
        {
            if( bad_map_if_ship( search_map, x+offset, y+1) 
                || bad_map_if_ship( search_map, x+offset, y-1))
            {
                return Bad_map;
            }
            map_set( search_map, x+offset, y, Search_mark);
            offset++;
            current = map_get( search_map, x+offset, y);
        }
        result = offset;
        if(    bad_map_if_ship( search_map, x+offset, y-1)
            || bad_map_if_ship( search_map, x+offset, y)
            || bad_map_if_ship( search_map, x+offset, y+1))
        {
                return Bad_map;
        }
        return result;
    }
    else if( is_ship( map_get( search_map, x, y+1)))
    {//Vertical
        if(    bad_map_if_ship( search_map, x-1, y-1)
            || bad_map_if_ship( search_map, x, y-1)
            || bad_map_if_ship( search_map, x+1, y-1))
        {
                return Bad_map;
        }
        scalar offset = 0;
        scalar current = map_get( search_map, x, y);
        while( is_ship( current))
        {
            if( bad_map_if_ship( search_map, x+1, y+offset) 
                || bad_map_if_ship( search_map, x-1, y+offset))
            {
                return Bad_map;
            }
            map_set( search_map, x, y+offset, Search_mark);
            offset++;
            current = map_get( search_map, x, y+offset);
        }
        result = offset;
        if(    bad_map_if_ship( search_map, x-1, y+offset)
            || bad_map_if_ship( search_map, x, y+offset)
            || bad_map_if_ship( search_map, x+1, y+offset))
        {
            return Bad_map;
        }
        return result;
    }
    else 
    {//Single
        if(    bad_map_if_ship( search_map, x-1, y-1)
            || bad_map_if_ship( search_map, x-1, y)
            || bad_map_if_ship( search_map, x-1, y+1)
            || bad_map_if_ship( search_map, x, y-1)
            || bad_map_if_ship( search_map, x, y+1)
            || bad_map_if_ship( search_map, x+1, y-1)
            || bad_map_if_ship( search_map, x+1, y)
            || bad_map_if_ship( search_map, x+1, y+1))
        {
            return Bad_map;
        }
        else
        {
            map_set( search_map, x, y, Search_mark);
            return 1;
        }
    }
    return 0;
}

scalar bad_map_if_ship( struct map_t *search_map, scalar x, scalar y)
{
    if( is_ship( map_get( search_map, x, y)))
    {
        return Bad_map;
    }
    else
    {
        map_set( search_map, x, y, Search_mark);
        return 0;
    }
}
