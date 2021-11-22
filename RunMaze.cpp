
#include "Timer.h"
#include "MazeSolver.h"
#include "MazeFactory.h"
#include "MazeUtils.h"
#include "CustomMaze.h"

#include <iostream>
#include <memory>
#include <string>

std::string mazeAnimation::solver_type = "";
bool mazeAnimation::create_animation = false;
int mazeAnimation::animation_frame_delay = 5; // Delay is in 1/100ths of a second

int main(){

    {

        mazeAnimation::create_animation = true;
        
        // Read in a custom maze from an image file and solve it.
        {
            // CustomMaze maze("./MazeImages/15x15_SmallObstacle.png");
            // maze.generateMaze();
    
            // auto[solution_Astar, solution_display_Astar] = MazeSolver::solveMaze(maze, &MazeSolver::AStarSolver_ALWAYS_ADD, &CellCoords::euclidean_distance);
            // mazeUtils::saveMazeAsImg(maze, solution_display_Astar, 1, mazeAnimation::solver_type);
            // auto[solution_Astart, solution_display_Astart] = MazeSolver::solveMaze(maze, &MazeSolver::AStarSolver_ONLY_ADD_NEW, &CellCoords::euclidean_distance);
            // mazeUtils::saveMazeAsImg(maze, solution_display_Astart, 1, mazeAnimation::solver_type);
            // auto[solution_Astarb, solution_display_Astarb] = MazeSolver::solveMaze(maze, &MazeSolver::AStarSolver_HEURISTIC_COST_ONLY, &CellCoords::euclidean_distance);
            // mazeUtils::saveMazeAsImg(maze, solution_display_Astarb, 1, mazeAnimation::solver_type);
            // auto[solution_trem, solution_display_trem] = MazeSolver::solveMaze(maze, &MazeSolver::TremauxSolver);
            // //mazeUtils::drawMazeToConsole(solution_display_trem);
            // mazeUtils::saveMazeAsImg(maze, solution_display_trem, 1, mazeAnimation::solver_type);
            
            // auto[height, width] = maze.getSize();
            // mazeAnimation::gif_filename = maze.getType() + "_" + std::to_string(height) + "x" + std::to_string(width) + ".gif";
            // std::cout << mazeAnimation::gif_filename << std::endl;
        }
        
        
        // Generate a maze based on user input and solve it.
        {
            std::unique_ptr<Maze> maze = MazeFactory::createMaze();
            Timer maze_timer("Custom Maze");
            (*maze).generateMaze();
            std::cout << "Generating maze took: " << maze_timer << std::endl;
            //std::vector<std::vector<std::string>> maze_display;
            ////(*maze).generateMazeDisplay(maze_display);
            ////mazeUtils::drawMazeToConsole(maze_display);
            // auto[solution_Astar, solution_display_Astar] = MazeSolver::solveMaze(*maze, &MazeSolver::AStarSolver_ALWAYS_ADD, &CellCoords::euclidean_distance);
            // mazeUtils::saveMazeAsImg(*maze, solution_display_Astar, 1, mazeAnimation::solver_type);
            // auto[solution_Astart, solution_display_Astart] = MazeSolver::solveMaze(*maze, &MazeSolver::AStarSolver_ONLY_ADD_NEW, &CellCoords::euclidean_distance);
            // mazeUtils::saveMazeAsImg(*maze, solution_display_Astart, 1, mazeAnimation::solver_type);
            // auto[solution_Astarb, solution_display_Astarb] = MazeSolver::solveMaze(*maze, &MazeSolver::AStarSolver_HEURISTIC_COST_ONLY, &CellCoords::euclidean_distance);
            // mazeUtils::saveMazeAsImg(*maze, solution_display_Astarb, 1, mazeAnimation::solver_type);
            //mazeUtils::drawMazeToConsole(solution_display_Astar);
            auto[solution_trem, solution_display_trem] = MazeSolver::solveMaze(*maze, &MazeSolver::TremauxSolver);
            //mazeUtils::drawMazeToConsole(solution_display_trem);
            mazeUtils::saveMazeAsImg(*maze, solution_display_trem, 1, mazeAnimation::solver_type);
        }

    }
    
    
    //mazeBenchmarking::benchmarkMaze("Wilsons", 100, 100, 1);
}