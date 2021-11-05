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
    
    void saveMazeAsImg(const Maze& maze, const std::vector<std::vector<std::string>>& maze_display){
        std::ofstream out("ColorMaze.ppm", std::ios::binary | std::ios::out | std::ios::trunc);
        auto[num_rows, num_cols] = maze.getSize();
        num_rows = num_rows*2 + 1;
        num_cols = num_cols*2 + 1;
        
        std::string header = "P3\n" + std::to_string(num_cols) + " " + std::to_string(num_rows) + "\n255\n";
        out << header;
        
        for(const auto& row : maze_display){
            
            for(const auto& elem : row) {
                std::string elem_color;
                
                // Determine the image pixel color based on the type of maze element we're drawing.
                if(elem == Maze::DisplayCharacters::wall) {
                    elem_color = "0 0 0\n"; // Walls are black
                } else if(elem == Maze::DisplayCharacters::room ||
                            elem == Maze::DisplayCharacters::vert_passage ||
                            elem == Maze::DisplayCharacters::horiz_passage){
                    elem_color = "255 255 255\n"; // Rooms and passages are white
                } else if(elem == Maze::DisplayCharacters::solution_path){
                    elem_color = "0 255 0\n"; // Solution path is green
                } else if(elem == Maze::DisplayCharacters::solution_touched){
                    elem_color = "0 0 200\n"; // Solution path is blue
                } else if(elem == Maze::DisplayCharacters::start_room){
                    elem_color = "255 0 255\n"; // Start room is purple
                } else if(elem == Maze::DisplayCharacters::finish_room){
                    elem_color = "255 0 0\n"; // Finish room is red
                }
                
                out << elem_color;
            }
            
        }
        
        out.close();
        
        // Now convert the file from .ppm into more normal .png format and then remove the .ppm file.
        system("convert ColorMaze.ppm ColorMaze.png");
        system("rm ColorMaze.ppm");
    }
}