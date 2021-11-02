#include "DFSMaze.h"

#include <iostream>
#include <stack>
#include <random>

DFSMaze::DFSMaze(int rows, int cols) :
    Maze(rows, cols)
{

    Maze::initializeCells(rows, cols);
}

void DFSMaze::generateMaze(){
    std::vector<CellCoords> visited;
    std::stack<CellCoords> path;
    
    visited.push_back(maze[0][0].getCellCoords());
    path.push(maze[0][0].getCellCoords());
    
    while(!path.empty()){
        CellCoords currentCell = path.top();
        std::vector<CellCoords> neighbors = Maze::getNeighbors(currentCell.row, currentCell.col);
        
        std::vector<CellCoords> unvisited;
        
        for(CellCoords cell : neighbors){
            if(!Maze::cellVisited(visited, cell)){
                unvisited.push_back(cell);
            }
        }
        
        if(unvisited.empty()){
            path.pop();
        } else {
            CellCoords nextCell = unvisited[Maze::randomlySelectNextIndex(unvisited.size())];
 
            // Get the maze cells from the actual maze so we can add passages in the maze
            MazeCell* toMazeCell = &(Maze::maze[nextCell.row][nextCell.col]);
            MazeCell* fromMazeCell = &(Maze::maze[currentCell.row][currentCell.col]);
            
            // Add passages between the two cells of the actual maze
            fromMazeCell->addPassage(*toMazeCell);
            toMazeCell->addPassage(*fromMazeCell);
            
            visited.push_back(nextCell);
            path.push(nextCell);
        }

    }
    
    pickStartAndFinish();
}

void DFSMaze::pickStartAndFinish(){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr_rows(0, maze_rows - 1);
    std::uniform_int_distribution<> distr_cols(0, maze_cols - 1); 
    
    start = {distr_rows(gen), distr_cols(gen)};
    do {
        finish = {distr_rows(gen), distr_cols(gen)};
    } while (start == finish);

}


