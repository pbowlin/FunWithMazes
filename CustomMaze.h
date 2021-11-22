#pragma once
/*
Generic custom maze that was read in from an image
*/

#include "Maze.h"

#include <string>

class CustomMaze : public Maze {
    public:
        CustomMaze(std::string maze_filepath_in, bool user_drawn);
        void generateMaze() override;
        

    private:
        void loadMazeFromPNG();
        bool convertImageToMazeDisplay(std::string ppm_filepath, std::vector<std::vector<std::string>>& maze_display);
        void convertMazeDisplayToMaze(std::vector<std::vector<std::string>>& maze_display);
        
        void loadUserDrawnMaze();
        
        void setStart(CellCoords new_start);
        void setFinish(CellCoords new_finish);
    
        std::string maze_filepath;
        bool user_drawn_maze;
        
        
};