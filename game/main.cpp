#include <iostream>
#include <vector>

class GameMap
{
  private:
    unsigned int x_size;
    unsigned int y_size;
    std::vector< std::vector< int > > map;
    GameMap();
  public:
    GameMap( unsigned int x, unsigned int y);
    int dumpMap();
};

int main()
{
    std::cout << "Begin" << std::endl;
    GameMap first( 10, 10);
    first.dumpMap();

    return 0;
}

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

int GameMap::dumpMap()
{
    for( int i = 0; i < y_size; i++)
    {
        for( int j = 0; j < x_size;  j++)
        {
            std::cout << map[ i][ j] << " ";
        }
        std::cout << std::endl;
    }
}

