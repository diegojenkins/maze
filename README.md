This program solves a simple maze using the wall follower algorithm, and following the right wall.
The code tracks both a position and a direction of the walker. A matrix structure is  used to store postion information.

The code is modular, with functions to test if a given square in the maze or is a wall. Movement of the walker is accomplished 
with a function to rotate the walker, and a function to go forward. The modular code allows possible changes to the algorithm, 
while still using the same basic functions for movement.

To compile, type in "make".

To run the program, type in "./maze MAZENAME", where MAZENAME is the name of the file.
If no maze is specified, an error will be output.
