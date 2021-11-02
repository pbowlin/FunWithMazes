
#include "Timer.h"
#include "MazeSolver.h"
#include "MazeFactory.h"

#include <iostream>
#include <memory>
#include <string>

void benchmarkMaze(std::string maze_type, int rows, int cols, int bench_trials){
    float total_time = 0.f;
    float fastest_trial = 999999.f;
    float slowest_trial = 0.f;
    std::cout << "Benchmarking maze generation time..." << std::endl;
    Timer benchmark_timer("Benchmarking procedure");
    for(int i = 1; i <= bench_trials; i++){
        
        if(i % 50 == 0 || i == bench_trials) {
            std::cout << "\t" << i << "/" << bench_trials << " trials complete." << std::endl;
        }
        
        std::unique_ptr<Maze> maze = MazeFactory::createMazeByType(maze_type, rows, cols);
        Timer trial_timer("Benchmark trial", false);
        (*maze).generateMaze();
        float trial_time = trial_timer.getTotalDuration();
        total_time += trial_time;
        if (trial_time < fastest_trial)
            fastest_trial = trial_time;
        else if (trial_time > slowest_trial)
            slowest_trial = trial_time;
        
    }
    
    std::cout << "average trial time: " << total_time/bench_trials << std::endl;
    std::cout << "Fastest trial: " << fastest_trial << std::endl;
    std::cout << "Slowest trial: " << slowest_trial << std::endl;
}

int main(){

    {
        std::unique_ptr<Maze> maze = MazeFactory::createMaze();
        Timer maze_timer("Custom Maze");
        (*maze).generateMaze();
        std::cout << "Generating maze took: " << maze_timer << std::endl;
        MazeSolver::solveMaze(*maze, &CellCoords::euclidean_distance, &MazeSolver::AStarSolver);
    }
    
    
    //benchmarkMaze("Prims", 25, 30, 20);
    
}