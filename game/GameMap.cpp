#include "GameMap.hpp"

#include <sstream>
#include <iostream>

GameMap::GameMap( unsigned int x, unsigned int y)
{
    _x_size = x;
    _y_size = y;
    _map.resize( _x_size);
    for( int i = 0; i < _x_size; i++)
    {
        _map[i].resize( _y_size);
        for( int j = 0; j < _y_size;  j++)
        {
            _map[ i][ j] = Cell();
        }
    }
}

std::string GameMap::dump() const
{
    std::stringstream dump_str;
    dump_str << "GameMap dump start" << std::endl
             << "x_size = " << _x_size << std::endl
             << "y_size = " << _y_size << std:: endl;
    for( int j = 0; j < _y_size; j++)
    {
        for( int i = 0; i < _x_size;  i++)
        {
            dump_str << _map[ i][ j].state_to_str() << " ";
        }
        dump_str << std::endl;
    }
    
    dump_str << "Ships:" << std::endl;

    dump_str << "GameMap dump end" << std:: endl;
    return dump_str.str();
}

void GameMap::hit( unsigned int x, unsigned int y)
{
    if( !( 0 <= x && x < _x_size))
    {
        //TODO exception
        std::cerr << "Error: Wrong X" << std::endl;
        return;
    }
    if( !( 0 <= y && y < _y_size))
    {
        //TODO exception
        std::cerr << "Error: Wrong Y" << std::endl;
        return;
    }
    _map[ x][ y].hit();
}

GameMap::Cell::Cell()
{
    _state = EmptyCell;
    _ship = nullptr;
}

void GameMap::Cell::hit()
{
    _state = HitCell;
}

std::string GameMap::Cell::state_to_str() const
{
    if( _state == EmptyCell)
    {
        return ".";
    }
    if( _state == HitCell)
    {
        return "v";
    }
    if( _state == ShipCell)
    {
        return "O";
    }
    if( _state == ( ShipCell & HitCell))
    {
        return "X";
    }
    //TODO add exception
}
