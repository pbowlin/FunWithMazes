#pragma once
/*
Maze implementation that uses an iterative randomized depth first search to generate the maze.
This maze algorithm favors long winding corridors with fewer dead ends.
*/

#include "Maze.h"

class DFSMaze : public Maze {
    public:
        DFSMaze(int rows, int cols);
        void generateMaze();
        
};