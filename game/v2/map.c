#include "map.h"

#include "tools.h"

#include <stdlib.h>
#include <stdio.h>

scalar map_set( struct map_t *map, scalar x, scalar y, scalar val);
scalar map_check_ship( struct map_t *map, scalar x, scalar y);
scalar is_ship( scalar current); //0 if false
void map_destroy_ship( struct map_t *map, scalar x, scalar y);

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
