
#include "Timer.h"
#include "MazeSolver.h"
#include "MazeFactory.h"
#include "MazeUtils.h"

#include <iostream>
#include <memory>
#include <string>


int main(){

    {
        std::unique_ptr<Maze> maze = MazeFactory::createMaze();
        Timer maze_timer("Custom Maze");
        (*maze).generateMaze();
        std::cout << "Generating maze took: " << maze_timer << std::endl;
        //std::vector<std::vector<std::string>> solution_display;
        //(*maze).generateMazeDisplay(solution_display);
        auto[solution, solution_display] = MazeSolver::solveMaze(*maze, &CellCoords::euclidean_distance, &MazeSolver::AStarSolver);
        //mazeUtils::drawMazeToConsole(solution_display);
        mazeUtils::saveMazeAsImg(*maze, solution_display, 1);
        
        //(*maze).saveMaze();
    }
    
     
    //mazeBenchmarking::benchmarkMaze("Wilsons", 100, 100, 1);
    
}