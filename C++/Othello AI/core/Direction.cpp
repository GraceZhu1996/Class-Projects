//DIRECTION_CPP
#include "Direction.hpp"

int DirectionMethods::toInt(Direction move)
{
	return static_cast<int>(move);
}
Direction DirectionMethods::toDirection(int move)
{
	switch(move)
	{
		case 0:
			return Direction::UP;
		case 1: 
			return Direction::DOWN;
		case 2: 
			return Direction::LEFT;
		case 3: 
			return Direction::RIGHT;
		case 4: 
			return Direction::TOPLEFT;
		case 5: 
			return Direction::TOPRIGHT;
		case 6: 
			return Direction::BOTTOMLEFT;
		case 7: 
			return Direction::BOTTOMRIGHT;
	}
}


//DIRECTION_CPP