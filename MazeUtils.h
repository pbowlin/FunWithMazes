#pragma once

#include "Maze.h"

#include <string>
#include <vector>
#include <unordered_set>

namespace mazeBenchmarking {
    void benchmarkMaze(std::string maze_type, int rows, int cols, int bench_trials);
}

namespace mazeUtils {
    void drawMazeToConsole(const std::vector<std::vector<std::string>>& maze_display);
    void saveMazeAsTxt(const std::vector<std::vector<std::string>>& maze_display);
    void saveMazeAsImg(const Maze& maze, const std::vector<std::vector<std::string>>& maze_display, int scale, std::string filename_suffix);
    int randomlySelectNextIndex(int num_options);
    std::string generateFilename(const Maze& maze, std::string filename_suffix);
}

namespace mazeAnimation {
    extern std::string solver_type;
    extern std::string heuristic_type;
    extern bool create_animation;
    extern int animation_frame_delay; // Delay is in 1/100ths of a second.
    
    void addAnimationFrame(const Maze& maze, const MazeSolutionDisplayElements solution_elems, CellCoords current);
}