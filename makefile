## Added zzz_ to all object files just to automatically sort them at the end of the list of files. I feel this keeps the directory looking a bit cleaner.

zzzz_FunWithMazes.exe: zzz_RunMaze.o zzz_MazeCell.o zzz_Maze.o zzz_DFSMaze.o zzz_WilsonsMaze.o zzz_PrimsMaze.o zzz_CustomMaze.o zzz_MazeSolver.o zzz_Timer.o zzz_MazeFactory.o zzz_MazeUtils.o
	g++ -std=c++17 -o zzzz_FunWithMazes.exe zzz_RunMaze.o zzz_MazeCell.o zzz_Maze.o zzz_DFSMaze.o zzz_WilsonsMaze.o zzz_PrimsMaze.o zzz_CustomMaze.o zzz_MazeSolver.o zzz_Timer.o zzz_MazeFactory.o zzz_MazeUtils.o
    
zzz_RunMaze.o: RunMaze.cpp
	g++ -std=c++17 -o zzz_RunMaze.o -c RunMaze.cpp

zzz_MazeCell.o: MazeCell.cpp MazeCell.h
	g++ -std=c++17 -o zzz_MazeCell.o -c MazeCell.cpp

zzz_Maze.o: Maze.cpp Maze.h
	g++ -std=c++17 -o zzz_Maze.o -c Maze.cpp

zzz_DFSMaze.o: DFSMaze.cpp DFSMaze.h
	g++ -std=c++17 -o zzz_DFSMaze.o -c DFSMaze.cpp

zzz_WilsonsMaze.o: WilsonsMaze.cpp WilsonsMaze.h
	g++ -std=c++17 -o zzz_WilsonsMaze.o -c WilsonsMaze.cpp

zzz_PrimsMaze.o: PrimsMaze.cpp PrimsMaze.h
	g++ -std=c++17 -o zzz_PrimsMaze.o -c PrimsMaze.cpp

zzz_CustomMaze.o: CustomMaze.cpp CustomMaze.h
	g++ -std=c++17 -o zzz_CustomMaze.o -c CustomMaze.cpp

zzz_MazeSolver.o: MazeSolver.cpp MazeSolver.h
	g++ -std=c++17 -o zzz_MazeSolver.o -c MazeSolver.cpp

zzz_Timer.o: Timer.cpp Timer.h
	g++ -std=c++17 -o zzz_Timer.o -c Timer.cpp
	
zzz_MazeFactory.o: MazeFactory.cpp MazeFactory.h
	g++ -std=c++17 -o zzz_MazeFactory.o -c MazeFactory.cpp
	
zzz_MazeUtils.o: MazeUtils.cpp MazeUtils.h
	g++ -std=c++17 -o zzz_MazeUtils.o -c MazeUtils.cpp

clean:
	rm *.o zzzz_FunWithMazes.exe