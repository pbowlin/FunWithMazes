#pragma once

#include "Maze.h"

#include <memory>
#include <string>


class MazeFactory {
    
    public:
        static std::unique_ptr<Maze> createMaze(); 
        static std::unique_ptr<Maze> createMazeByType(std::string maze_type, int num_rows, int num_cols);
        static void decideMazeSolver(const Maze& maze);
    
    private:
        MazeFactory();
        
    
};