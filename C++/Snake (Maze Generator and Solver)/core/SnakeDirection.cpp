//SNAKEDIRECTIOM_CPP
#include "SnakeDirection.hpp"
#include "Direction.hpp"

	Direction snd::getDirection(int x)
	{
		switch(x)
		{
			case 0:
				return Direction::up;
				break;
			case 1:
				return Direction::down;
				break;
			case 2:
				return Direction::left;
				break;
			case 3:
				return Direction::right;
				break;
			default:
				return Direction::right;
		}
	}


	Direction snd::getOppositeDirection(Direction d)
	{
		switch (d)
			{
				case Direction::up:
					return Direction::down;
					break;
				case Direction::down:
					return Direction::up;
					break;
				case Direction::left:
					return Direction::right;
					break;
				case Direction::right:
					return Direction::left;
					break;
			}
	}



//SNAKEDIRECTION_CPP