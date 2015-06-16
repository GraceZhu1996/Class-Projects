#include "SnakeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include <vector>
#include <utility>
#include <iostream>
#include "SnakeDirection.hpp"
#include <ics46/factory/DynamicFactory.hpp>

using namespace snd;

typedef std::pair<int, int> intPair;
typedef std::vector<Direction> dVector;

const int STATUS_OK = 0;
const int STATUS_BLOCKED = 1;
const int STATUS_DONE= 2;



ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, SnakeSolver, "Snake Solver (Required)");


dVector getPossibleMoves(const Maze &maze, intPair p, Direction from)
{
	dVector result;
	for (int i = 3; i > - 1; i--) //Reverse loop bc our solution is to the bottom right.
	{
		if (!maze.wallExists(std::get<0>(p), std::get<1>(p), getDirection(i)))
		{
			if(getDirection(i) != from) //We do not want to go back the direction we came
				result.push_back(getDirection(i));
		}
		
	}
	return result;

}

int solver(const Maze &maze, MazeSolution &mazeSolution, intPair position, Direction from)
{
	if (mazeSolution.isComplete())
		return STATUS_DONE;

	dVector moves = getPossibleMoves(maze, position, from);
	if (moves.size() > 0)
	{
		for (dVector::iterator it = moves.begin(); it != moves.end(); it++)
		{
			int result = STATUS_OK;

			mazeSolution.extend(*it);
			result = solver(maze, mazeSolution, mazeSolution.getCurrentCell(), getOppositeDirection(*it));

			if (result == STATUS_BLOCKED)
			{
				mazeSolution.backUp();
				continue;
			}
			else if (result == STATUS_OK)
			{
				break;
			}else if (result == STATUS_DONE)
				return STATUS_DONE;

		}
		return STATUS_BLOCKED;
	}
	else
	{
		return STATUS_BLOCKED;
	}
}

SnakeSolver::SnakeSolver(){};
void SnakeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
	solver(maze, mazeSolution, mazeSolution.getCurrentCell(), Direction::up);

}


