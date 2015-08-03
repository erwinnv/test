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
    std::string state_to_str( State);
    void update_state();
  public:
    Ship( unsigned int new_size, Ship::Orientation new_orientation);
    std::string dump();
    void hit( unsigned int coordinate);
    State get_state();
};

