#include "MazeUtils.h"
#include "Timer.h"
#include "MazeFactory.h"

#include <memory>
#include <iostream>
#include <fstream>

namespace mazeBenchmarking {
    void benchmarkMaze(std::string maze_type, int rows, int cols, int bench_trials){
        float total_time = 0.f;
        float fastest_trial = 999999.f;
        float slowest_trial = 0.f;
        std::cout << "Benchmarking maze generation time..." << std::endl;
        Timer benchmark_timer("Benchmarking procedure");
        for(int i = 1; i <= bench_trials; i++){
    
            std::unique_ptr<Maze> maze = MazeFactory::createMazeByType(maze_type, rows, cols);
            Timer trial_timer("Benchmark trial", false);
            (*maze).generateMaze();
            float trial_time = trial_timer.getTotalDuration();
            total_time += trial_time;
            if (trial_time < fastest_trial)
                fastest_trial = trial_time;
            if (trial_time > slowest_trial)
                slowest_trial = trial_time;
                
            if(i % 50 == 0 || i == bench_trials) {
                std::cout << "\t" << i << "/" << bench_trials << " trials complete." << std::endl;
            }
            
        }
        
        std::cout << "average trial time: " << total_time/bench_trials << std::endl;
        std::cout << "Fastest trial: " << fastest_trial << std::endl;
        std::cout << "Slowest trial: " << slowest_trial << std::endl;
    }
}

namespace mazeUtils {
    
    
    void drawMazeToConsole(const std::vector<std::vector<std::string>>& maze_display){
    
        // std::vector<std::vector<std::string>> maze_display;
        // maze.generateMazeDisplay(maze_display);
        //Maze::display_maze(maze_display);
        
        // Draw the maze to the console
        for(const std::vector<std::string>& row_display : maze_display) {
            for(const std::string& maze_element : row_display) {
                std::cout << maze_element;
            }
            std::cout << std::endl;
        }
        
    }
    
    // Saves the current maze to a text file. Currently does not work because of linux color formatting in display string.
    void saveMazeAsTxt(const std::vector<std::vector<std::string>>& maze_display){
        
        // std::vector<std::vector<std::string>> maze_display;
        // maze.generateMazeDisplay(maze_display);
        
        std::ofstream maze_file;
        maze_file.open("MazeFile.txt");
        
        for(const std::vector<std::string>& row_display : maze_display) {
            for(const std::string& maze_element : row_display) {
                maze_file << maze_element;
            }
            maze_file << std::endl;
        }
        
        maze_file.close();
        
    }
}