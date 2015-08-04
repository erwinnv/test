#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "GameMap.hpp"
#include "Ship.hpp"

int main()
{
    std::cout << "Begin" << std::endl;
    GameMap first( 20, 10);
    std::cout << first.dump();
    
    Ship first_ship( 3, Ship::Orientation::Horizontal);
    std::cout << first_ship.dump();
    if( first_ship.get_state() != Ship::State::New)
    {
        std::cout << "Error: Wrong state. Expected 'New'" << std::endl;
    }
    
    first_ship.hit( 2);
    std::cout << first_ship.dump();
    if( first_ship.get_state() != Ship::State::Damaged)
    {
        std::cout << "Error: Wrong state. Expected 'Damaged'" << std::endl;
    }
    
    first_ship.hit( 1);
    first_ship.hit( 0);
    std::cout << first_ship.dump();
    if( first_ship.get_state() != Ship::State::Destroyed)
    {
        std::cout << "Error: Wrong state. Expected 'Destroyed'" << std::endl;
    }

    first.hit( 0, 0);
    first.hit( 0, 1);
    first.hit( 0, 5);
    first.hit( 0, 15);
    first.hit( 0, -1);
    first.hit( 0, -100);
    first.hit( 0, 100);
    first.hit( 1, 0);
    first.hit( 12, 3);
    first.hit( -1, 3);
    first.hit( 100, 0);
    first.hit( 100, 100);
    std::cout << first.dump();
    
    Ship simple( 3, Ship::Horizontal);
    first.add_ship( simple, 0, 0); 
    first.add_ship( simple, 6, 0); 
    first.add_ship( simple, 0, 8); 
    first.add_ship( simple, 4, 0);
    first.add_ship( simple, 5, 7);
    std::cout << first.dump();

    std::cout << "FIRE" << std::endl;
    first.hit( 0, 7);
    first.hit( 0, 8);
    first.hit( 0, 9);
    std::cout << first.dump();
    return 0;
}


