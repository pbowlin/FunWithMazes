#include "MazeFactory.h"
#include "DFSMaze.h"
#include "PrimsMaze.h"
#include "WilsonsMaze.h"
#include "CustomMaze.h"
#include "Timer.h"

#include <iostream>
#include <string>

std::unique_ptr<Maze> MazeFactory::createMaze() {
    int maze_type, num_rows, num_cols;
    bool read_maze_from_image, freehand_maze;
    std::string user_input;
    std::string maze_image_path = "./MazeImages/TestMazes/AsGraph/15x15_SmallObstacle.png"; // false
    // std::string maze_image_path = "./MazeImages/TestMazes/Freehand/20x20AStarWikiCloneSimpleThin.png"; // true
    // std::string maze_image_path = "./MazeImages/TestMazes/Freehand/TinySpiralMaze.png"; // true
    // std::string maze_image_path = "./MazeImages/TestMazes/Freehand/TinyMaze.png"; // true

    std::cout << "\nWhat would you like to do?\n\t(0) - Generate a random maze\n\t(1) - Read in a maze from an image" << std::endl;
    
    std::getline(std::cin, user_input);
    read_maze_from_image = std::stoi(user_input);
    
    if(read_maze_from_image){
        std::cout << "\nWhat type of maze image is it?\n\t(0) - Maze drawn as graph\n\t(1) - Freehand drawn maze" << std::endl;
        std::getline(std::cin, user_input);
        freehand_maze = std::stoi(user_input);
        std::cout << "\nPlease enter the full pathname to the image (or enter \"def\" for the default image.)" << std::endl;
        std::getline(std::cin, user_input);
        
        if(user_input != "def"){
            maze_image_path = user_input;
        }
        
        maze_type = 4;
    } else {
        std::cout << "What type of maze would you like to create?\n\t(1) - Depth First Maze\n\t\tBiased towards long winding corridors.\n\t(2) - Prim's Maze\n\t\tBiased towards frequent and short dead ends.\n\t(3) - Wilson's Maze\n\t\tUnbiased. Generates uniformly between long corridors and short dead ends." << std::endl;
        std::cin >> maze_type;
        
        std::cout << "How many rows would you like your maze to have?" << std::endl;
        std::cin >> num_rows;
        
        std::cout << "How many columns would you like your maze to have?" << std::endl;
        std::cin >> num_cols;
    }

    std::unique_ptr<Maze> maze;
    if(maze_type == 1) {
        maze = std::make_unique<DFSMaze>(num_rows, num_cols); 
    }else if (maze_type == 2) {
        maze = std::make_unique<PrimsMaze>(num_rows, num_cols);
    } else if (maze_type == 3) {
        maze = std::make_unique<WilsonsMaze>(num_rows, num_cols);
    } else if(maze_type == 4) {
        maze = std::make_unique<CustomMaze>(maze_image_path, freehand_maze);
    } else {
        // Default Maze
        std::cout << "Default maze (depth first) generator is being used." << std::endl;
        maze = std::make_unique<DFSMaze>(num_rows, num_cols);
    }
    
    Timer maze_timer("Maze generation");
    maze->generateMaze();
    return maze;

}

// Creates a maze without needing user input. (Used for benchmarking)
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

