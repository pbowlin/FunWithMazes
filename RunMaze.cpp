
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
        std::vector<std::vector<std::string>> maze_display;
        ////(*maze).generateMazeDisplay(maze_display);
        ////mazeUtils::drawMazeToConsole(maze_display);
        auto[solution_Astar, solution_display_Astar] = MazeSolver::solveMaze(*maze, &MazeSolver::AStarSolver, &CellCoords::euclidean_distance);
        mazeUtils::saveMazeAsImg(*maze, solution_display_Astar, 1, "AStar");
        //mazeUtils::drawMazeToConsole(solution_display_Astar);
        auto[solution_trem, solution_display_trem] = MazeSolver::solveMaze(*maze, &MazeSolver::TremauxSolver);
        //mazeUtils::drawMazeToConsole(solution_display_trem);
        mazeUtils::saveMazeAsImg(*maze, solution_display_trem, 1, "Tremaux");

    }
    
    
    //mazeBenchmarking::benchmarkMaze("Wilsons", 100, 100, 1);
}