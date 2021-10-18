
#include "MazeCell.h"
#include "DFSMaze.h"

int main(){
    
    MazeCell mc(3,5);
    mc.printCellCoords();
    
    DFSMaze m(20, 20);
    
    m.generateMaze();
    //m.listCells();
    m.drawMaze();
    
}