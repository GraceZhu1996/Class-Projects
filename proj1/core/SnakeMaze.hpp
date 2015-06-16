//SNAKEMAZE_HPP
#ifndef SNAKEMAZE_HPP
#define SNAKEMAZE_HPP

#include "MazeGenerator.hpp"

class SnakeMaze : public MazeGenerator
{
public:

    SnakeMaze();
    virtual void generateMaze(Maze& maze);
};

#endif
//SNAKEMAZE_HPP
