#include "MazeSolver.h"
#include "MazeUtils.h"

#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <string>
#include <algorithm>

// This version of A Star will always add the cell to the open list if the path is less than the previous path. See comments in add passage block for details.
std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> MazeSolver::AStarSolver_ALWAYS_ADD(const Maze& maze_obj, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func){
    std::cout << "Solving maze with A* algorithm" << std::endl;
    const std::vector<std::vector<MazeCell>>& maze = maze_obj.getMaze();
    const CellCoords start = maze_obj.getStart();
    const CellCoords finish = maze_obj.getFinish();
    
    std::vector<CellCoords> solution;
    std::unordered_set<CellCoords> touched;
    
    // Quick structure to default an int value to infinity rather than 0
    struct path_cost {
        double cost = std::numeric_limits<double>::max();
    };
    
    std::unordered_map<CellCoords, CellCoords> came_from; // The key is a cell and the value is the cell that preceeds the key cell on the cheapest path from the start
    std::unordered_map<CellCoords, path_cost> cheapest_path_from_start; // Maps each cell to its cost on the cheapest path from the start
    cheapest_path_from_start[start].cost = 0;
    
    // Compares two cells by the provided heuristic for the priority queue.
    // For priority queue this function should return true if the lhs goes BEFORE the rhs in the queue (meaning it would be a lower priority)
    auto lambda_compare = [finish, &cheapest_path_from_start, &heuristic_func](const CellCoords& lhs, const CellCoords& rhs){
        double lhs_score = cheapest_path_from_start[lhs].cost + heuristic_func(lhs, finish);
        double rhs_score = cheapest_path_from_start[rhs].cost + heuristic_func(rhs, finish);
        
        return lhs_score >= rhs_score;
    };
    
    std::priority_queue<CellCoords, std::vector<CellCoords>, decltype(lambda_compare)> open_cells(lambda_compare); // Holds the nodes that may need to be expanded. The current best option for expansion is always on top.
    std::unordered_set<CellCoords> expansion_candidates; // Only purpose of this is to mirror the cells in the priority queue to allow constant time lookup to check if a cell is in the queue
    open_cells.push(start);
    expansion_candidates.insert(start);
    
    while(!open_cells.empty()){
        CellCoords current = open_cells.top();
        touched.insert(open_cells.top());
        
        if (current == finish){
            solution = reconstruct_path(came_from, finish);
            break;
        }
        
        open_cells.pop();
        expansion_candidates.erase(current);
        for(const CellCoords& passage : maze[current.row][current.col].getPassages()){
            int path_to_start_cost = cheapest_path_from_start[current].cost + 1;
            
            if (path_to_start_cost < cheapest_path_from_start[passage].cost){
                came_from[passage] = current;
                cheapest_path_from_start[passage].cost = path_to_start_cost;
                
                // TODO: This could be bad because if we don't check if the passage is already in the expansion candidates then we could end up with 
                // multiple of the same node inside the expansion candidates.
                open_cells.push(passage);
                expansion_candidates.insert(passage);
 
            }
            
        }
        
        if(mazeAnimation::create_animation){
            mazeAnimation::addAnimationFrame(maze_obj, touched, current);
        }
        
    }
    
    return {solution, touched };
}

// This version of A Star will only add the cell to the open list if the path is less than the previous path and the passage has not been added already. See comments in add passage block for details.
std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> MazeSolver::AStarSolver_ONLY_ADD_NEW(const Maze& maze_obj, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func){
    std::cout << "Solving maze with A* algorithm" << std::endl;
    const std::vector<std::vector<MazeCell>>& maze = maze_obj.getMaze();
    const CellCoords start = maze_obj.getStart();
    const CellCoords finish = maze_obj.getFinish();
    
    std::vector<CellCoords> solution;
    std::unordered_set<CellCoords> touched;
    
    // Quick structure to default an int value to infinity rather than 0
    struct path_cost {
        double cost = std::numeric_limits<double>::max();
    };
    
    std::unordered_map<CellCoords, CellCoords> came_from; // The key is a cell and the value is the cell that preceeds the key cell on the cheapest path from the start
    std::unordered_map<CellCoords, path_cost> cheapest_path_from_start; // Maps each cell to its cost on the cheapest path from the start
    cheapest_path_from_start[start].cost = 0;
    
    // Compares two cells by the provided heuristic for the priority queue.
    // For priority queue this function should return true if the lhs goes BEFORE the rhs in the queue (meaning it would be a lower priority)
    auto lambda_compare = [finish, &cheapest_path_from_start, &heuristic_func](const CellCoords& lhs, const CellCoords& rhs){
        double lhs_score = cheapest_path_from_start[lhs].cost + heuristic_func(lhs, finish);
        double rhs_score = cheapest_path_from_start[rhs].cost + heuristic_func(rhs, finish);
        
        return lhs_score >= rhs_score;
    };
    
    std::priority_queue<CellCoords, std::vector<CellCoords>, decltype(lambda_compare)> open_cells(lambda_compare); // Holds the nodes that may need to be expanded. The current best option for expansion is always on top.
    std::unordered_set<CellCoords> expansion_candidates; // Only purpose of this is to mirror the cells in the priority queue to allow constant time lookup to check if a cell is in the queue
    open_cells.push(start);
    expansion_candidates.insert(start);
    
    while(!open_cells.empty()){
        CellCoords current = open_cells.top();
        touched.insert(open_cells.top());
        
        if (current == finish){
            solution = reconstruct_path(came_from, finish);
            break;
        }
        
        open_cells.pop();
        expansion_candidates.erase(current);
        for(const CellCoords& passage : maze[current.row][current.col].getPassages()){
            int path_to_start_cost = cheapest_path_from_start[current].cost + 1;
            
            if (path_to_start_cost < cheapest_path_from_start[passage].cost){
                came_from[passage] = current;
                cheapest_path_from_start[passage].cost = path_to_start_cost;
                
                // TODO: I believe the below method could be bad because if we only add the passage to the open cells when it is not already in there then we are
                // neglecting to re-order the priority queue when we find a better path to a cell we have already seen. 
                if(expansion_candidates.count(passage) == 0){
                    open_cells.push(passage);
                    expansion_candidates.insert(passage);
                }
                
            }
            
        }
        
    }
    
    return {solution, touched };
}

// This version of A Star will always only consider the cost to the goal when figuring which cell to expand next (This is not a correct A* but seems to be much less costly -- i.e. expand fewer
// nodes -- for simple mazes like what I am generating... where the path is likely to be better if you are closer to the goal regardless of how you got there, since there is only 1 solution.)
std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> MazeSolver::AStarSolver_HEURISTIC_COST_ONLY(const Maze& maze_obj, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func){
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
        for(const CellCoords& passage : maze[current.row][current.col].getPassages()){
            int path_to_start_cost = cheapest_path_from_start[current].cost + 1;
            
            if (path_to_start_cost < cheapest_path_from_start[passage].cost){
                came_from[passage] = current;
                cheapest_path_from_start[passage].cost = path_to_start_cost;
                estimated_cost_to_goal[passage].cost = path_to_start_cost + heuristic_func(passage, finish);
                
                if(expansion_candidates.count(passage) == 0){
                    open_cells.push(passage);
                    expansion_candidates.insert(passage);
                }
                
            }
            
        }
        
    }
    
    return {solution, touched };
}

std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> MazeSolver::TremauxSolver(const Maze& maze_obj){
    std::cout << "Solving maze with Tremaux's algorithm" << std::endl;
    const std::vector<std::vector<MazeCell>>& maze = maze_obj.getMaze();
    const CellCoords start = maze_obj.getStart();
    const CellCoords finish = maze_obj.getFinish();
    
    std::vector<CellCoords> solution;
    std::unordered_set<CellCoords> touched;
    
    using marks = std::unordered_map<std::string, int>; 
    std::unordered_map<CellCoords, marks> intersection_tracker;
    
    CellCoords current = start;
    CellCoords prev = start;
    
    //Lambda to figure out what direction a cell is in reference to an intersection cell
    auto getCellDirection = [](const CellCoords& intersection_cell, const CellCoords& reference_cell){
        if(reference_cell.col - intersection_cell.col > 0){
            return "East";
        } else if(reference_cell.col - intersection_cell.col < 0){
            return "West";
        } else if(reference_cell.row - intersection_cell.row > 0){
            return "North";
        } else {
            return "South";
        }
    };
    
    int next_passage_idx;
    int loop_count=0;
    while(current != finish){
        touched.insert(current);
        const std::vector<CellCoords>* passages = &(maze[current.row][current.col].getPassages());
        if(passages->size() == 1){ 
            // Current cell is a dead end, go back
            next_passage_idx = 0;
            
        } else if( passages->size() == 2) {
            // Current cell is a passage, continue forward
            next_passage_idx = (*passages)[0] == prev ? 1 : 0;
        } else {
            // Current cell is an intersection
            
            bool first_time_at_intersection = intersection_tracker.count(current) == 0;
            intersection_tracker[current][getCellDirection(current,prev)] += 1; // Mark the intersection from the direction we came
            
            if(first_time_at_intersection){
                // We have never been to this intersection before so proceed in a random new direction
                do {
                    next_passage_idx = mazeUtils::randomlySelectNextIndex(passages->size());
                } while ((*passages)[next_passage_idx] == prev );
                
                // Mark the intersection with the direction of the path we chose
                intersection_tracker[current][getCellDirection(current, (*passages)[next_passage_idx])] = 1;
            } else {
                // We have visited this intersection before
                if (intersection_tracker[current][getCellDirection(current,prev)] == 1 ){
                    // There are not 2 marks on the direction from which we entered, so mark it again and go back the way we came
                    intersection_tracker[current][getCellDirection(current,prev)] += 1;
                    for(int i = 0; i < passages->size(); ++i){
                        if((*passages)[i] == prev){
                            next_passage_idx = i;
                            break;
                        }
                    }
                } else {
                    // There are 2 marks on the direction from which we entered, so proceed towards the direction with the fewest marks.
                    int fewest_marks = 9999;
                    for(int i = 0; i < passages->size(); ++i){
                        CellCoords passage = (*passages)[i];
                        int passage_marks = intersection_tracker[current][getCellDirection(current, passage)];
                        if(passage_marks < fewest_marks){
                            next_passage_idx = i;
                            fewest_marks = passage_marks;
                        }
                        //next_passage_idx = intersection_tracker[current][getCellDirection(current, passage)] < fewest_marks ? i : next_passage_idx;
                    }
                    intersection_tracker[current][getCellDirection(current, (*passages)[next_passage_idx])] += 1;
                }
            }
        }
        // Advance to the next cell
        prev = current;
        current = (*passages)[next_passage_idx];
        
    }
    
    // Lastly, reconstruct the path back to the start by following the intersections with only 1 mark.
    solution.push_back(finish);
    solution.push_back(prev);
    
    current = prev;
    prev = finish;
    std::cout << "Reconstructing path" << std::endl;
    
    while(current != start){
        const std::vector<CellCoords>* passages = &(maze[current.row][current.col].getPassages());
        
        if(intersection_tracker.count(current) != 0) {
            // This is an intersection. Find the direction with only 1 mark to know which way to proceed
            for(int i = 0; i < passages->size(); ++i){
                CellCoords passage = (*passages)[i];
                if(intersection_tracker[current][getCellDirection(current, passage)] == 1 && passage != prev){
                    next_passage_idx = i;
                    break;
                }
            }
        } else {
            // This is just a passage so continue forward
            next_passage_idx = (*passages)[0] == prev ? 1 : 0;
        }
        
        prev = current;
        current = (*passages)[next_passage_idx];
        solution.push_back(current);
    }
    
    std::reverse(solution.begin(), solution.end());
    return {solution, touched};
}

std::vector<CellCoords> MazeSolver::reconstruct_path(const std::unordered_map<CellCoords, CellCoords>& came_from, const CellCoords& finish){
    std::vector<CellCoords> path;
    path.push_back(finish);
    
    while(came_from.count(path.back()) != 0){
        path.push_back(came_from.at(path.back()));
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}


// std::vector<std::vector<std::string>> MazeSolver::generateSolutionDisplay(const Maze& maze, const std::vector<CellCoords>& solution, const std::unordered_set<CellCoords>& touched){
//     std::vector<std::vector<std::string>> maze_display;
//     maze.generateMazeDisplay(maze_display);
    
//     for(const CellCoords& touch : touched){
//         maze_display[touch.row*2 + 1][touch.col*2 + 1] = Maze::DisplayCharacters::solution_touched;
//     }
    
//     for(const CellCoords& step : solution){
//         maze_display[step.row*2 + 1][step.col*2 + 1] = Maze::DisplayCharacters::solution_path;
//     }
    
//     // Notate the start and finish cells because they were over-ridden by the solution path
//     CellCoords start = maze.getStart();
//     CellCoords finish = maze.getFinish();

//     maze_display[start.row*2+1][start.col*2+1] = Maze::DisplayCharacters::start_room;
//     maze_display[finish.row*2+1][finish.col*2+1] = Maze::DisplayCharacters::finish_room;
    
//     return maze_display;

// }