#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>
#include <vector>

class GameMap;

class Ship
{
  public:
    enum Orientation
    {
        Horizontal,
        Vertical
    };
    enum State
    {
        New,
        Damaged,
        Destroyed
    };
    class Part;
  private:
    unsigned int _size;
    std::vector< Part> _parts;
    Orientation _orientation;
    State _state;
    
    GameMap *_map;
    unsigned int _x, _y;
    
    Ship();
    void update_state();
  public:
    Ship( unsigned int new_size, Ship::Orientation new_orientation);
    std::string dump() const;
    std::string str() const;
    void hit( unsigned int offset);
    void hit( unsigned int x, unsigned int y);
    std::string state_to_str() const;
    bool get_part_state( unsigned int offset) const;
    bool get_part_state( unsigned int x, unsigned int y) const;
    Part *get_part_ptr( unsigned int offset);
    State get_state();
    unsigned int get_size() const;
    Orientation get_orientation() const;

    void add_map( GameMap *map, unsigned int x, unsigned int y);
};

class Ship::Part
{
  private:
    unsigned int _x, _y;
    bool _state;
    GameMap *_map;
    Ship *_ship;
    Part();
  public:
    Part( Ship *ship);
    void hit();
    void add_map( GameMap *map, unsigned int x, unsigned int y);
    bool get_state() const;
    std::string str() const;
    Ship *get_ship_ptr();
};

#endif //SHIP_HPP
