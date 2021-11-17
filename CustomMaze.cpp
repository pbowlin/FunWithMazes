#include "CustomMaze.h"
#include "MazeUtils.h"

#include <iostream>
#include <fstream>
#include <sstream>

CustomMaze::CustomMaze(std::string maze_filepath_in):
    Maze(0,0),
    maze_filepath(maze_filepath_in)
    {
        type = "CustomMaze";
    }
    
void CustomMaze::generateMaze(){
    loadMazeFromPNG(maze_filepath);
}

void CustomMaze::loadMazeFromPNG(std::string filepath) {
    // First convert the image to the workable .ppm ascii format.
    std::string ppm_filepath = filepath.substr(0, filepath.find(".png")) + ".ppm";
    std::string imageMagick_convert_command = "convert " + filepath + " -compress none " + ppm_filepath;
    system(imageMagick_convert_command.c_str());
    
    std::vector<std::vector<std::string>> maze_display;
    if(!convertImageToMazeDisplay(ppm_filepath, maze_display))
        return;
    
    convertMazeDisplayToMaze(maze_display);
    
}

bool CustomMaze::convertImageToMazeDisplay(std::string ppm_filepath, std::vector<std::vector<std::string>>& maze_display){
    // Open the NetBPM image and read in the maze size
    std::ifstream file(ppm_filepath);
    if((file.rdstate() & std::ifstream::failbit ) != 0){
        std::cout << "ERROR: Converted NetBPM file could not be opened. Check png filename. If the image filename is correct then an error occured during the ImageMagick conversion." << std::endl;
        return false;
    }
    
    std:: string str;
    int rows, cols;
    int i = 0;
    while(std::getline(file, str)){
        if(i == 1){
            std::stringstream stream(str);
            stream >> rows >> cols;
            break;
        }
        ++i;
    }
    
    if(rows % 2 == 0 || cols % 2 == 0){
        std::cout << "ERROR: Even size dimension. Maze image width and height must both be odd.\nCan't generate maze with given image." << std::endl; 
        return false;
    }

    std::getline(file, str); // Advance the line in the file past the max val line, to the start of pixel values
    
    // Read in the maze
    for(int i = 0; i < rows; ++i){
        std::vector<std::string> row;
        std::getline(file, str);
        std::stringstream stream(str);
        for(int j = 0; j < cols; ++j){
            int r,g,b;
            stream >> r >> g >> b;
            
            if((i == 0 || i == rows - 1 || j == 0 || j == cols - 1) 
                && (r != 0 || g != 0 || b != 0)){
                std::cout << "ERROR: The entire border of the image must be black pixels (walls). Pixel at (row: " << i << ", col: " << j << ") is not black.\nCan't generate maze with given image." << std::endl; 
                return false;
            }
            
            if(r == 0 && g == 0 && b == 0) {
                // Black pixel is a wall
                if(i % 2 == 1 && j % 2 == 1){
                    std::cout << "Warning: Pixels with an even row and col must be open rooms. Pixel at (row: " << i << ", col: " << j << ") is a wall. Making it a room instead." << std::endl;
                    row.push_back(Maze::DisplayCharacters::room);
                } else {
                   row.push_back(Maze::DisplayCharacters::wall); 
                }
                
            } else if (r == 255 && g == 0 && b == 0){
                // Red pixel is the finish
                row.push_back(Maze::DisplayCharacters::finish_room);
            } else if(r == 255 && g == 0 && b == 255){
                // Purple pixel is the start
                row.push_back(Maze::DisplayCharacters::start_room);
            } else if(r == 255 && g == 255 && b == 255){
                // Pixel is white so it could be a room or a passage
                if(i % 2 == 1 && j % 2 == 1){
                    // row and column are both odd, so its a room
                    row.push_back(Maze::DisplayCharacters::room);
                } else if (i % 2 == 1 && j % 2 == 0){
                    // row is odd and column is even, so its a horizontal passage
                    row.push_back(Maze::DisplayCharacters::horiz_passage);
                } else {
                    // row is even and column is odd, so its a vertical passage
                    // Note that we don't care about when row and col are both even, or both odd because that
                    // will always be a wall or a room, respectively. These are already dealt with above.
                    row.push_back(Maze::DisplayCharacters::vert_passage);
                }
            }
            
        }
        maze_display.push_back(row);
        
    }
    
    return true;
}

void CustomMaze::convertMazeDisplayToMaze(std::vector<std::vector<std::string>>& maze_display){
    Maze::initializeCells(maze_display.size()/2, maze_display[0].size()/2);
    
    // Set the maze size
    maze_rows = (int)(maze.size());
    maze_cols = (int)(maze[0].size());
    
    // Loop over the entire maze and at each cell check if there is a passage connecting it to the cell below it or the cell to its right
    for(int i = 0; i < maze_rows; ++i){
        for (int j = 0; j < maze_cols; ++j){
            int display_row = i * 2 + 1;
            int display_col = j * 2 + 1;
            
            if(maze_display[display_row][display_col] == Maze::DisplayCharacters::start_room){
                setStart({i,j});
            } else if (maze_display[display_row][display_col] == Maze::DisplayCharacters::finish_room){
                setFinish({i,j});
            }
            
            if(maze_display[display_row + 1][display_col] != Maze::DisplayCharacters::wall){
                // There is a passage between this cell and the cell below it, so add the passages to the cell
                MazeCell* currentCell = &(maze[i][j]);
                MazeCell* connectedCell = &(maze[i+1][j]);
                
                currentCell->addPassage(connectedCell->getCellCoords());
                connectedCell->addPassage(currentCell->getCellCoords());
            }
            
            if(maze_display[display_row][display_col + 1] != Maze::DisplayCharacters::wall){
                // There is a passage between this cell and the cell to its right, so add the passages to the cell
                MazeCell* currentCell = &(maze[i][j]);
                MazeCell* connectedCell = &(maze[i][j+1]);
                
                currentCell->addPassage(connectedCell->getCellCoords());
                connectedCell->addPassage(currentCell->getCellCoords());
            }
            
        }
    }
    
}

void CustomMaze::setStart(CellCoords new_start){
    start = new_start;
}

void CustomMaze::setFinish(CellCoords new_finish){
    finish = new_finish;
}