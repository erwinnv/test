#include "Ship.hpp"

#include <sstream>

Ship::Ship( unsigned int new_size, 
          Ship::Orientation new_orientation)
{
    _orientation = new_orientation;
    _state = New;
    _size = new_size;
    _parts.resize( _size);
    for( int i = 0; i < _size; i++)
    {
        _parts[i] = true;
    }
}

std::string Ship::dump()
{
    std::stringstream dump_str;
    dump_str << "Ship dump start" << std::endl
             << "size = " << _size << std::endl
             << "state = " << state_to_str( _state) << std::endl 
             << "Ship:" << std::endl;
    std::string separator;
    if( _orientation == Horizontal)
    {
        separator = " ";
    }
    else
    {
        separator = "\n";
    }
    for( int i = 0; i < _size; i++)
    {
        if( _parts[ i])
        {
            dump_str << "O";
        }
        else
        {
            dump_str << "X";
        }
        dump_str << separator;
    }
    dump_str << std::endl
             << "Ship dump end" << std::endl;

    return dump_str.str();
}

void Ship::hit( unsigned int coordinate)
{
    _parts[ coordinate] = false;
    update_state();
}


std::string Ship::state_to_str( State state)
{
    switch( state)
    {
        case( New): return "New";
        case( Damaged): return "Damaged";
        case( Destroyed): return "Destroyed";
        default: return "Unknown";
    }
}

void Ship::update_state()
{
    unsigned int good_parts = 0;
    for( int i = 0; i < _size; i++)
    {
        if( _parts[ i])
        {
            good_parts++;
        }
    }
    if( good_parts == _size)
    {
        _state = New;
    }
    if( good_parts == 0)
    {
        _state = Destroyed;
    }
    if( 0 < good_parts && good_parts < _size)
    {
        _state = Damaged;
    }
}

Ship::State Ship::get_state()
{
    return _state;
}
