#include "GameMap.hpp"

#include <sstream>

GameMap::GameMap( unsigned int x, unsigned int y)
{
    x_size = x;
    y_size = y;
    map.resize( y_size);
    for( int i = 0; i < y_size; i++)
    {
        map[i].resize( x_size);
        for( int j = 0; j < x_size;  j++)
        {
            map[ i][ j] = 0;
        }
    }
}

std::string GameMap::dumpMap()
{
    std::stringstream dump;
    for( int i = 0; i < y_size; i++)
    {
        for( int j = 0; j < x_size;  j++)
        {
            dump << map[ i][ j] << " ";
        }
        dump << std::endl;
    }
    return dump.str();
}


