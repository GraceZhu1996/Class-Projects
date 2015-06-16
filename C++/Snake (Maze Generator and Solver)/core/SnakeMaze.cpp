//SNAKEMAZE_CPP
#include <random>
#include <ics46/factory/DynamicFactory.hpp>
#include "Maze.hpp"
#include "SnakeMaze.hpp"
#include "SnakeDirection.hpp"
#include "MazeVerifier.hpp"
#include "MazeException.hpp"
#include <iostream>
#include <utility>
#include <vector>


using namespace snd; //My SnakeDirection NameSpace

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, SnakeMaze, "Snake Maze (Required)");

int randomNumber(int min, int max)
{
	std::default_random_engine engine{std::random_device{}()};
	std::uniform_int_distribution<int> dist{min, max};
	return dist(engine);
}


bool dig(Maze &maze, std::pair<int, int> c, Direction move)
{
	if (maze.wallExists(std::get<0>(c), std::get<1>(c), move)) 
	{
		maze.removeWall(std::get<0>(c), std::get<1>(c), move);
		return true;
	}
	return false;
}



std::pair<int, int> getCell(int x, int y, int move)
{
	switch(move)
	{
		case 0: //UP
			return std::pair<int, int> (x, y - 1);
			break;
		case 1: //DOWN
			return std::pair<int, int> (x, y + 1);
			break;
		case 2: //LEFT
			return std::pair<int, int> (x - 1, y);
			break;
		case 3: //RIGHT
			return std::pair<int, int> (x + 1, y);
			break;
	}
}

std::vector<int> getValidMoves(Maze &maze, int x, int y, bool **footPrint)
{
	std::vector<int> result;
	int left = x - 1;
	int right = x + 1;
	int up = y - 1;
	int down = y + 1;

	if (left >= 0)
	{
		if (!footPrint[left][y])
			result.push_back(2); //Left
	}
	if (up >= 0)
	{
		if (!footPrint[x][up])
			result.push_back(0); //UP
	}
	if (right < maze.getWidth())
	{
		if (!footPrint[right][y])
			result.push_back(3); //RIght
	}
	if (down < maze.getHeight())
	{
		if (!footPrint[x][down])
			result.push_back(1); //Down
	}
	return result;
}

void mazeDigger(Maze &maze, std::pair<int, int> cell, bool **footPrint)
{

	int x = std::get<0>(cell);
	int y = std::get<1>(cell);

	footPrint[x][y] = true;
	std::pair<int, int> next;
	std::vector<int> validDirections = getValidMoves(maze, x, y, footPrint); 	//Get surrounding unvisited cells
	int r;
	while(validDirections.size() > 0)
	{
		std::vector<int>::iterator it = validDirections.begin();
		r = randomNumber(0, validDirections.size() - 1);
		while(--r > -1)
			it++;

		next = getCell(x, y, *it);

		if (!footPrint[std::get<0>(next)][std::get<1>(next)])
		{
			dig(maze, cell, getDirection(*it));
			mazeDigger(maze, next, footPrint);
		}
		
		validDirections = getValidMoves(maze, x, y, footPrint);
	}
}

SnakeMaze::SnakeMaze(){};
void SnakeMaze::generateMaze(Maze& maze)
{

    maze.addAllWalls();

   bool **reached = new bool*[maze.getWidth()];

    for (int i = 0; i < maze.getWidth(); ++i)
    {
    	reached[i] = new bool[maze.getHeight()];
    	for (int j = 0; j < maze.getHeight(); ++j)
    		reached[i][j] = false;
    }
   mazeDigger(maze, std::pair<int, int>(0,0), reached);

    for (int i = 0; i < maze.getWidth(); ++i)
    {
    	delete[] reached[i];
    }
    delete reached;


}
//SNAKEMAZE_CPP
