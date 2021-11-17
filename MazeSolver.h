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
            MazeSolutionDisplayElements* solution_elems_ptr = &solution_elems;
            maze.generateMazeDisplay(solution_display, solution_elems_ptr);
            
            return {solution, solution_display};
        }
        
        static std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> AStarSolver_ALWAYS_ADD(const Maze& maze_obj, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func);
        static std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> AStarSolver_ONLY_ADD_NEW(const Maze& maze_obj, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func);
        static std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> AStarSolver_HEURISTIC_COST_ONLY(const Maze& maze_obj, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func);
        static std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> TremauxSolver(const Maze& maze_obj);
        //static std::vector<std::vector<std::string>> generateSolutionDisplay(const Maze& maze, const std::vector<CellCoords>& solution, const std::unordered_set<CellCoords>& touched);
        
        
    private:
        MazeSolver(); // This class cannot be instantiated
        
        static std::vector<CellCoords> reconstruct_path(const std::unordered_map<CellCoords, CellCoords>& came_from, const CellCoords& finish);
};