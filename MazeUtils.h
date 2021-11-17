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
}

namespace mazeAnimation {
    static std::string gif_filename = "Test.gif";
    static bool create_animation = false;
    static int animation_frame_delay_ms = 10;
    
    void addAnimationFrame(const Maze& maze, const std::unordered_set<CellCoords>& touched, CellCoords current);
}