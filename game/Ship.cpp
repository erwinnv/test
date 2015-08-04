#include "Ship.hpp"

#include <sstream>
#include <iostream>

Ship::Ship( unsigned int new_size, 
          Ship::Orientation new_orientation)
{
    _orientation = new_orientation;
    _state = New;
    _size = new_size;
    for( int i = 0; i < _size; i++)
    {
        _parts.push_back( Part( this));
    }
    _map = nullptr;
}

std::string Ship::dump() const
{
    std::stringstream dump_str;
    dump_str << "Ship dump start" << std::endl
             << "size = " << _size << std::endl
             << "state = " << state_to_str() << std::endl 
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
        dump_str << _parts[ i].str() << separator;
    }
    dump_str << std::endl
             << "Ship dump end" << std::endl;

    return dump_str.str();
}

void Ship::hit( unsigned int coordinate)
{
    _parts[ coordinate].hit();
    update_state();
}


std::string Ship::state_to_str() const
{
    switch( _state)
    {
        case( New): return "New";
        case( Damaged): return "Damaged";
        case( Destroyed): return "Destroyed";
        default: 
            std::cerr << "Warning: unknown Ship state" << std::endl;
            //TODO exception
            return "Unknown";
    }
}

void Ship::update_state()
{
    unsigned int good_parts = 0;
    for( int i = 0; i < _size; i++)
    {
        if( _parts[ i].get_state())
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

unsigned int Ship::get_size() const
{
    return _size;
}

Ship::Orientation Ship::get_orientation() const
{
    return _orientation;
}

std::string Ship::str() const
{
    std::string result = state_to_str() + ": ";
    for( int i = 0; i < _size; i++)
    {
        result += _parts[ i].str();
    }
    return result;
}

void Ship::add_map( GameMap *map, unsigned int x, unsigned int y)
{
    _map = map;
    _x = x;
    _y = y;
    for( int i = 0; i < _size; i++)
    {
        _parts[ i].add_map( _map, x, y);
        if( _orientation == Horizontal)
        {
            x++;
        }
        if( _orientation == Vertical)
        {
            y++;
        }
    }
}

void Ship::hit( unsigned int x, unsigned int y)
{
    int offset_x = _x - x;
    int offset_y = _y - y;
    
    if( offset_x < 0 || offset_x > _size 
        || ( offset_x != 0 && _orientation != Horizontal))   
    {
        std::cerr << "Error: Ship( X, y) missed" << std::endl;
        //TODO exceptions
        return;
    }
    else if( _orientation == Horizontal)
    {
        hit( offset_x);
        return;
    }
    
    if( offset_y < 0 || offset_y > _size 
        || ( offset_y != 0 && _orientation != Vertical))  
    {
        std::cerr << "Error: Ship( x, Y) missed" << std::endl;
        //TODO exceptions
        return;
    }
    else if( _orientation == Vertical)
    {
        hit( offset_y);
        return;
    }

    std::cerr << "Error: Ship( x, y) missed" << std::endl;
    //TODO exceptions
    return;
}

bool Ship::get_part_state( unsigned int offset) const
{
    if( offset < _size)
    {
        return _parts[ offset].get_state();
    }
    //TODO exception
    return false;
}
bool Ship::get_part_state( unsigned int x, unsigned int y) const
{
    int offset_x = _x - x;
    int offset_y = _y - y;
    
    if( offset_x < 0 || offset_x > _size 
        || ( offset_x != 0 && _orientation != Horizontal))   
    {
        std::cerr << "Error: Ship( X, y) missed" << std::endl;
        //TODO exceptions
        return false;
    }
    else if( _orientation == Horizontal)
    {
        return get_part_state( offset_x);
    }
    
    if( offset_y < 0 || offset_y > _size 
        || ( offset_y != 0 && _orientation != Vertical))  
    {
        std::cerr << "Error: Ship( x, Y) missed" << std::endl;
        //TODO exceptions
        return false;
    }
    else if( _orientation == Vertical)
    {
        return get_part_state( offset_y);
    }

    std::cerr << "Error: Ship( x, y) missed" << std::endl;
    //TODO exceptions
    return false;
}

Ship::Part::Part( Ship * ship)
{
    _ship = ship;
    _state = true;
    _map = nullptr;
    _x = _y = 13;
}

std::string Ship::Part::str() const
{
    if( _state)
    {
        return "O";
    }
    else
    {
        return "X";
    }
}

bool Ship::Part::get_state() const
{
    return _state;
}

void Ship::Part::hit()
{
    _state = false;
    std::cout << "x = " << _x << "; y = " << _y << std::endl;
    _ship->hit( _x, _y);
    return;
}

void Ship::Part::add_map( GameMap *map, unsigned int x, unsigned int y)
{
    _map = map;
    _x = x;
    _y = y;
}

Ship::Part *Ship::get_part_ptr( unsigned int offset) 
{
    return &_parts[ offset];
}
Ship *Ship::Part::get_ship_ptr()
{
    return _ship;
}
