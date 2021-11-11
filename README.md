# FunWithMazes
Solo project to explore different maze generation and solving algorithms and techniques.

As of now there are 3 maze generation algorithms and 2 maze solving algorithms.
Maze Generation:
    Depth First Maze - Biased towards long winding corridors. 
    Prim's Maze - Biased towards frequent and short dead ends.
    Wilson's Maze - Unbiased. Has a good mix of long and short paths.
    
    Each of the above algorithms generates a simple maze, meaning that from any point in the maze there is exactly 1 path to any other point in the maze.
    As such, there are no loops, there is only 1 solution to the maze, and obviously that solution is also the shortest path through the maze.
    
Maze Solving:
    A* Search - Has an "omniscient" view of the maze (it knows where the start and finish are and uses that knowledge to direct its solution search).
        As of now, you can set the heuristic used by A* to be either manhattan or euclidean distance to the finish. 
        A* will find the shortest path through the maze (given some assumptions about the heuristic used) even if it is not a simple maze
        
    Tremaux's Algorithm - Has no knowledge of the maze it is searching
        It is a blind algorithm that, unlike other more naive blind solving implementaions like wall following, will successfully find the exit even if there are loops in the maze. 
        It is not guaranteed to find the shortest path through the maze. 


compile with:
makefile 
or 	g++ -std=c++17 -o FunWithMazes.exe RunMaze.cpp MazeCell.cpp Maze.cpp DFSMaze.cpp... etc

can check with valgrind using:
valgrind --leak-check=yes ./FunWithMazes.exe
