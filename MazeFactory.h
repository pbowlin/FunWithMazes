#pragma once

#include "Maze.h"


class MazeFactory {
    
    public:
        static Maze* createMaze();    
    
    private:
        MazeFactory();
        
    
};