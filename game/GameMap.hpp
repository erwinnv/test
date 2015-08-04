#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <string>
#include <vector>

#include "Ship.hpp"

class GameMap
{
  public:
    class Cell;
  private:
    unsigned int _x_size;
    unsigned int _y_size;
    std::vector< std::vector< Cell > > _map;
    std::vector< Ship > _ships;
    GameMap();
  public:
    GameMap( unsigned int x, unsigned int y);
    std::string dump() const;

    void hit( unsigned int x, unsigned int y);
    void add_ship( Ship ship, unsigned int x, unsigned int y);
    bool check_add_ship( Ship ship, unsigned int x, unsigned int y) const;
};

class GameMap::Cell
{
  public:
    enum State
    {
        EmptyCell = 0x0,
        HitCell   = 0x1,
        ShipCell  = 0x3,
    };
  private:
    State _state;
    Ship::Part *_part;
  public:
    Cell();
    std::string state_to_str() const;
    State get_state() const;
    void hit();
    Ship *get_ship_ptr() const;
    void add_part( Ship::Part *part);
};

#endif //GAME_MAP_HPP
