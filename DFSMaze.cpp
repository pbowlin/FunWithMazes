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
    std::cout << "Generating DFS Maze!" << std::endl;
    std::vector<MazeCell> visited;
    std::stack<MazeCell> path;
    
    visited.push_back(maze[0][0]);
    path.push(maze[0][0]);
    
    while(!path.empty()){
        MazeCell currentCell = path.top();
        int curr_row = currentCell.getCellCoords().row;
        int curr_col = currentCell.getCellCoords().col;
        std::vector<MazeCell> neighbors = Maze::getNeighbors(curr_row, curr_col);
        
        std::vector<MazeCell> unvisited;
        
        for(MazeCell cell : neighbors){
            if(!cellVisited(visited, cell)){
                unvisited.push_back(cell);
            }
        }
        
        if(unvisited.empty()){
            path.pop();
        } else {
            MazeCell nextCell = selectNextCell(unvisited);
 
            // Note that when adding passages we need to affect the mazecells that belong to the actual maze
            // not the copies of the maze's cells like we've created above. So get the actual maze's cells now.
            MazeCell* toMazeCell = &(Maze::maze[nextCell.getCellCoords().row][nextCell.getCellCoords().col]);
            MazeCell* fromMazeCell = &(Maze::maze[currentCell.getCellCoords().row][currentCell.getCellCoords().col]);
            
            // Add passages between the two cells of the actual maze
            fromMazeCell->addPassage(*toMazeCell);
            toMazeCell->addPassage(*fromMazeCell);
            
            visited.push_back(nextCell);
            path.push(nextCell);
        }

    }
    
    pickStartAndFinish();
}

bool DFSMaze::cellVisited(const std::vector<MazeCell>& visited, const MazeCell& cell){
    for(MazeCell mc : visited){
        if (cell == mc) 
            return true;
    }
    return false;
}


MazeCell DFSMaze::selectNextCell(std::vector<MazeCell>& unvisited){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, unvisited.size() - 1); // define the range
    int index = distr(gen);
    //std::cout << "\tIndex selected: " << index << " || " << unvisited << " || " << *unvisited[index] << std::endl;
    return unvisited[index];
}
