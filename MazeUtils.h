#pragma once

#include "Maze.h"

#include <string>
#include <vector>

namespace mazeBenchmarking {
    void benchmarkMaze(std::string maze_type, int rows, int cols, int bench_trials);
}

namespace mazeUtils {
    void drawMazeToConsole(const std::vector<std::vector<std::string>>& maze_display);
    void saveMazeAsTxt(const std::vector<std::vector<std::string>>& maze_display);
    void saveMazeAsImg(const Maze& maze, const std::vector<std::vector<std::string>>& maze_display);
}