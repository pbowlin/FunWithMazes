FunWithMazes.exe: RunMaze.o MazeCell.o Maze.o DFSMaze.o WilsonsMaze.o PrimsMaze.o MazeSolver.o Timer.o MazeFactory.o MazeUtils.o
	g++ -std=c++17 -o FunWithMazes.exe RunMaze.o MazeCell.o Maze.o DFSMaze.o WilsonsMaze.o PrimsMaze.o MazeSolver.o Timer.o MazeFactory.o MazeUtils.o
    
RunMaze.o: RunMaze.cpp
	g++ -std=c++17 -c RunMaze.cpp

MazeCell.o: MazeCell.cpp MazeCell.h
	g++ -std=c++17 -c MazeCell.cpp

Maze.o: Maze.cpp Maze.h
	g++ -std=c++17 -c Maze.cpp

DFSMaze.o: DFSMaze.cpp DFSMaze.h
	g++ -std=c++17 -c DFSMaze.cpp

WilsonsMaze.o: WilsonsMaze.cpp WilsonsMaze.h
	g++ -std=c++17 -c WilsonsMaze.cpp

PrimsMaze.o: PrimsMaze.cpp PrimsMaze.h
	g++ -std=c++17 -c PrimsMaze.cpp

MazeSolver.o: MazeSolver.cpp MazeSolver.h
	g++ -std=c++17 -c MazeSolver.cpp

Timer.o: Timer.cpp Timer.h
	g++ -std=c++17 -c Timer.cpp
	
MazeFactory.o: MazeFactory.cpp MazeFactory.h
	g++ -std=c++17 -c MazeFactory.cpp
	
MazeUtils.o: MazeUtils.cpp MazeUtils.h
	g++ -std=c++17 -c MazeUtils.cpp

clean:
	rm *.o FunWithMazes.exe