
#include "MazeCell.h"
#include "DFSMaze.h"
#include "WilsonsMaze.h"
#include "PrimsMaze.h"
#include "Timer.h"
#include "MazeSolver.h"

#include <iostream>

int main(){
    
    int rows = 20;
    int cols = 50;

    std::cout << "================================ DFS MAZE ================================" << std::endl;
    DFSMaze dfsm(rows, cols); 
    Timer dfsmaze_timer("DFS Maze");
    dfsm.generateMaze();
    std::cout << "Generating maze took: " << dfsmaze_timer << std::endl;
    //dfsm.drawMaze();
    //m.listCellsWithPassages();
    MazeSolver::solveMaze(dfsm, &CellCoords::manhattan_distance, &MazeSolver::AStarSolver);
    
    std::cout << "================================ WILSON'S MAZE ================================" << std::endl;
    WilsonsMaze wm(rows, cols);
    Timer wmaze_timer("Wilson's Maze");
    wm.generateMaze();
    std::cout << "Generating maze took: " << wmaze_timer << std::endl;
    //wm.drawMaze();
    MazeSolver::solveMaze(wm, &CellCoords::manhattan_distance, &MazeSolver::AStarSolver);
    
    std::cout << "================================ PRIM'S MAZE ================================" << std::endl;
    PrimsMaze pm(rows, cols); 
    Timer pmaze_timer("Prims Maze");
    pm.generateMaze();
    std::cout << "Generating maze took: " << pmaze_timer << std::endl;
    //pm.drawMaze();
    MazeSolver::solveMaze(pm, &CellCoords::manhattan_distance, &MazeSolver::AStarSolver);
    
    
    //MazeSolver::AStarSolver(pm.getMaze());

    
}