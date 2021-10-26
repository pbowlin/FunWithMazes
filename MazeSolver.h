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
        static std::vector<MazeCell> solveMaze(const std::vector<std::vector<MazeCell>>& maze, const CellCoords& start, const CellCoords& finish, std::function<int(const CellCoords&, const CellCoords&)> heuristic_func,
                    std::function<std::vector<MazeCell>(const std::vector<std::vector<MazeCell>>&, const CellCoords&, const CellCoords&, 
                    std::function<int(const CellCoords&, const CellCoords&)>)>solver_func);
        
        static std::vector<MazeCell> AStarSolver(const std::vector<std::vector<MazeCell>>& maze, const CellCoords& start, const CellCoords& finish, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func);
        
    private:
        MazeSolver(); // This class cannot be instantiated
};