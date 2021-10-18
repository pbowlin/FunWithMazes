#pragma once
/*
Maze implementation that uses an iterative randomized depth first search to generate the maze. 
*/

#include "Maze.h"

class DFSMaze : public Maze {
    public:
        DFSMaze(int rows, int cols);
        void generateMaze();
        
    private: 
        bool cellVisited(const std::vector<MazeCell*>& visited, const MazeCell& cell);
        MazeCell* selectNextCell(std::vector<MazeCell*>& unvisited);
};