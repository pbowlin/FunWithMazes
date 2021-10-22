#pragma once
/*
Maze implementation that uses Prim's algorithm to generate the maze. 
Prim's algorithm favors frequent short dead ends.
*/

#include "Maze.h"

#include <vector>

// Struct to represent walls in a maze. Walls have coordinates for each
// side of the wall, representing the two rooms divided by said wall.
struct Wall {
  CellCoords side_A, side_B;
  
};

class PrimsMaze : public Maze {
    public:
        PrimsMaze(int rows, int cols);
        void generateMaze();
        
    private: 
    
        std::vector<Wall> getWalls(const CellCoords& cell);

};