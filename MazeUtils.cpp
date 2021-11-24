#include "MazeUtils.h"
#include "Timer.h"
#include "MazeFactory.h"

#include <memory>
#include <iostream>
#include <fstream>
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
        std::string filename_base = generateFilename(maze, filename_suffix);
        std::string filename_ppm = filename_base + ".ppm";
        std::string filename_png = filename_base + ".png";
        
        std::ofstream out(filename_ppm, std::ios::binary | std::ios::out | std::ios::trunc);
        
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
                } else if (elem == Maze::DisplayCharacters::current_cell){
                    elem_color = "255 125 0\n"; // Current cell is orange
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
    
    // Generates a file path based on the maze type and size. This does not add a file type extension.
    std::string generateFilename(const Maze& maze, std::string filename_suffix){
        std::string maze_type = maze.getType();
        auto[num_rows, num_cols] = maze.getSize();
        
        return "./MazeImages/Generated/" + maze_type + "_" + std::to_string(num_rows) + "x" + std::to_string(num_cols)  + filename_suffix;
    }
    
}

namespace mazeAnimation {
    void addAnimationFrame(const Maze& maze, const MazeSolutionDisplayElements solution_elems, CellCoords current){
        static int animation_frame_count = 1;
        if (animation_frame_count == 1)
            std::cout << "\tAnimating the solution while the maze is solved. This may take a while for medium/larger mazes..." << std::endl;

        std::vector<std::vector<std::string>> maze_display;
        maze.generateMazeDisplay(maze_display, &solution_elems);
        maze_display[current.row * 2 + 1][current.col * 2 + 1] = Maze::DisplayCharacters::current_cell;

        // When ImageMagick makes gifs apparently it sorts on the filename of each image and that is the order in which the images are added to the gif, so 
        // here we just pad the image number with zeros to ensure the images are added in the correct order (image 1 is appended with "000001" instead of just "1",
        // and will come before 10, which is 000010)
        int n_zero = 6;
        std::string anim_count_str = std::to_string(animation_frame_count);
        anim_count_str = std::string(n_zero - std::min(n_zero, (int)anim_count_str.length()), '0') + anim_count_str;

        std::string suffix = solver_type + anim_count_str;
        mazeUtils::saveMazeAsImg(maze, maze_display, 4, suffix);

        if (animation_frame_count % 100 == 0 || solution_elems.solution.size() != 0) {
            std::string base_filename = mazeUtils::generateFilename(maze, solver_type);
            std::string miff_filename = base_filename + anim_count_str + ".miff"; // Intermediate filetype for image magick while building the gif
            std::string png_filename = base_filename + "*.png";

            // Create an animation with Image Magick with the following command:
            // convert -delay ##(in ms) -loop ##(0 for infinite loop) [images/gifs to add to animation seperated by spaces (wildcards allowed)] [destination filepath]
            // Example: convert -delay 50 -loop 0 testDFS.gif PrimsMaze_30x30*.png testMaze.gif
            std::string imageMagick_animate_command = "convert -delay " + std::to_string(animation_frame_delay) + " -loop 1 " + png_filename + " " + miff_filename;
            system(imageMagick_animate_command.c_str());

            std::string remove_command = "rm " + png_filename;
            system(remove_command.c_str());

            std::cout << "\t" << animation_frame_count << " frames animated." << std::endl;
        }

        if (solution_elems.solution.size() != 0) {
            std::cout << "\tFinalizing maze animation..." << std::endl;
            std::string base_filename = mazeUtils::generateFilename(maze, solver_type);
            std::string miff_filename = base_filename + "*.miff"; // All our images have been saved in .miff files, so we use these files to build the final gif
            std::string gif_filename = base_filename + ".gif";

            std::string imageMagick_final_animate = "convert -delay " + std::to_string(animation_frame_delay) + " -loop 1 " + miff_filename + " " + gif_filename;
            system(imageMagick_final_animate.c_str());

            std::string remove_command = "rm " + miff_filename;
            system(remove_command.c_str());

            std::cout << "\tDone animating maze." << std::endl;
            animation_frame_count = 0;
        } else {
            ++animation_frame_count;
        }

    }
}