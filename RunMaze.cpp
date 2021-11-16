
#include "Timer.h"
#include "MazeSolver.h"
#include "MazeFactory.h"
#include "MazeUtils.h"

#include <iostream>
#include <memory>
#include <string>

struct Allocations {
    uint32_t count = 0;
    uint32_t allocated = 0;
    uint32_t freed = 0;
    
    uint32_t currentUsage() { return allocated - freed;}
};

static Allocations alloc_metrics;

void* operator new(size_t size){
    //std::cout << "\tAllocating " << size << " bytes" << std::endl;
    alloc_metrics.allocated += size;
    alloc_metrics.count += 1;
    return malloc(size);
}

void operator delete(void* memory, size_t size){
    //std::cout << "\tFreeing " << size << " bytes" << std::endl;
    alloc_metrics.freed += size;
    free(memory);
}

int main(){

    {
        
        std::unique_ptr<Maze> maze = MazeFactory::createMaze();
        //std::cout << "Maze created: " << alloc_metrics.allocated << " bytes, allocations: " << alloc_metrics.count << std::endl;
        Timer maze_timer("Custom Maze");
        (*maze).generateMaze();
        //std::cout << "Maze generated: " << alloc_metrics.allocated << " bytes , allocations: " << alloc_metrics.count << std::endl;
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
        
        //(*maze).saveMaze();
        //std::cout << "Bytes in use: " << alloc_metrics.allocated << ", allocations: " << alloc_metrics.count << std::endl;
    }
    
    
    //mazeBenchmarking::benchmarkMaze("Wilsons", 100, 100, 1);
    std::cout << "Exiting program" << std::endl;
}