#pragma once

#include <vector>
#include <iostream>

struct CellCoords {
    int row, col;
    
    static int manhattan_distance(const CellCoords& cell_a, const CellCoords& cell_b);
};

bool operator==(const CellCoords& lhs , const CellCoords& rhs);
std::ostream& operator<<(std::ostream& o, const CellCoords& cc);

class MazeCell {
    private:
        CellCoords coords;
        std::vector<MazeCell> has_passages_to;
        
    public:
        
        MazeCell(int row, int col);
        MazeCell() = delete;
        void addPassage(MazeCell& connection);
        CellCoords getCellCoords() const;
        const std::vector<MazeCell>& getPassages() const;
        bool isConnected(const MazeCell& mc) const;
        
        void printCellCoords();
        void printPassages();
        
        friend bool operator==(const MazeCell& lhs , const MazeCell& rhs);
        friend std::ostream& operator<<(std::ostream& o, const MazeCell& mc);
        friend std::ostream& operator<<(std::ostream& o, const std::vector<MazeCell>& passages);
        friend std::ostream& operator<<(std::ostream& o, const std::vector<MazeCell*>& passages);
        
        
};

namespace std {

  template <>
  struct hash<MazeCell>
  {
    std::size_t operator()(const MazeCell& cell) const;
  };
  
  template <>
  struct hash<CellCoords>
  {
    std::size_t operator()(const CellCoords& coords) const;
  };

}