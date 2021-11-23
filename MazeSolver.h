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
    
        template<typename F, typename... Args>
        static std::tuple<std::vector<CellCoords>, std::vector<std::vector<std::string>>> solveMaze(const Maze& maze, F solver_func, Args...args){
            auto[solution, touched] = solver_func(maze, args...); // <--- return is captured with structured bindings. Cool!
    
            std::vector<std::vector<std::string>> solution_display;
            MazeSolutionDisplayElements solution_elems = {solution, touched};
            maze.generateMazeDisplay(solution_display, &solution_elems);
            
            return {solution, solution_display};
        }
        
        static std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> AStarSolver(const Maze& maze_obj, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func);
        static std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> TremauxSolver(const Maze& maze_obj);
        static void decideMazeSolver(const Maze& maze);
        
    private:
        MazeSolver(); // This class cannot be instantiated
        
        static std::vector<CellCoords> reconstruct_path(const std::unordered_map<CellCoords, CellCoords>& came_from, const CellCoords& finish);
};