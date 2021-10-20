#pragma once
/*
Maze implementation that uses Wilson's algorithm to generate the maze. 
Wilson's algorithm is one of the few algorithms with no biases. (i.e. it does
not tend to favor long corridors, or frequent short dead ends.)
*/

#include "Maze.h"

#include <list>

class WilsonsMaze : public Maze {
    public:
        WilsonsMaze(int rows, int cols);
        void generateMaze();
        
    private: 
        // bool cellVisited(const std::vector<MazeCell*>& visited, const MazeCell& cell);
        // MazeCell* selectNextCell(std::vector<MazeCell*>& unvisited);
        std::list<MazeCell> performRandomWalk(MazeCell start_cell);
        MazeCell selectNextCell(const std::vector<MazeCell>& neighbors);
};