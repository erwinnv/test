#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>
#include <vector>

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
  private:
    unsigned int _size;
    std::vector< bool> _parts;
    Orientation _orientation;
    State _state;
    
    Ship();
    void update_state();
  public:
    Ship( unsigned int new_size, Ship::Orientation new_orientation);
    std::string dump();
    void hit( unsigned int coordinate);
    std::string state_to_str() const;
    State get_state();
};

#endif //SHIP_HPP
