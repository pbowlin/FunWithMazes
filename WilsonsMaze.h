#pragma once
/*
Maze implementation that uses Wilson's algorithm to generate the maze. 
Wilson's algorithm is one of the few algorithms with no biases. (i.e. it does
not tend to favor long corridors, or frequent short dead ends.)
*/

#include "Maze.h"

#include <list>
#include <unordered_set>

class WilsonsMaze : public Maze {
    public:
        WilsonsMaze(int rows, int cols);
        void generateMaze();
        
    private: 
        std::list<CellCoords> performRandomWalk(CellCoords start_coords, const std::unordered_set<CellCoords>& cells_not_in_maze);
        std::list<CellCoords>::iterator checkPathForCell(const std::list<CellCoords>& path, const CellCoords& next_coords);
        void addPathToMaze(const std::list<CellCoords>& path, std::unordered_set<CellCoords>& cells_not_in_maze);

};