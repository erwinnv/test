#include "tools.h"

#include <stdlib.h>
#include <time.h>

scalar get_random_scalar( scalar max)
{
    return rand() % max;
}

void get_random_scalar_set_seed()
{
    srand( time( NULL));
}

