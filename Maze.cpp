#include "Maze.h"

#include <iostream>
#include <random>
#include <cmath>

Maze::Maze(int rows, int cols) : 
    maze_rows(rows),
    maze_cols(cols) 
{
}


// Initializes each cell in the maze vector
void Maze::initializeCells(int rows, int cols){
    
    for(int i = 0; i < rows; ++i){
        std::vector<MazeCell> new_row;
        for(int j = 0; j < cols; ++j){
            new_row.push_back(MazeCell(i,j));
        }
        maze.push_back(new_row);
        new_row.clear();
    }
 
}

// Neighbors are defined as cells orthagonal to a given cell... regardless of whether or not there is a wall between them.
std::vector<CellCoords> Maze::getNeighbors(int row, int col){
    std::vector<CellCoords> neighbors;
    
    if(row > 0 ){
        neighbors.push_back({row - 1, col});
    }
    
    if(row < maze_rows - 1 ){
        neighbors.push_back({row + 1, col});
    }
    
    if(col > 0 ){
        neighbors.push_back({row, col - 1});
    }
    
    if(col < maze_cols - 1 ){
        neighbors.push_back({row, col + 1});
    }
    
    return neighbors;
}

void Maze::listCellsWithPassages() const {
    for(int row = 0; row < maze_rows; ++row){
        for (int col = 0; col < maze_cols; ++col){
            std::cout << maze[row][col] << " -> ";
            for(auto cc : maze[row][col].getPassages()){
                std::cout << cc << ", ";
            }
            std::cout << std::endl;
        }
    }
}

const std::vector<std::vector<MazeCell>>& Maze::getMaze() const {
    return maze;
}

CellCoords Maze::getStart() const{
    return start;
}

CellCoords Maze::getFinish() const{
    return finish;
}

std::tuple<int, int> Maze::getSize() const {
    return {maze_rows, maze_cols};
}

std::string Maze::getType() const {
    return type;
}

void Maze::generateMazeDisplay(std::vector<std::vector<std::string>>& maze_display, const MazeSolutionDisplayElements* const solution_elems_ptr) const {
    
    // Initialize maze to be entirely walls
    for(int i = 0; i < maze_rows * 2 + 1; ++i){
        std::vector<std::string> maze_row_display(maze_cols * 2 + 1, Maze::DisplayCharacters::wall);
        maze_display.push_back(maze_row_display);
    }
    
    // Iterate over the maze and knock out walls for every room and passage
    for(int i = 0; i < maze_rows; ++i){
        for(int j = 0; j < maze_cols; ++j){
            maze_display[i*2+1][j*2+1] = Maze::DisplayCharacters::room; // All rooms are open
            
            // Now check if we need to knock out any walls to the neighboring rooms.
            // Because we iterate left to right, top to bottom we only 
            // need to check the cells to the right and below the current cell.
            if(maze[i][j].isConnected({i, j+1})){
                maze_display[i*2+1][j*2+2] = Maze::DisplayCharacters::horiz_passage;
            }
            
            if(maze[i][j].isConnected({i+1, j})){
                maze_display[i*2+2][j*2+1] = Maze::DisplayCharacters::vert_passage;
            }
        }
    }
    
    if(solution_elems_ptr){
        for(const CellCoords& touch : solution_elems_ptr->touched){
            maze_display[touch.row*2 + 1][touch.col*2 + 1] = Maze::DisplayCharacters::solution_touched;
        }
        
        for(const CellCoords& step : solution_elems_ptr->solution){
            maze_display[step.row*2 + 1][step.col*2 + 1] = Maze::DisplayCharacters::solution_path;
        }
    }
    
    // Notate the start and finish cells
    maze_display[start.row*2+1][start.col*2+1] = Maze::DisplayCharacters::start_room;
    maze_display[finish.row*2+1][finish.col*2+1] = Maze::DisplayCharacters::finish_room;

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

bool Maze::cellVisited(const std::vector<CellCoords>& visited, const CellCoords& cell){
    for(CellCoords cc : visited){
        if (cell == cc) 
            return true;
    }
    return false;
}
