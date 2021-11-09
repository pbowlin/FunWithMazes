#include "WilsonsMaze.h"

#include <iostream>
#include <random>
#include <unordered_set>
#include <list>
#include <vector>
#include <random>
#include <algorithm>

WilsonsMaze::WilsonsMaze(int rows, int cols) :
    Maze(rows, cols)
{
    type = "WilsonsMaze";
    Maze::initializeCells(rows, cols);
}


void WilsonsMaze::generateMaze(){
    
    // First we initialize a container of cells not yet in the maze.
    std::unordered_set<CellCoords> cells_not_in_maze;
    for(int i = 0; i < maze_rows; ++i){
        for(int j = 0; j < maze_cols; ++j){
            cells_not_in_maze.insert({i,j});
        }
    }
    
    // Set the first cell in the container (which is a random cell) 
    // to be the initial cell within the maze
    cells_not_in_maze.erase(cells_not_in_maze.begin());
    
    // We perform random walks from the remaining cells until
    // every cell is in the maze
    while(!cells_not_in_maze.empty()){
        CellCoords current_coords = *cells_not_in_maze.begin();

        std::list<CellCoords> path = performRandomWalk(current_coords, cells_not_in_maze);

        addPathToMaze(path, cells_not_in_maze);
    }
    
    Maze::pickStartAndFinish();
}

// This will perform a random walk from the start cell until it reaches a cell that is in the maze
std::list<CellCoords> WilsonsMaze::performRandomWalk(CellCoords start_coords, const std::unordered_set<CellCoords>& cells_not_in_maze){
    std::list<CellCoords> path { start_coords };
    CellCoords current_coords = start_coords;
    CellCoords previous_coords = start_coords; 

    while(true){
        std::vector<CellCoords> neighbors = Maze::getNeighbors(current_coords.row, current_coords.col);
        
        // Now remove the neighbor from which we just came... so we don't immediately backtrack. But only if we still have somewhere to go.
        if(neighbors.size() > 1)
            neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), previous_coords), neighbors.end());

        CellCoords next_coords = neighbors[Maze::randomlySelectNextIndex(neighbors.size())];

        //Check to see if the new cell connects to an already-built portion of the maze
        if(cells_not_in_maze.count(next_coords) == 0){
            // We have connected to the existing maze so add the last cell and return the path
            path.push_back(next_coords);
            return path;
        }
        
        // Check if the next cell is already in the path, creating a loop
        auto path_loop_start = std::find(path.begin(), path.end(), next_coords);
        if(path_loop_start != path.end()){
            // The next cell is in the path, creating a loop.
            // Remove all the cells that are in the loop.
            path.erase(++path_loop_start, path.end());
        } else {
            // No loop so add the next cell to the path
            path.push_back(next_coords);
            
        }
        
        previous_coords = current_coords;
        current_coords = next_coords;
    }

}

void WilsonsMaze::addPathToMaze(const std::list<CellCoords>& path, std::unordered_set<CellCoords>& cells_not_in_maze){
    auto cell_A_iter = path.begin();
    auto cell_B_iter = ++path.begin();
    while(cell_B_iter != path.end()){
        Maze::maze[(*cell_A_iter).row][(*cell_A_iter).col].addPassage(Maze::maze[(*cell_B_iter).row][(*cell_B_iter).col]);
        Maze::maze[(*cell_B_iter).row][(*cell_B_iter).col].addPassage(Maze::maze[(*cell_A_iter).row][(*cell_A_iter).col]);
        
        cells_not_in_maze.erase(*cell_A_iter);
        
        ++cell_A_iter;
        ++cell_B_iter;
    }
}


