
#include "MazeCell.h"
#include "DFSMaze.h"
#include "WilsonsMaze.h"
#include "PrimsMaze.h"
#include "Timer.h"

#include <iostream>

int main(){

    std::cout << "================================ DFS MAZE ================================" << std::endl;
    DFSMaze dfsm(20, 50); 
    Timer dfsmaze_timer("DFS Maze");
    dfsm.generateMaze();
    std::cout << "Generating maze took: " << dfsmaze_timer << std::endl;
    dfsm.drawMaze();
    //m.listCellsWithPassages();
    
    std::cout << "================================ WILSON'S MAZE ================================" << std::endl;
    WilsonsMaze wm(20, 50);
    Timer wmaze_timer("Wilson's Maze");
    wm.generateMaze();
    std::cout << "Generating maze took: " << wmaze_timer << std::endl;
    wm.drawMaze();
    
    std::cout << "================================ PRIM'S MAZE ================================" << std::endl;
    PrimsMaze pm(20, 50); 
    Timer pmaze_timer("Prims Maze");
    pm.generateMaze();
    std::cout << "Generating maze took: " << pmaze_timer << std::endl;
    pm.drawMaze();

    
}