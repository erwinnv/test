#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include "map.h"

enum
{
    X_size = 10,
    Y_size = 10,
};

struct map_t *place_all_ships( struct map_t *map,
                           struct map_t *mask_map,
                           scalar *ships,
                           scalar biggest_ship_size,
                           scalar rank);
struct map_t *generate_new_map();
// Not usable, because I didn't found a way to generate the seed :-(
struct map_t *new_correct_map_from_scalar_array( scalar *seed, scalar size);
scalar get_requaired_array_size( scalar x, scalar y);

#endif //MAP_GENERATOR_H
