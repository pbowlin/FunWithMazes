#pragma once

/*
This is a fully static class whose methods can be invoked with different
algorithms with which to solve and display a provided maze.
*/

#include "MazeCell.h"
#include "Maze.h"

#include <vector>
#include <functional>
#include <tuple>
#include <unordered_set>

class MazeSolver {
    public:
        static std::tuple<std::vector<CellCoords>, std::vector<std::vector<std::string>>> solveMaze(const Maze& maze, std::function<int(const CellCoords&, const CellCoords&)> heuristic_func,
                    std::function<std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>>(const std::vector<std::vector<MazeCell>>&, const CellCoords&, const CellCoords&, 
                    std::function<int(const CellCoords&, const CellCoords&)>)>solver_func);
        
        static std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> AStarSolver(const std::vector<std::vector<MazeCell>>& maze, const CellCoords& start, const CellCoords& finish, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func);
        static std::vector<std::vector<std::string>> generateSolutionDisplay(const Maze& maze, const std::vector<CellCoords>& solution, const std::unordered_set<CellCoords>& touched);
        
        
    private:
        MazeSolver(); // This class cannot be instantiated
        
        static std::vector<CellCoords> reconstruct_path(const std::unordered_map<CellCoords, CellCoords>& came_from, const CellCoords& finish);
};