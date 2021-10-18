#pragma once

#include "MazeCell.h"

#include <vector>

class Maze {
  public:
  
    Maze(int rows, int cols);
  
    virtual void generateMaze() = 0;
    
    void listCells();
    virtual void drawMaze();
    
  protected:
    virtual void initializeCells(int rows, int cols);
    std::vector<MazeCell*> getNeighbors(MazeCell& mc);
    virtual void pickStartAndFinish();
    
    int maze_rows, maze_cols;
    CellCoords start;
    CellCoords finish;
    std::vector<std::vector<MazeCell>> maze;
    
     
};