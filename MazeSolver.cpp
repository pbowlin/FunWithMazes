#include "MazeSolver.h"

#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <string>

std::tuple<std::vector<CellCoords>, std::vector<std::vector<std::string>>> MazeSolver::solveMaze(const Maze& maze, std::function<int(const CellCoords&, const CellCoords&)> heuristic_func,
                    std::function<std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>>(const Maze& maze_obj, std::function<int(const CellCoords&, const CellCoords&)>)>solver_func){
                        
    auto[solution, touched] = solver_func(maze, heuristic_func); // <--- return is captured with structured bindings. Cool!
    
    std::vector<std::vector<std::string>> solution_display = generateSolutionDisplay(maze, solution, touched);
    
    return {solution, solution_display};
}

        
std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> MazeSolver::AStarSolver(const Maze& maze_obj, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func){
    std::cout << "Solving maze with A* algorithm" << std::endl;
    const std::vector<std::vector<MazeCell>>& maze = maze_obj.getMaze();
    const CellCoords start = maze_obj.getStart();
    const CellCoords finish = maze_obj.getFinish();
    
    std::vector<CellCoords> solution;
    std::unordered_set<CellCoords> touched;
    
    // Compares two cells by the provided heuristic for the priority queue.
    // For priority queue this function should return true if the lhs goes BEFORE the rhs in the queue (meaning it would be a lower priority)
    auto lambda_compare = [finish, &heuristic_func](const CellCoords& lhs, const CellCoords& rhs){
        int lhs_score = heuristic_func(lhs, finish);
        int rhs_score = heuristic_func(rhs, finish);
        
        return lhs_score >= rhs_score;
    };
    
    std::priority_queue<CellCoords, std::vector<CellCoords>, decltype(lambda_compare)> open_cells(lambda_compare); // Holds the nodes that may need to be expanded. The current best option for expansion is always on top.
    std::unordered_set<CellCoords> expansion_candidates; // Only purpose of this is to mirror the cells in the priority queue to allow constant time lookup to check if a cell is in the queue
    open_cells.push(start);
    expansion_candidates.insert(start);
    
    // Quick structure to default an int value to infinity rather than 0
    struct path_cost {
        double cost = std::numeric_limits<double>::max();
    };
    
    std::unordered_map<CellCoords, CellCoords> came_from; // The key is a cell and the value is the cell that preceeds the key cell on the cheapest path from the start
    std::unordered_map<CellCoords, path_cost> cheapest_path_from_start; // Maps each cell to its cost on the cheapest path from the start
    std::unordered_map<CellCoords, path_cost> estimated_cost_to_goal; // maps each cell to its estimated cost to the goal based on the heuristic
    
    cheapest_path_from_start[start].cost = 0;
    estimated_cost_to_goal[start].cost = heuristic_func(start, finish);
    
    while(!open_cells.empty()){
        CellCoords current = open_cells.top();
        touched.insert(open_cells.top());
        
        if (current == finish){
            solution = reconstruct_path(came_from, finish);
            break;
        }
        
        open_cells.pop();
        expansion_candidates.erase(current);
        for(const MazeCell& passage : maze[current.row][current.col].getPassages()){
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
    
    return {solution, touched };
}

std::vector<CellCoords> MazeSolver::reconstruct_path(const std::unordered_map<CellCoords, CellCoords>& came_from, const CellCoords& finish){
    std::vector<CellCoords> path;
    path.push_back(finish);
    
    while(came_from.count(path.back()) != 0){
        path.push_back(came_from.at(path.back()));
    }
    
    return path;
}

std::vector<std::vector<std::string>> MazeSolver::generateSolutionDisplay(const Maze& maze, const std::vector<CellCoords>& solution, const std::unordered_set<CellCoords>& touched){
    std::vector<std::vector<std::string>> maze_display;
    maze.generateMazeDisplay(maze_display);
    
    for(const CellCoords& touch : touched){
        maze_display[touch.row*2 + 1][touch.col*2 + 1] = Maze::DisplayCharacters::solution_touched;
    }
    
    for(const CellCoords& step : solution){
        maze_display[step.row*2 + 1][step.col*2 + 1] = Maze::DisplayCharacters::solution_path;
    }
    
    // Notate the start and finish cells because they were over-ridden by the solution path
    CellCoords start = maze.getStart();
    CellCoords finish = maze.getFinish();

    maze_display[start.row*2+1][start.col*2+1] = Maze::DisplayCharacters::start_room;
    maze_display[finish.row*2+1][finish.col*2+1] = Maze::DisplayCharacters::finish_room;
    
    return maze_display;

}