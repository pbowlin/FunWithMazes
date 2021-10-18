#include "MazeCell.h"

#include <iostream>

bool operator==(const MazeCell& lhs , const MazeCell& rhs){
    return lhs.coords.row == rhs.coords.row && lhs.coords.col == rhs.coords.col;
}

std::ostream& operator<<(std::ostream& o, const MazeCell& mc ){
    return o << "(" << mc.coords.row << ", " << mc.coords.col << ")";
}

std::ostream& operator<<(std::ostream& o, const std::vector<MazeCell>& neighbors ){
    for(const MazeCell& mc : neighbors){
        o << mc << ", ";
    }
    
    return o;
}

std::ostream& operator<<(std::ostream& o, const std::vector<MazeCell*>& neighbors ){
    for(const MazeCell* mc : neighbors){
        o << *mc << ", ";
    }
    
    return o;
}

MazeCell::MazeCell(int row, int col) : 
    coords(CellCoords{row,col})
{

}

void MazeCell::addPassage(MazeCell& connection){
    has_passages_to.push_back(connection);
}

const std::vector<MazeCell>& MazeCell::getPassages() const{
    return has_passages_to;
}

bool MazeCell::isConnected(const MazeCell& mc){
    for(const MazeCell& passage : has_passages_to){
        if (passage == mc)
            return true;
    }
    return false;
}

CellCoords MazeCell::getCellCoords() const{
    return coords;
}

void MazeCell::printCellCoords(){
    std::cout << "row: " << coords.row << ", col: " << coords.col << std::endl;
}

void MazeCell::printPassages() {
    for (MazeCell& mc : has_passages_to){
        std::cout << "\t"; 
        mc.printCellCoords();
    }
}