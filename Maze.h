#pragma once
/*
Abstract class to define a generic maze. All mazes should have a maze grid
as well as a start and finish. Neighbors are defined as cells orthagonal to 
a given cell... regardless of whether or not there is a wall between them.
*/

#include "MazeCell.h"

#include <vector>

class Maze {
  public:
  
    Maze(int rows, int cols);
    virtual ~Maze() = default;
  
    virtual void generateMaze() = 0;
    void listCellsWithPassages();
    virtual void drawMaze();
    
  protected:
    virtual void initializeCells(int rows, int cols);
    virtual std::vector<CellCoords> getNeighbors(int row, int col); 
    virtual void pickStartAndFinish();
    virtual bool cellVisited(const std::vector<CellCoords>& visited, const CellCoords& cell);
    
    int randomlySelectNextIndex(int num_options);
    
    int maze_rows, maze_cols;
    CellCoords start;
    CellCoords finish;
    std::vector<std::vector<MazeCell>> maze;
    
     
};