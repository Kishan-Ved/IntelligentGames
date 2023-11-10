# IntelligentGames
Intelligent games in C/C++, along with a cubesolver.

# CubeSolver
## Solves any 2X2X2 Rubik's cube 
This repository contains code to solve any 2X2X2 Rubik's cube. 

The file cube.c contains the C language code to solve any cube (or return an illegal state). 

Refer to cube_img to understand the permutations and orientations, also use 2by2by2 pdf for reference. 

## Description of Moves:

R represents a clockwise turn of the right face of the cube.

U represents a clockwise turn of the up (top) face of the cube.

F represents a clockwise turn of the front face of the cube.

R', U', F' represent an anti-clockwise turn of the right, up, and front faces of the cube resp.

R2, U2, F2 represent a 180° turn of the right, up, and front faces of the cube resp.

## Data Structures Used:

This project uses only:
1. Arrays
2. Queues (implented as arrays)
3. Graphs

No inbuilt libraries have been used, all code is written from scratch. 

## Algorithm Used:

BFS - Breadth First Search is used to find the shortest path to the solve the cube.
