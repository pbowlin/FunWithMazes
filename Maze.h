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
  
    virtual void generateMaze() = 0;
    
    void listCells();
    virtual void drawMaze();
    
  protected:
    virtual void initializeCells(int rows, int cols);
    std::vector<MazeCell> getNeighbors(int row, int col); 
    virtual void pickStartAndFinish();
    
    int maze_rows, maze_cols;
    CellCoords start;
    CellCoords finish;
    std::vector<std::vector<MazeCell>> maze;
    
     
};