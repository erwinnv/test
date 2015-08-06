#ifndef MAP_H
#define MAP_H

#include "tools.h"

enum field
{
    Empty = '.',
    Hit   = 'v',
    Hidden = '-',

    Ship_any     = '0',
    Ship_single  = '1',
    Ship_double  = '2',
    Ship_triple  = '3',
    Ship_qward   = '4',
    Ship_biggest = '5',
    
    Hit_ship = 'X',
    Destroyed_ship = 'Z',
    
    Out_of_range = 0, //should be 0, used in if()
};

enum Const_h
{
    Max_ship_size = 4,
};
extern const scalar Ship_sizes[];
//Ships[ length] - expected count of ships with length 


struct map_t
{
    char *ptr;
    scalar x_size, y_size;
    scalar ships_count;
};

struct map_t *map_new( scalar x_size, scalar y_size);
void map_delete( struct map_t *map);

scalar map_get( struct map_t *map, scalar x, scalar y);
scalar map_fire( struct map_t *map, scalar x, scalar y);

struct map_t *file_to_new_map( const char *filename);
struct map_t *map_get_map_for_enemy( struct map_t *map);
struct map_t *map_update_enemy_map( struct map_t *dst, struct map_t *src);

scalar map_is_correct( struct map_t *map); 


int map_dump( struct map_t *map);

#endif //MAP_H

