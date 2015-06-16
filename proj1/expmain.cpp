#include "Maze.hpp"
#include "SnakeMaze.hpp"

int main()
{
    Maze myMaze;
    SnakeMaze mazeGen;

    mazeGen.generateMaze(myMaze);
    return 0;
}
