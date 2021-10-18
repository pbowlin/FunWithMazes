#include "DFSMaze.h"

#include <iostream>
#include <stack>
#include <random>

DFSMaze::DFSMaze(int rows, int cols) :
    Maze(rows, cols)
{

    initializeCells(rows, cols);
}


void DFSMaze::generateMaze(){
    std::cout << "Generating DFS Maze!" << std::endl;
    std::vector<MazeCell*> visited;
    std::stack<MazeCell*> path;
    
    visited.push_back(&(maze[0][0]));
    path.push(&(maze[0][0]));
    
    while(!path.empty()){
        MazeCell* currentCell = path.top();
        std::vector<MazeCell*> neighbors = getNeighbors(*currentCell);

        //std::cout << "Current cell: " << *currentCell << " -> " << neighbors << std::endl;
        
        std::vector<MazeCell*> unvisited;
        
        for(MazeCell* cell_ptr : neighbors){
            if(!cellVisited(visited, *cell_ptr)){
                unvisited.push_back(cell_ptr);
            }
        }
        
        //std::cout << "\tUnvisited: " << unvisited << std::endl;
        
        if(unvisited.empty()){
            path.pop();
        } else {
            MazeCell* nextCell = selectNextCell(unvisited);
            //std::cout << "\t" << *nextCell << std::endl;
            currentCell->addPassage(*nextCell);
            nextCell->addPassage(*currentCell);
            
            visited.push_back(nextCell);
            path.push(nextCell);
        }

    }
    
    pickStartAndFinish();
}

bool DFSMaze::cellVisited(const std::vector<MazeCell*>& visited, const MazeCell& cell){
    for(MazeCell* mc : visited){
        if (cell == *mc) 
            return true;
    }
    return false;
}

MazeCell* DFSMaze::selectNextCell(std::vector<MazeCell*>& unvisited){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, unvisited.size() - 1); // define the range
    int index = distr(gen);
    //std::cout << "\tIndex selected: " << index << " || " << unvisited << " || " << *unvisited[index] << std::endl;
    return unvisited[index];
}
