#include "PrimsMaze.h"

#include <iostream>
#include <unordered_set>
#include <vector>
#include <utility>


PrimsMaze::PrimsMaze(int rows, int cols) :
    Maze(rows, cols)
{
    type = "PrimsMaze";
    Maze::initializeCells(rows, cols);
}

void PrimsMaze::generateMaze(){
    
    // For now just start at the first cell in the maze
    CellCoords initial_cell {0,0};
    std::unordered_set<CellCoords> visited {initial_cell};
    
    // Add the walls of the first cell to a list
    std::vector<Wall> walls;
    std::vector<Wall> initial_walls = getWalls(initial_cell);
    walls.insert(walls.end(), initial_walls.begin(), initial_walls.end());
    
    while(!walls.empty()){
        int random_wall_idx = Maze::randomlySelectNextIndex(walls.size());
        Wall* random_wall = &walls[random_wall_idx];
        
        // Check to see if both rooms have been visited
        if(visited.count(random_wall->side_A) + visited.count(random_wall->side_B) != 2){
            // Get the unvisited room
            CellCoords unvisited_side = visited.count(random_wall->side_A) == 0 ? random_wall->side_A : random_wall->side_B;
            
            // Add passages between the rooms (knock down the wall)
            MazeCell* room_A = &(Maze::maze[(random_wall->side_A).row][(random_wall->side_A).col]);
            MazeCell* room_B = &(Maze::maze[(random_wall->side_B).row][(random_wall->side_B).col]);
            
            room_A->addPassage(*room_B);
            room_B->addPassage(*room_A);
            
            // Mark the unvisited cell as visited
            visited.insert(unvisited_side);
            
            // Add the new room's walls to the list (this must happen after the passages have been created
            // or else duplicate walls will be entered)
            std::vector<Wall> new_walls = getWalls(unvisited_side);
            walls.insert(walls.end(), new_walls.begin(), new_walls.end());
        }
        
        // Remove the random wall from the list of walls
        walls[random_wall_idx] = std::move(walls.back()); // By moving the last element into the element we are going to remove we
                                                          // can then just pop the last element and get constant time vector removal!
        walls.pop_back();
    }
    
    Maze::pickStartAndFinish();
    
    
}


std::vector<Wall> PrimsMaze::getWalls(const CellCoords& cell_coords){
    std::vector<Wall> walls;
    std::vector<CellCoords> neighbors_coords = Maze::getNeighbors(cell_coords.row, cell_coords.col);
    
    MazeCell* cell = &(Maze::maze[cell_coords.row][cell_coords.col]);
    for(const CellCoords& neighbor_coords : neighbors_coords) {
        MazeCell* neighbor = &(Maze::maze[neighbor_coords.row][neighbor_coords.col]);
        
        // Check the actual maze for walls between each neighbor and this cell
        if(!(*cell).isConnected(*neighbor)){
            walls.push_back( {cell_coords, neighbor_coords} );
        }
    }
    
    return walls;
}