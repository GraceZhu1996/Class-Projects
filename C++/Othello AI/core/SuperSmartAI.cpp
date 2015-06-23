//SUPERSMARTAI_CPP
#include <ics46/factory/DynamicFactory.hpp>
#include "SuperSmartAI.hpp"
#include "Direction.hpp"
#include <iostream>
#include <math.h>
#include <cmath>
#include <set>
#include "OthelloGameState.hpp"

using namespace std;

typedef std::pair<int, int> intPair;
typedef std::pair<int, std::pair<int, int>> intSquarePair;
typedef std::pair<intPair, Direction> CellDirection;


struct Move
{
	bool corner = false;
	bool edge = false;
	int distance = 0;
	intPair destination;

	bool operator>(const Move &right) const
	{
		//Rankings
		if (this->corner)
			return true;
		else if (right.corner)
			return false;
		if (this->edge)
			return true;
		else if (right.edge)
			return false;
		return this->distance > right.distance;
	}

	bool operator<(const Move &right) const
	{
		//Rankings
		return !operator>(right);
	}

	bool operator=(const Move &right) const
	{
		return (this->corner == right.corner && this->edge == right.edge &&  this->distance == right.distance && this->destination == right.destination);
	}
};


intPair nullCell = intPair(-1, -1);

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, tsalako::SuperSmartAI, "Cortana (Required).");

int toInt(OthelloCell cell)
{
	//Returns  int value of cell
	return static_cast<int>(cell);
}

int distance(intPair from, intPair to)
{
	int from_x = get<0>(from);
	int from_y = get<1>(from);
	int to_x = get<0>(to);
	int to_y = get<1>(to);

	return sqrt(pow((from_y - to_y), 2) + pow((from_x - to_x), 2));
}

intPair getMoveInDirection(const OthelloGameState &state, intPair cell, Direction move, const int &width, const int &height)
{

	const int parent_x = get<0>(cell);
	const int parent_y = get<1>(cell);
	const OthelloCell parentCell = state.board().cellAt(parent_x, parent_y);

	OthelloCell previousCell = parentCell;

	int x = get<0>(cell);
	int y = get<1>(cell);

	switch (move)
	{
		case Direction::UP:
			y--;
			while(y >= 0)
			{
				if (state.board().isValidCell(x, y))
				{	
					if (state.board().cellAt(x, y) == OthelloCell::empty)
					{
						if (previousCell == OthelloCell::empty)  //If the previous cell is empty
							return nullCell;
						else if(previousCell != parentCell) //If the previous cell was an opponents
							return intPair(x, y);
						else if(previousCell == parentCell)
							return nullCell;
					}
					else if(state.board().cellAt(x, y) == parentCell)
					{
						return nullCell;
					}

					previousCell = state.board().cellAt(x, y);
					y--;
				} 
				else
				{
					return nullCell;
				}
			}
			return nullCell;

		case Direction::DOWN:
			y++;
			while(y < height)
			{
				if (state.board().isValidCell(x, y))
				{	
					if (state.board().cellAt(x, y) == OthelloCell::empty)
					{
						if (previousCell == OthelloCell::empty)  //If the previous cell is empty
							return nullCell;
						else if(previousCell != parentCell) //If the previous cell was an opponents
							return intPair(x, y);
						else if(previousCell == parentCell)
							return nullCell;
					}
					else if(state.board().cellAt(x, y) == parentCell)
					{
						return nullCell;
					}
					
					previousCell = state.board().cellAt(x, y);
					y++;
				} 
				else
				{
					return nullCell;
				}
			}
			return nullCell;

		case Direction::LEFT:
			x--;
			while(x >= 0)
			{
				if (state.board().isValidCell(x, y))
				{	
					if (state.board().cellAt(x, y) == OthelloCell::empty)
					{
						if (previousCell == OthelloCell::empty)  //If the previous cell is empty
							return nullCell;
						else if(previousCell != parentCell) //If the previous cell was an opponents
							return intPair(x, y);
						else if(previousCell == parentCell)
							return nullCell;
					}
					else if(state.board().cellAt(x, y) == parentCell)
					{
						return nullCell;
					}
					
					previousCell = state.board().cellAt(x, y);
					x--;
				} 
				else
				{
					return nullCell;
				}
			}
			return nullCell;

		case Direction::RIGHT:
			x++;
			while(x < width)
			{
				if (state.board().isValidCell(x, y))
				{	
					if (state.board().cellAt(x, y) == OthelloCell::empty)
					{
						if (previousCell == OthelloCell::empty)  //If the previous cell is empty
							return nullCell;
						else if(previousCell != parentCell) //If the previous cell was an opponents
							return intPair(x, y);
						else if(previousCell == parentCell)
							return nullCell;
					}
					else if(state.board().cellAt(x, y) == parentCell)
					{
						return nullCell;
					}
					
					previousCell = state.board().cellAt(x, y);
					x++;
				} 
				else
				{
					return nullCell;
				}
			}
			return nullCell;

		case Direction::TOPLEFT:
			y--; x--;
			while(x >= 0 && y >= 0)
			{
				if (state.board().isValidCell(x, y))
				{	
					if (state.board().cellAt(x, y) == OthelloCell::empty)
					{
						if (previousCell == OthelloCell::empty)  //If the previous cell is empty
							return nullCell;
						else if(previousCell != parentCell) //If the previous cell was an opponents
							return intPair(x, y);
						else if(previousCell == parentCell)
							return nullCell;
					}
					else if(state.board().cellAt(x, y) == parentCell)
					{
						return nullCell;
					}
					
					previousCell = state.board().cellAt(x, y);
					y--; x--;
				} 
				else
				{
					return nullCell;
				}
			}
			return nullCell;

		case Direction::TOPRIGHT:
			y--; x++;
			while(x < width && y >= 0)
			{
				if (state.board().isValidCell(x, y))
				{	
					if (state.board().cellAt(x, y) == OthelloCell::empty)
					{
						if (previousCell == OthelloCell::empty)  //If the previous cell is empty
							return nullCell;
						else if(previousCell != parentCell) //If the previous cell was an opponents
							return intPair(x, y);
						else if(previousCell == parentCell)
							return nullCell;
					}
					else if(state.board().cellAt(x, y) == parentCell)
					{
						return nullCell;
					}
					
					previousCell = state.board().cellAt(x, y);
					y--; x++;
				} 
				else
				{
					return nullCell;
				}
			}
			return nullCell;

		case Direction::BOTTOMLEFT:
			y++; x--;
			while(x >= 0 && y < height)
			{
				if (state.board().isValidCell(x, y))
				{	
					if (state.board().cellAt(x, y) == OthelloCell::empty)
					{
						if (previousCell == OthelloCell::empty)  //If the previous cell is empty
							return nullCell;
						else if(previousCell != parentCell) //If the previous cell was an opponents
							return intPair(x, y);
						else if(previousCell == parentCell)
							return nullCell;
					}
					else if(state.board().cellAt(x, y) == parentCell)
					{
						return nullCell;
					}
					
					previousCell = state.board().cellAt(x, y);
					y++; x--;
				} 
				else
				{
					return nullCell;
				}
			}
			return nullCell;

		case Direction::BOTTOMRIGHT:
			y++; x++;
			while(x < width && y < height)
			{
				if (state.board().isValidCell(x, y))
				{	
					if (state.board().cellAt(x, y) == OthelloCell::empty)
					{
						if (previousCell == OthelloCell::empty)  //If the previous cell is empty
							return nullCell;
						else if(previousCell != parentCell) //If the previous cell was an opponents
							return intPair(x, y);
						else if(previousCell == parentCell)
							return nullCell;
					}
					else if(state.board().cellAt(x, y) == parentCell)
					{
						return nullCell;
					}
					
					previousCell = state.board().cellAt(x, y);
					y++; x++;
				} 
				else
				{
					return nullCell;
				}
			}
			return nullCell;

	}
}

std::set<Move> getValidMoves(const OthelloGameState &state, OthelloCell player, const int &width, const int &height)
{
	intPair corner_A = intPair(0, 0);
	intPair corner_B = intPair(width - 1, 0);
	intPair corner_C = intPair(0, height - 1);
	intPair corner_D = intPair(width - 1, height - 1);


	std::set<Move> result;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (state.board().cellAt(x, y) == player) //If our color is in that cell, generate posible moves;
			{
				for (int i = 0; i < DirectionMethods::MAX; i++)
				{
					intPair ip = getMoveInDirection(state, intPair(x, y), DirectionMethods::toDirection(i), width, height);

					if (ip != nullCell) //Filtering out the invalid moves
					{
						Move m;
						m.destination = ip;
						if (ip == corner_A || ip == corner_B || ip == corner_C || ip == corner_D)
						{
							m.corner = true;
						}
						if ( get<0>(ip) == 0 ||  get<0>(ip) == width - 1 ||  get<1>(ip) == 0 ||  get<1>(ip) == height - 1)
						{
							m.edge = true;
						}
						m.distance = distance(intPair(x, y), ip);
						result.insert(m);
					}
					
				}
			}
		}
	}

	return result;	
}

int search(std::unique_ptr<OthelloGameState> state, int depth, const OthelloCell originalPlayer, const int &width, const int &height)
{
	OthelloCell currentPlayer;
	if (state->isBlackTurn())
		currentPlayer = OthelloCell::black;
	else
		currentPlayer = OthelloCell::white;

	if (depth == 0)
	{
		//Base case
		int totalblack = state->blackScore();
		int totalwhite = state->whiteScore();

		if (originalPlayer == OthelloCell::black)
			return totalblack-totalwhite;
		else
			return totalwhite-totalblack;
	}
	else
	{
		//Recursive step
		std::set<Move> moves = getValidMoves(*state, currentPlayer, width, height);
		std::set<Move>::iterator it= moves.begin();;

		int finalscore;

		for (it = moves.begin(); it != moves.end(); it++)
		{

			int score = 0;
			//Make Move
			std::unique_ptr<OthelloGameState> clone = state->clone();

			if (clone->isValidMove(get<0>(it->destination), get<1>(it->destination)))
				clone->makeMove(get<0>(it->destination), get<1>(it->destination));
			else
				continue;


			//Compute Score
			if (currentPlayer == originalPlayer)
			{
				if (it->corner)
				{
					score += sqrt(width*height) * 10;
				}
				else if (it->edge)
				{
					score += sqrt(width*height) * 5;
				}
				else
				{
					score += sqrt(width*height) + it->distance;
				}
			}
			else
			{
				if (it->corner)
				{
					score -= sqrt(width*height) * 10;
				}
				else if (it->edge)
				{
					score -= sqrt(width*height) * 5;
				}
				else
				{
					score -= sqrt(width*height) + it->distance;
				}
			}


			int result =  search(clone->clone(), depth - 1, originalPlayer, width, height);
			if (result > score)
			{
				finalscore = result;
			}
		}

		return finalscore;
	}
}


intPair tsalako::SuperSmartAI::chooseMove(const OthelloGameState& state)
{
	const int width = state.board().width();
	const int height = state.board().height();

	OthelloCell currentPlayer;
	if (state.isBlackTurn())
		currentPlayer = OthelloCell::black;
	else
		currentPlayer = OthelloCell::white;

	std::set<Move> moves = getValidMoves(state, currentPlayer, width, height);
	std::set<Move>::iterator it = moves.begin();

	int score = 0;
	intPair recommendedMove = it->destination;

	for (it = moves.begin(); it != moves.end(); it++)
	{
		if (it->corner)
		{
			recommendedMove = it->destination;
			break;
		}
		std::unique_ptr<OthelloGameState> clone = state.clone();

		if (clone->isValidMove(get<0>(it->destination), get<1>(it->destination)))
			clone->makeMove(get<0>(it->destination), get<1>(it->destination));
		else
			continue;

		int result = search(state.clone(), 3, currentPlayer, width, height);
		if (result > score)
		{
			score = result;
			recommendedMove = it->destination;
		}
	}

	return recommendedMove;
}
//SUPERSMARTAI_CPP