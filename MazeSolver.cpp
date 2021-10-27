#include "MazeSolver.h"

#include <iostream>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <limits>

std::vector<CellCoords> MazeSolver::solveMaze(const std::vector<std::vector<MazeCell>>& maze, const CellCoords& start, const CellCoords& finish, std::function<int(const CellCoords&, const CellCoords&)> heuristic_func,
                    std::function<std::vector<CellCoords>(const std::vector<std::vector<MazeCell>>&, const CellCoords&, const CellCoords&, 
                    std::function<int(const CellCoords&, const CellCoords&)>)>solver_func){
                        
    std::cout << "Solving maze" << std::endl;
    std::vector<CellCoords> solution = solver_func(maze, start, finish, heuristic_func);
    
    return solution;
}

        
std::vector<CellCoords> MazeSolver::AStarSolver(const std::vector<std::vector<MazeCell>>& maze, const CellCoords& start, const CellCoords& finish, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func){
    std::cout << "Solving maze with A* algorithm" << std::endl;
    std::vector<CellCoords> solution;
    
    // Compares two cells by manhattan distance to the goal as a heuristic for the priority queue.
    auto lambda_compare = [finish, &heuristic_func](const CellCoords& lhs, const CellCoords& rhs){
        int lhs_manhattan = heuristic_func(lhs, finish);
        int rhs_manhattan = heuristic_func(rhs, finish);
        
        return lhs_manhattan >= rhs_manhattan;
    };
    
    std::priority_queue<CellCoords, std::vector<CellCoords>, decltype(lambda_compare)> open_cells(lambda_compare); // Holds the nodes that may need to be expanded. The current best option for expansion is always on top.
    std::unordered_set<CellCoords> expansion_candidates; // Only purpose of this is to mirror the cells in the priority queue to allow constant time lookup to check if a cell is in the queue
    open_cells.push(start);
    expansion_candidates.insert(start);
    
    // Quick structure to default an int value to infinity rather than 0
    struct path_cost {
        int cost = std::numeric_limits<int>::max();
    };
    
    std::unordered_map<CellCoords, CellCoords> came_from; // The key is a cell and the value is the cell that preceeds the key cell on the cheapest path from the start
    std::unordered_map<CellCoords, path_cost> cheapest_path_from_start; // Maps each cell to its cost on the cheapest path from the start
    std::unordered_map<CellCoords, path_cost> estimated_cost_to_goal; // maps each cell to its estimated cost to the goal based on the heuristic
    
    cheapest_path_from_start[start].cost = 0;
    estimated_cost_to_goal[start].cost = heuristic_func(start, finish);
    
    while(!open_cells.empty()){
        CellCoords current = open_cells.top();
        //std::cout << "Current cell: " << current << std::endl;
        if (current == finish){
            //std::cout << "Finish cell reached: " << current << std::endl;
            std::vector<CellCoords> final_path = reconstruct_path(came_from, finish);
            std::cout << "Path: " << std::endl;
            for(auto x : final_path){
                std::cout << x << std::endl;
            }
            break;
        }
        
        open_cells.pop();
        expansion_candidates.erase(current);
        for(const MazeCell& passage : maze[current.row][current.col].getPassages()){
            //std::cout << passage << std::endl;
            int path_to_start_cost = cheapest_path_from_start[current].cost + 1;
            
            if (path_to_start_cost < cheapest_path_from_start[passage.getCellCoords()].cost){
                came_from[passage.getCellCoords()] = current;
                cheapest_path_from_start[passage.getCellCoords()].cost = path_to_start_cost;
                estimated_cost_to_goal[passage.getCellCoords()].cost = path_to_start_cost + heuristic_func(passage.getCellCoords(), finish);
                
                if(expansion_candidates.count(passage.getCellCoords()) == 0){
                    open_cells.push(passage.getCellCoords());
                    expansion_candidates.insert(passage.getCellCoords());
                }
                
            }
            
        }
        
    }
    
    return solution;
}

std::vector<CellCoords> MazeSolver::reconstruct_path(const std::unordered_map<CellCoords, CellCoords>& came_from, const CellCoords& finish){
    std::vector<CellCoords> path;
    path.push_back(finish);
    
    while(came_from.count(path.back()) != 0){
        path.push_back(came_from.at(path.back()));
    }
    
    return path;
}