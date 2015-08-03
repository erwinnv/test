#include <string>
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
    std::string dumpMap();
};


