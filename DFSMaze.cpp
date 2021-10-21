#include "DFSMaze.h"

#include <iostream>
#include <stack>
#include <random>

DFSMaze::DFSMaze(int rows, int cols) :
    Maze(rows, cols)
{

    Maze::initializeCells(rows, cols);
}

// TODO: Try changing all the MazeCell containers to be CellCoords containers instead.
// Maybe that will have much faster copying?
void DFSMaze::generateMaze(){
    std::cout << "Generating DFS Maze!" << std::endl;
    std::vector<CellCoords> visited;
    std::stack<CellCoords> path;
    
    visited.push_back(maze[0][0].getCellCoords());
    path.push(maze[0][0].getCellCoords());
    
    while(!path.empty()){
        CellCoords currentCell = path.top();
        std::vector<CellCoords> neighbors = Maze::getNeighbors(currentCell.row, currentCell.col);
        
        std::vector<CellCoords> unvisited;
        
        for(CellCoords cell : neighbors){
            if(!cellVisited(visited, cell)){
                unvisited.push_back(cell);
            }
        }
        
        if(unvisited.empty()){
            path.pop();
        } else {
            CellCoords nextCell = selectNextCell(unvisited);
 
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

bool DFSMaze::cellVisited(const std::vector<CellCoords>& visited, const CellCoords& cell){
    for(CellCoords cc : visited){
        if (cell == cc) 
            return true;
    }
    return false;
}


CellCoords DFSMaze::selectNextCell(std::vector<CellCoords>& unvisited){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, unvisited.size() - 1); // define the range
    int index = distr(gen);
    //std::cout << "\tIndex selected: " << index << " || " << unvisited << " || " << *unvisited[index] << std::endl;
    return unvisited[index];
}
