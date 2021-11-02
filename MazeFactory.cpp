#include "MazeFactory.h"
#include "DFSMaze.h"
#include "PrimsMaze.h"
#include "WilsonsMaze.h"

#include <iostream>

std::unique_ptr<Maze> MazeFactory::createMaze() {
    int maze_type, num_rows, num_cols;
    
    std::cout << "What type of maze would you like to create?\n\t(1) - Depth First Maze\n\t(2) - Prim's Maze\n\t(3) - Wilson's Maze" << std::endl;
    std::cin >> maze_type;
    
    std::cout << "How many rows would you like your maze to have?" << std::endl;
    std::cin >> num_rows;
    
    std::cout << "How many columns would you like your maze to have?" << std::endl;
    std::cin >> num_cols;
    

    if(maze_type == 1) {
        return std::make_unique<DFSMaze>(num_rows, num_cols); 
    }else if (maze_type == 2) {
        return std::make_unique<PrimsMaze>(num_rows, num_cols);
    } else if (maze_type == 3) {
        return std::make_unique<WilsonsMaze>(num_rows, num_cols);
    } else {
        // Default Maze
        std::cout << "Default maze (depth first) generator is being used." << std::endl;
        return std::make_unique<DFSMaze>(num_rows, num_cols);
    }

}

// Creates a Wilson's maze with 25 rows and 30 columns.
std::unique_ptr<Maze> MazeFactory::createMazeByType(std::string maze_type, int num_rows, int num_cols) {
    if(maze_type == "DFS") {
        return std::make_unique<DFSMaze>(num_rows, num_cols); 
    }else if (maze_type == "Prims") {
        return std::make_unique<PrimsMaze>(num_rows, num_cols);
    } else if (maze_type == "Wilsons") {
        return std::make_unique<WilsonsMaze>(num_rows, num_cols);
    } else {
        // Default Maze
        std::cout << "Default maze (depth first) generator is being used." << std::endl;
        return std::make_unique<DFSMaze>(num_rows, num_cols);
    }
}