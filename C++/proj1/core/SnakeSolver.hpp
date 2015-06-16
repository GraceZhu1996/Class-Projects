//SNAKE_SOLVER_HPP
#ifndef SNAKE_SOLVER_HPP
#define SNAKE_SOLVER_HPP

#include "MazeSolver.hpp"

class SnakeSolver : public MazeSolver
{
public:
	SnakeSolver();

    virtual void solveMaze(
        const Maze& maze, MazeSolution& mazeSolution);
};

#endif
//SNAKE_SOLVER_HPP