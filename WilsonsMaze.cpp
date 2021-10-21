#include "WilsonsMaze.h"

#include <iostream>
#include <random>
#include <unordered_set>
#include <list>
#include <vector>
#include <random>

WilsonsMaze::WilsonsMaze(int rows, int cols) :
    Maze(rows, cols)
{

    Maze::initializeCells(rows, cols);
}


void WilsonsMaze::generateMaze(){
    std::cout << "Generating DFS Maze!" << std::endl;
    
    /*
    1 Container to store cells that do not yet belong to a path
        Could randomly select from a container that has these nodes
        Could select in order from a container that was generated by randomly inserting the nodes
        I could also use this to check if the new node in the current path already belongs to the maze
    2 Container for the current path
        Order matters
        Inserting a new cell at every step
        Check maze's paths to see if cell already exists in the maze
        Checking to see if that cell is already in the current path
        Delete potentially many nodes and frequently (but the deletions are always from one starting point through to the end of the container)
        
    */
    
    // First we initialize a container of cells not yet in the maze.
    std::unordered_set<CellCoords> cells_not_in_maze;
    for(int i = 0; i < maze_rows; ++i){
        for(int j = 0; j < maze_cols; ++j){
            cells_not_in_maze.insert({i,j});
        }
    }
    
    for(auto& cc : cells_not_in_maze){
        std::cout << cc << std::endl;
    }
    
    // Set the first cell in the container (which is a random cell) 
    // to be the initial cell within the maze
    cells_not_in_maze.erase(cells_not_in_maze.begin());
    
    std::cout << "after initial cell: " << std::endl;
    // for(auto& mc : cells_not_in_maze){
    //     std::cout << mc << std::endl;
    // }
    std::cout << "myset's buckets contain:\n";
    for ( unsigned i = 0; i < cells_not_in_maze.bucket_count(); ++i) {
        std::cout << "bucket #" << i << " contains:";
        for ( auto local_it = cells_not_in_maze.begin(i); local_it!= cells_not_in_maze.end(i); ++local_it )
            std::cout << " " << *local_it;
        std::cout << std::endl;
    }
    std::cout << "Load factor: " << cells_not_in_maze.load_factor() << std::endl;
    
    // We perform random walks from the remaining cells until
    // every cell is in the maze
    while(!cells_not_in_maze.empty()){
        CellCoords current_coords = *cells_not_in_maze.begin();
        std::list<CellCoords> path = performRandomWalk(current_coords);
    }
    
}

std::list<CellCoords> WilsonsMaze::performRandomWalk(CellCoords start_coords){
    std::list<CellCoords> path;
    path.push_back(start_coords);
    CellCoords current_coords = start_coords;
    
    // while(true){
    //     std::vector<MazeCell*> neighbors = Maze::getNeighbors(current_cell.getCellCoords().row, current_cell.getCellCoords().col);
        
        
    // }
    
    return path;
}

// MazeCell WilsonsMaze::selectNextCell(const std::vector<MazeCell>& neighbors){
//     std::random_device rd; // obtain a random number from hardware
//     std::mt19937 gen(rd()); // seed the generator
//     std::uniform_int_distribution<> distr(0, neighbors.size() - 1); // define the range
//     int index = distr(gen);
//     return neighbors[index];
// }

