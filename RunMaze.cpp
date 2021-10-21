
#include "MazeCell.h"
#include "DFSMaze.h"
#include "WilsonsMaze.h"
#include "Timer.h"

#include <iostream>

int main(){
    
    MazeCell mc(3,5);
    mc.printCellCoords();
    
    DFSMaze m(20, 50); 
    Timer maze_timer("DFS Maze");
    m.generateMaze();
    std::cout << "Generating maze took: " << maze_timer << std::endl;
    m.drawMaze();
    //m.listCells();
    
    // WilsonsMaze m(5, 3);
    // Timer maze_timer("Wilson's Maze");
    // m.generateMaze();
    // std::cout << "Generating maze took: " << maze_timer << std::endl;
    // //m.drawMaze();
    
}