//DIRECTION_HPP
#ifndef DIRECTION_HPP
#define DIRECTION_HPP


enum class Direction {UP, DOWN, LEFT, RIGHT, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT};

namespace DirectionMethods
{
	const int MAX = 8;
	
	int toInt(Direction move);
	Direction toDirection(int move);
}
#endif

//DIRECTION_HPP