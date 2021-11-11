#include "MazeCell.h"

#include <iostream>
#include <string>
#include <cmath>

/////////////////////////////////////////////////////////
// CellCoords operator overloads, hashing, and methods //
/////////////////////////////////////////////////////////

bool operator==(const CellCoords& lhs , const CellCoords& rhs){
    return lhs.row == rhs.row && lhs.col == rhs.col;
}

bool operator!=(const CellCoords& lhs , const CellCoords& rhs){
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& o, const CellCoords& cc ){
    return o << "(" << cc.row << ", " << cc.col << ")";
}

std::size_t std::hash<CellCoords>::operator()(const CellCoords& coords) const {
    return std::hash<std::string>()(to_string(coords.row) + to_string(coords.col));
}

// Returns the manhattan distance from cell_a to cell_b
int CellCoords::manhattan_distance(const CellCoords& cell_a, const CellCoords& cell_b){
    return std::abs(cell_a.row - cell_b.row) + std::abs(cell_a.col - cell_b.col);
}

// Returns the euclidean distance (stright line distance) from cell_a to cell_b
int CellCoords::euclidean_distance(const CellCoords& cell_a, const CellCoords& cell_b){
    return std::sqrt(std::pow(cell_a.row - cell_b.row, 2) + std::pow(cell_a.col - cell_b.col, 2));
}

/////////////////////////////////////////////
// MazeCell operator overloads and hashing //
/////////////////////////////////////////////

bool operator==(const MazeCell& lhs , const MazeCell& rhs){
    return lhs.coords == rhs.coords;
}

std::ostream& operator<<(std::ostream& o, const MazeCell& mc ){
    return o << mc.coords;
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

std::size_t std::hash<MazeCell>::operator()(const MazeCell& cell) const {
    // return std::hash<std::string>()(to_string(cell.getCellCoords().row) + to_string(cell.getCellCoords().col));
    return std::hash<CellCoords>()(cell.getCellCoords());
}

/////////////////////////////////////
// MazeCell method implementations //
/////////////////////////////////////

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

bool MazeCell::isConnected(const MazeCell& mc) const{
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