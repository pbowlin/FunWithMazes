#include "Maze.h"

#include <iostream>
#include <random>

Maze::Maze(int rows, int cols) : 
    maze_rows(rows),
    maze_cols(cols) 
{
        
}


// Initializes each cell in the maze vector
void Maze::initializeCells(int rows, int cols){
    std::cout << "Initializing cells!" << std::endl;
    
    for(int i = 0; i < rows; ++i){
        std::vector<MazeCell> new_row;
        for(int j = 0; j < cols; ++j){
            new_row.push_back(MazeCell(i,j));
        }
        maze.push_back(new_row);
        new_row.clear();
    }
 
}


std::vector<MazeCell*> Maze::getNeighbors(MazeCell& mc){
    CellCoords coords = mc.getCellCoords();
    std::vector<MazeCell*> neighbors;
    
    if(coords.row > 0 ){
        neighbors.push_back(&(maze[coords.row - 1][coords.col]));
    }
    
    if(coords.row < maze_rows - 1 ){
        neighbors.push_back(&(maze[coords.row + 1][coords.col]));
    }
    
    if(coords.col > 0 ){
        neighbors.push_back(&(maze[coords.row][coords.col - 1]));
    }
    
    if(coords.col < maze_cols - 1 ){
        neighbors.push_back(&(maze[coords.row][coords.col + 1]));
    }
    
    return neighbors;
}

void Maze::listCells() {
    for(int row = 0; row < maze_rows; ++row){
        for (int col = 0; col < maze_cols; ++col){
            std::cout << maze[row][col] << " -> ";
            std::cout << (maze[row][col].getPassages()) << std::endl;
        }
    }
}

void Maze::drawMaze(){
    std::vector<std::vector<std::string>> maze_display;
    
    // Initialize maze to be entirely walls
    for(int i = 0; i < maze_rows * 2 + 1; ++i){
        std::vector<std::string> maze_row_display(maze_cols * 2 + 1, "██");
        maze_display.push_back(maze_row_display);
    }
    
    // Iterate over the maze and knock out walls for every room and passage
    for(int i = 0; i < maze_rows; ++i){
        for(int j = 0; j < maze_cols; ++j){
            maze_display[i*2+1][j*2+1] = "  "; // All rooms are open
            
            // Now check if we need to knock out any walls to the neighboring rooms
            // Because we iterate left to right, top to bottom we only 
            // need to check the cells to the right and below the current cell.
            if(maze[i][j].isConnected(MazeCell(i, j+1))){
                maze_display[i*2+1][j*2+2] = "  ";
            }
            
            if(maze[i][j].isConnected(MazeCell(i+1, j))){
                maze_display[i*2+2][j*2+1] = "  ";
            }
        }
    }
    
    // Knock out the walls to the start and finish cells.
    maze_display[start.row*2+1][0] = "  ";
    maze_display[finish.row*2+1][2*maze_cols] = "  ";
    
    // Draw the maze to the console
    for(const std::vector<std::string>& row_display : maze_display) {
        for(const std::string& maze_element : row_display) {
            std::cout << maze_element;
        }
        std::cout << std::endl;
    }
}

void Maze::pickStartAndFinish(){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, maze_rows - 1); // define the range
    int start_row = distr(gen);
    int finish_row = distr(gen);
    
    start = {start_row, 0};
    finish = {finish_row, maze_cols - 1};
}
