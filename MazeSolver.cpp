#include "MazeSolver.h"

#include <iostream>
#include <queue>
#include <cmath>
#include <unordered_map>

std::vector<MazeCell> MazeSolver::solveMaze(const std::vector<std::vector<MazeCell>>& maze, const CellCoords& start, const CellCoords& finish, std::function<int(const CellCoords&, const CellCoords&)> heuristic_func,
                    std::function<std::vector<MazeCell>(const std::vector<std::vector<MazeCell>>&, const CellCoords&, const CellCoords&, 
                    std::function<int(const CellCoords&, const CellCoords&)>)>solver_func){
                        
    std::cout << "Solving maze" << std::endl;
    std::vector<MazeCell> solution = solver_func(maze, start, finish, heuristic_func);
    
    return solution;
}

        
std::vector<MazeCell> MazeSolver::AStarSolver(const std::vector<std::vector<MazeCell>>& maze, const CellCoords& start, const CellCoords& finish, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func){
    std::cout << "Solving maze with A* algorithm" << std::endl;
    std::vector<MazeCell> solution;
    
    // Compares two cells by manhattan distance to the goal as a heuristic for the priority queue.
    auto lambda_compare = [finish, &heuristic_func](const CellCoords& lhs, const CellCoords& rhs){
        int lhs_manhattan = heuristic_func(lhs, finish);
        int rhs_manhattan = heuristic_func(rhs, finish);
        
        return lhs_manhattan >= rhs_manhattan;
    };
    
    std::priority_queue<CellCoords, std::vector<CellCoords>, decltype(lambda_compare)> open_cells(lambda_compare);
    
    open_cells.push(start);
    
    std::unordered_map<CellCoords, CellCoords> came_from; // The key is a cell and the value is the cell that preceeds the key cell on the cheapest path from the start
    std::unordered_map<CellCoords, int> cheapest_path_from_start; // Maps each cell to its cost on the cheapest path from the start
    std::unordered_map<CellCoords, int> estimated_cost_to_goal; // maps each cell to its estimated cost to the goal based on the heuristic
    
    cheapest_path_from_start[start] = 0;
    estimated_cost_to_goal[start] = heuristic_func(start, finish);
    
    
    // std::cout << "Finish: " << finish << std::endl;
    
    // open_cells.push({0, 1});
    // open_cells.push({0, 5});
    // open_cells.push({0, 3});
    // open_cells.push({0, 4});
    
    // int i = 1;
    // while(open_cells.size()){
    //     std::cout << i << ": " << open_cells.top() << std::endl;
    //     open_cells.pop();
    //     i++;
    // }
    
    
    
    
    
    return solution;
}