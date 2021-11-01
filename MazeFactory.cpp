#include "MazeFactory.h"

#include <iostream>

Maze* MazeFactory::createMaze() {
    int maze_type, num_rows, num_cols;
    
    std::cout << "What type of maze would you like to create?\n\t(1) - Depth First Maze\n\t(2) - Prim's Maze\n\t(3) - Wilson's Maze" << std::endl;
    std::cin >> maze_type;
    
    std::cout << "How many rows would you like your maze to have?" << std::endl;
    std::cin >> num_rows;
    
    std::cout << "How many columns would you like your maze to have?" << std::endl;
    std::cin >> num_cols;
    
    
    
}