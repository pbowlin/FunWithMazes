# FunWithMazes
Solo project to explore different maze generation and solving algorithms and techniques. I used this project as an excuse to try to play around with aspects of the C++ language that I was aware of but either had little experience with or perhaps had never used at all. It was more a learning excercise than an effort to design the best/most efficient maze generation and solving program. 

As of now there are 4 maze generation algorithms and 2 maze solving algorithms.
## Maze Generation:
- Depth First Maze - Biased towards long winding corridors. 
- Prim's Maze - Biased towards frequent and short dead ends.
- Wilson's Maze - Unbiased. Has a good mix of long and short paths.
- Custom Maze - You can read in custom mazes from images. See custom maze section below.
    
Each of the above algorithms generates a simple maze, meaning that from any point in the maze there is exactly 1 path to any other point in the maze.
As such, there are no loops, there is only 1 solution to the maze, and obviously that solution is also the shortest path through the maze.
    
## Maze Solving:
- A* Search - Has an "omniscient" view of the maze (it knows where the start and finish are and uses that knowledge to direct its solution search).
    - As of now, you can set the heuristic used by A* to be either manhattan or euclidean distance to the finish. 
    - A* will find the shortest path through the maze (given some assumptions about the heuristic used) even if it is not a simple maze
        
- Tremaux's Algorithm - Has no knowledge of the maze it is searching
    - It is a blind algorithm that, unlike other more naive blind solving implementaions like wall following, will successfully find the exit even if there are loops in the maze. 
    - It is not guaranteed to find the shortest path through the maze. 

### Custom Maze Generation
If you'd like you can read in mazes from image files for use with the program. There are two types of mazes you can read in:
- Freehand Maze - You can draw your own maze and read it in. The format of the image is as follows: 
    - Black pixels are interpreted as walls and white pixels are interpreted as rooms.
    - The start room is a purple pixel (RGB values of 255, 0, 255 respectively.)
    - The finish room is a red pixel (RGB values of 255, 0, 0 respectively.)
- Maze as a graph - This is an image that is formatted exactly in the manner that the program will save maze image files if they were generated within the program.
    - The image must have odd height and width values (i.e. image size can be 31 x 15 but not 30 x 15, 31 x 16, 30 x 16, etc...)  
    - The entire border of the image is black pixels
    - The start room is a purple pixel (RGB values of 255, 0, 255 respectively.)
    - The finish room is a red pixel (RGB values of 255, 0, 0 respectively.)
    - All odd row/col combinations are rooms, and all rooms are white pixels
    - All even row/col combinations are walls, and are black pixels
    - Pixels at odd/even row/col combinations are either passages or walls between rooms, represented by white or black pixels respectively

## Compiling/Running/Checking
compile with:
makefile 
or 	g++ -std=c++17 -o FunWithMazes.exe RunMaze.cpp MazeCell.cpp Maze.cpp DFSMaze.cpp... etc

can check with valgrind using:
valgrind --leak-check=yes ./FunWithMazes.exe

