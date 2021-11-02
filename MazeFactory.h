#pragma once

#include "Maze.h"

#include <memory>


class MazeFactory {
    
    public:
        static std::unique_ptr<Maze> createMaze();    
    
    private:
        MazeFactory();
        
    
};