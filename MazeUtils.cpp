#include "MazeUtils.h"
#include "Timer.h"
#include "MazeFactory.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

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
    
    void saveMazeAsImg(const Maze& maze, const std::vector<std::vector<std::string>>& maze_display, int scale, std::string filename_suffix){
        std::string maze_type = maze.getType();
        auto[num_rows, num_cols] = maze.getSize();
        
        std::string filename_base = "./MazeImages/" + maze_type + "_" + std::to_string(num_rows) + "x" + std::to_string(num_cols) + "_" + filename_suffix;
        std::string filename_ppm = filename_base + ".ppm";
        std::string filename_png = filename_base + ".png";
        
        std::ofstream out(filename_ppm, std::ios::binary | std::ios::out | std::ios::trunc);
        
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
                } else if(elem == Maze::DisplayCharacters::room){
                    elem_color = "255 255 255\n"; // Rooms are white
                } else if (elem == Maze::DisplayCharacters::vert_passage ||
                            elem == Maze::DisplayCharacters::horiz_passage){
                    elem_color = "255 255 255\n"; // passages are white
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
        std::string conversion_command = "convert " + filename_ppm + " -scale " + std::to_string(scale * 100) + "% " + filename_png;
        //std::string conversion_command = "convert " + filename_ppm + " " + filename_png;
        std::string remove_command = "rm " + filename_ppm;
        system(conversion_command.c_str()); // convert image.ppm -scale 400x result.png
        system(remove_command.c_str());
    }
    
    int randomlySelectNextIndex(int num_options){
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, num_options - 1); // define the range
        //std::cout << "\tIndex selected: " << index << " || " << unvisited << " || " << *unvisited[index] << std::endl;
        return distr(gen);
    }
    
    
    void loadMazeFromPNG(std::string filepath) {
        // First convert the image to the workable .ppm ascii format.
        std::string ppm_filepath = filepath.substr(0, filepath.find(".png")) + ".ppm";
        std::string imageMagick_convert_command = "convert " + filepath + " -compress none " + ppm_filepath;
        std::cout << "ppm filepath: " << ppm_filepath << std::endl;
        std::cout << "Conversion command: " << imageMagick_convert_command << std::endl;
        system(imageMagick_convert_command.c_str());
        
        std::ifstream file(ppm_filepath);
        std:: string str;
        int rows, cols;
        int i = 0;
        while(std::getline(file, str)){
            if(i == 1){
                std::stringstream stream(str);
                stream >> rows >> cols;
                break;
            }
            ++i;
        }
        std::cout << rows << ", " << cols << std::endl;
        std::vector<std::vector<std::string>> maze_display;
        std::getline(file, str); // Advance the line in the file past the max val line, to the start of pixel values
        for(int i = 0; i < rows; ++i){
            std::vector<std::string> row;
            std::getline(file, str);
            std::stringstream stream(str);
            std::cout << str << std::endl;
            for( int j = 0; j < cols; ++j){
                
                int r,g,b;
                stream >> r >> g >> b;
                std::cout << "(" << r << ", " << g << ", " << b << "),";
                
                if(r == 0 && g == 0 && b == 0) {
                    // Black pixel is a wall
                    row.push_back(Maze::DisplayCharacters::wall);
                    std::cout << "Wall\t";
                } else if (r == 255 && g == 0 && b == 0){
                    // Red pixel is the finish
                    row.push_back(Maze::DisplayCharacters::finish_room);
                    std::cout << "Finish\t";
                } else if(r == 255 && g == 0 && b == 255){
                    // Purple pixel is the start
                    row.push_back(Maze::DisplayCharacters::start_room);
                    std::cout << "Start\t";
                } else if(r == 255 && g == 255 && b == 255){
                    // Pixel is white so it could be a room or a passage
                    if(i % 2 == 1 && j % 2 == 1){
                        // row and column are both odd, so its a room
                        row.push_back(Maze::DisplayCharacters::room);
                        std::cout << "Room\t";
                    } else if (i % 2 == 1 && j % 2 == 0){
                        // row is odd and column is even, so its a horizontal passage
                        row.push_back(Maze::DisplayCharacters::horiz_passage);
                        std::cout << "HPass\t";
                    } else {
                        // row is even and column is odd, so its a vertical passage
                        // Note that we don't care about when row and col are both even because that
                        // will always be a wall, so it is taken care of in the black pixel section
                        row.push_back(Maze::DisplayCharacters::vert_passage);
                        std::cout << "VPass\t";
                    }
                }
                
            }
            std::cout << std::endl;
            maze_display.push_back(row);
            
        }
        
        // while(std::getline(file, str)){
        //     std::cout << str << std::endl;
            
        // }
        std::cout << "Done reading file, printing maze:" << std::endl;
        drawMazeToConsole(maze_display);
        
    }
}