#pragma once

/*
This is a fully static class whose methods can be invoked with different
algorithms with which to solve and display a provided maze.
*/

#include "MazeCell.h"

#include <vector>
#include <functional>

class MazeSolver {
    public:
        static std::vector<CellCoords> solveMaze(const std::vector<std::vector<MazeCell>>& maze, const CellCoords& start, const CellCoords& finish, std::function<int(const CellCoords&, const CellCoords&)> heuristic_func,
                    std::function<std::vector<CellCoords>(const std::vector<std::vector<MazeCell>>&, const CellCoords&, const CellCoords&, 
                    std::function<int(const CellCoords&, const CellCoords&)>)>solver_func);
        
        static std::vector<CellCoords> AStarSolver(const std::vector<std::vector<MazeCell>>& maze, const CellCoords& start, const CellCoords& finish, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func);
        
    private:
        MazeSolver(); // This class cannot be instantiated
        
        static std::vector<CellCoords> reconstruct_path(const std::unordered_map<CellCoords, CellCoords>& came_from, const CellCoords& finish);
};