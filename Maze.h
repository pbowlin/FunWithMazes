#pragma once
/*
Abstract class to define a generic maze. All mazes should have a maze grid
as well as a start and finish. Neighbors are defined as cells orthagonal to 
a given cell... regardless of whether or not there is a wall between them.
*/

#include "MazeCell.h"

#include <vector>
#include <string>
#include <tuple>

class Maze {
  public:
  
    Maze(int rows, int cols);
    virtual ~Maze() = default;
  
    virtual void generateMaze() = 0;
    virtual void generateMazeDisplay(std::vector<std::vector<std::string>>& maze_display) const;
    
    void listCellsWithPassages() const;
    const std::vector<std::vector<MazeCell>>& getMaze() const;
    CellCoords getStart() const;
    CellCoords getFinish() const;
    std::tuple<int, int> getSize() const;
    std::string getType() const;
    
    
    struct DisplayCharacters {
      // Note that the characters are formatted to colorize them in the linux terminal i.e \033[;32mThis text is green\033[0m
      inline static std::string wall = "███";
      inline static std::string room = "   "; // "··"
      inline static std::string vert_passage = " ^ ";
      inline static std::string horiz_passage = " - ";
      inline static std::string solution_path = " \033[1;32m*\033[0m ";
      inline static std::string solution_touched = " \033[;36m*\033[0m ";
      inline static std::string start_room = " \033[1;31mS\033[0m ";
      inline static std::string finish_room = " \033[1;31mF\033[0m ";
    };
    
    //static void display_maze(const std::vector<std::vector<std::string>>& maze_display);
    
    
  protected:
    virtual void initializeCells(int rows, int cols);
    virtual std::vector<CellCoords> getNeighbors(int row, int col); 
    virtual void pickStartAndFinish();
    virtual bool cellVisited(const std::vector<CellCoords>& visited, const CellCoords& cell);
    
    int randomlySelectNextIndex(int num_options);
    
    std::string type;
    int maze_rows, maze_cols;
    CellCoords start;
    CellCoords finish;
    std::vector<std::vector<MazeCell>> maze;
    
     
};