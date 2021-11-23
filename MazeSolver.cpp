#include "MazeSolver.h"
#include "MazeUtils.h"

#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <string>
#include <algorithm>
#include <vector>


std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> MazeSolver::AStarSolver(const Maze& maze_obj, std::function<int(const CellCoords&, const CellCoords&)>heuristic_func){
    std::cout << "Solving maze with A* algorithm" << std::endl;
    mazeAnimation::solver_type = "_Astar";
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
    
    // Compares two cells by the provided heuristic for sorting the vector.
    // This function should return true if the lhs goes BEFORE the rhs in the container (meaning it would be a less desirable cell to explore)
    auto lambda_compare = [finish, &cheapest_path_from_start, &heuristic_func](const CellCoords& lhs, const CellCoords& rhs){
        double lhs_heur = heuristic_func(lhs, finish);
        double rhs_heur = heuristic_func(rhs, finish);
        
        double lhs_score = cheapest_path_from_start[lhs].cost + lhs_heur;
        double rhs_score = cheapest_path_from_start[rhs].cost + rhs_heur;

        if(lhs_score == rhs_score){
            return lhs_heur >= rhs_heur;
        }
        
        return lhs_score >= rhs_score;
    };
    
    std::vector<CellCoords> open_cells; // Holds the nodes that may need to be expanded. The current best option for expansion is always on top.
                                        // Used vector here instead of priority queue so that I have exact control over how/when elements are added and sorted in the container
    std::unordered_set<CellCoords> expansion_candidates; // Only purpose of this is to mirror the cells in the priority queue to allow constant time lookup to check if a cell is in the queue
    open_cells.push_back(start);
    expansion_candidates.insert(start);
    
    CellCoords current;
    int count = 0;
    while(!open_cells.empty()){
        current = open_cells.back();
        touched.insert(open_cells.back());
        
        if (current == finish){
            solution = reconstruct_path(came_from, finish);
            break;
        }
        
        open_cells.pop_back();
        expansion_candidates.erase(current);
        for(const CellCoords& passage : maze[current.row][current.col].getPassages()){
            int path_to_start_cost = cheapest_path_from_start[current].cost + 1;
            
            if (path_to_start_cost < cheapest_path_from_start[passage].cost){
                came_from[passage] = current;
                cheapest_path_from_start[passage].cost = path_to_start_cost;
                
                if(expansion_candidates.count(passage) == 0){
                    open_cells.push_back(passage);
                    expansion_candidates.insert(passage);
                }
                std::sort(open_cells.begin(), open_cells.end(), lambda_compare);
 
            }
            
        }
        if(mazeAnimation::create_animation){
            mazeAnimation::addAnimationFrame(maze_obj, {solution, touched}, current);
        }
    }
    
    if(mazeAnimation::create_animation){
        mazeAnimation::addAnimationFrame(maze_obj, {solution, touched}, current);
    }
    return {solution, touched };
}

std::tuple<std::vector<CellCoords>, std::unordered_set<CellCoords>> MazeSolver::TremauxSolver(const Maze& maze_obj){
    std::cout << "Solving maze with Tremaux's algorithm" << std::endl;
    mazeAnimation::solver_type = "_Tremaux";
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
        
        if(mazeAnimation::create_animation){
            mazeAnimation::addAnimationFrame(maze_obj, {solution, touched}, current);
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
    
    if(mazeAnimation::create_animation){
        mazeAnimation::addAnimationFrame(maze_obj, {solution, touched}, current);
    }
    
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
